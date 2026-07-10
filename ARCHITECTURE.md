# Architecture

Module-by-module deep dive through the four federation wires. The
[README](README.md) has the pitch and the screenshots; this file
has the engineering.

## Contents

- [One source, four wires](#one-source-four-wires)
- [Module boundary discipline](#module-boundary-discipline)
- [ClearanceDIS: IEEE 1278.1 wire codec](#clearancedis-ieee-12781-wire-codec)
- [ClearanceDDS: OMG DDS via Fast DDS](#clearancedds-omg-dds-via-fast-dds)
- [ClearanceRTI: OMG DDS via RTI Connext](#clearancerti-omg-dds-via-rti-connext)
- [ClearanceHLA: IEEE 1516-2010 via OpenRTI](#clearancehla-ieee-1516-2010-via-openrti)
- [Data flow inside CLEARANCE](#data-flow-inside-clearance)
- [Vendor SDK integration notes](#vendor-sdk-integration-notes)
- [What this repo does not include](#what-this-repo-does-not-include)

## One source, four wires

Every federation wire reads from the same source of truth: the sim
controller's per-tick snapshot of aircraft state, radar emissions,
comms traffic, and weapons events. On each server tick every
enabled emitter marshals that snapshot into its wire format and
writes to its transport. No emitter modifies sim state; they are
strictly downstream consumers of an authoritative struct.

```
   Sim tick (server-authoritative)
        |
        v
   Per-tick snapshot
   FAircraftState, FRadarEmission, FVoiceCommsEvent,
   FRadioTransmitter, FWeaponsFireEvent, FWeaponsDetonationEvent
        |
        +--> [FAircraftState -> FEntityState (POD)]
        |         -> ClearanceDIS::BuildEntityStatePDU
        |            -> UDP multicast 224.0.0.1:3000 (IEEE 1278.1)
        |
        +--> [FAircraftState -> AircraftState (IDL POD)]
        |         -> Fast DDS DataWriter on Domain 0
        |            -> RTPS (OMG DDS-RTPS 2.5)
        |
        +--> [FAircraftState -> AircraftState (IDL POD, same schema)]
        |         -> RTI Connext DataWriter on Domain 1
        |            -> RTPS (same wire protocol, different vendor)
        |
        +--> [FAircraftState -> AircraftStateWire (POD)]
                  -> FClearanceHLAFederate::UpdateAircraftAttributes
                     -> OpenRTI attribute update to federation "CLEARANCE"
                        -> ATCManagedAircraft object (RPR-FOM 2.0 extension)
```

Each emitter is independently start/stop-able from the operator
console via server RPCs on `AClearanceOperatorPC`
(`Server_InjectStart*` / `Server_InjectStop*`). Enabling one does
not enable any of the others; enabling all four does not
double-encode the snapshot because each emitter reads the same
source struct and marshals separately.

## Module boundary discipline

Every wire codec is a standalone C++ module. Zero Unreal types
across the public boundary. No `FName`, no `FVector`, no `TArray`,
no `UObject`. The four modules use the same discipline realised
three different ways depending on the vendor SDK's constraints.

**ClearanceDIS** exposes POD structs and free functions directly:

- `FEntityState`, `FFireEvent`, `FDetonationEvent`,
  `FEmissionSnapshot`, `FSignalEvent`, `FTransmitterState`
- `BuildEntityStatePDU(...)`, `ParseEntityStatePDU(...)`, and nine
  more Build/Parse pairs
- `FWireParams` for site/application/exercise identifiers
- `CLEARANCEDIS_API` DLL export macro that works both under UBT and
  standalone via CMake

Everything the codec needs sits in `<cstdint>`, `std::vector`,
`std::string`. That is the entire header. Presentable in an
interview without a single line of Unreal context.

**ClearanceDDS and ClearanceRTI** cannot expose POD directly
because the vendor SDKs' types leak from their headers. Both use
**PImpl**:

- Public class `FClearancePublisher` (Fast DDS) /
  `FClearanceRTIPublisher` (Connext) with a forward-declared
  `Impl` pointer
- Public methods take POD in and return POD out
- Every Fast DDS type and every RTI type stays inside the `Impl`
  translation unit

That way `#include "ClearanceDDS/ClearanceDDSPublisher.h"` in a
consumer never drags Fast DDS's `<fastdds/dds/domain/DomainParticipant.hpp>`
into the caller's compile unit, and the same for RTI's
`<dds/dds.hpp>`.

**ClearanceHLA** does the same thing: `FClearanceHLAFederate` is a
public facade over an internal `Impl` that owns the OpenRTI
`RTIambassador` and the `NullFederateAmbassador`-derived callback
receiver. Six public methods:

- `CreateFederation(federation, fomPath)` - idempotent
- `Join(federation, federate, fomPath)` - returns
  `unique_ptr<FClearanceHLAFederate>`
- `RegisterAircraftInstance(callsign)`
- `UpdateAircraftAttributes(state)`
- `PublishAircraftState(state)` - register-then-update convenience
- `Resign()` - clean tear-down

The Unreal-tied adapters (`UClearanceDISEmitter`,
`UClearanceDDSEmitter`, `UClearanceRTIEmitter`,
`UClearanceHLAEmitter`) are thin. Each `Emit*` method:

1. Reads the sim's authoritative Unreal struct
2. Converts it to POD at the module boundary
3. Calls the pure C++ API
4. Hands results back to the caller

That is where all the type coupling to Unreal lives. The wire
codecs themselves never see it.

## ClearanceDIS: IEEE 1278.1 wire codec

Six PDU types, all spec-compliant, all live-verified against
Wireshark's built-in DIS dissector.

### Entity State PDU (Type 1, §7.3.4, 144 bytes)

Every aircraft in the sim broadcasts one per tick with:
- Position in world coordinates (ECEF metres)
- Velocity in m/s along each axis
- Orientation as yaw / pitch / roll in radians
- Force ID (friendly / hostile / neutral / unknown, per RPR-FOM
  affiliation byte at spec offset 18)
- Marking as 11-byte ASCII callsign
- Entity Type (aircraft class, kind / domain / country / category)

A Wireshark-equipped observer sees every aircraft as a proper DIS
entity with a callsign and live position track. Receivable by any
DIS federate on the network.

### Fire PDU (Type 2, §7.3.3, 96 bytes)

When the operator scrambles an interceptor, each fighter emits a
Fire PDU containing:
- Firing / Target / Munition entity IDs
- Event ID (sequential, per-federate unique)
- Firing world location (ECEF metres)
- Burst Descriptor: munition type, warhead kind, fuse kind, quantity
- Velocity at launch and range

Paired with the later Detonation PDU by Event ID.

### Detonation PDU (Type 3, §7.3.4, 104 bytes)

When the intercept resolves, each fighter emits a Detonation PDU
with the same Firing / Target / Munition / Event IDs as the earlier
Fire. Result byte is set to 2 (Entity Proximate Detonation) which
is the non-lethal escort-out semantic used in ATC / air-defence
training, not a lethal engagement.

Federated observers get a full weapons-event lifecycle: Fire opens
the event, Detonation closes it, both PDUs pair by Event ID.

### Emission PDU (Type 23, §7.6.2, 100 + track/jam records)

Every active radar broadcasts one per tick with:
- Emitting entity ID
- Radar fingerprint: centre frequency (Hz), PRF (Hz), pulse width
  (microseconds), effective radiated power (dBm), emitter
  catalogue name (e.g. 4830 = ASR-9 civil surveillance), emitter
  function code (e.g. 3 = Early Warning / Surveillance)
- Current beam pointing direction (azimuth radians)
- Track/Jam list: entity ID of every aircraft the radar is
  currently painting

The Track/Jam list is the ELINT hook. An external simulator with a
Radar Warning Receiver can tell whether a CLEARANCE radar is
currently tracking IT. That is the foundation of Electronic
Intelligence.

### Transmitter PDU (Type 25, §7.7.2)

Every active radio broadcasts one Transmitter PDU per tick with:
- Radio Reference ID (owner entity, hashed from callsign via FNV-1a)
- Radio ID (which radio on the entity)
- Radio Entity Type: Kind 7 (Radio), Domain 2 (Air), Category 5
  (VHF/UHF - the standard airliner comms profile)
- Transmit State (0 off, 1 on-idle, 2 on-transmitting)
- Antenna Location (ECEF metres, tracks aircraft position)
- Frequency (Hz, 64-bit, defaulted to 121.5 MHz international ATC
  guard)
- Modulation Type (Amplitude AM Generic - standard VHF ATC)
- Crypto System (0 No Encryption)

Heartbeat companion to Signal. Federation receivers learn "there
is a radio at this position tuned to 121.5 MHz on VHF AM" from the
Transmitter stream, then map subsequent Signal PDUs to it.

### Signal PDU (Type 26, §7.7.3)

Every transcribed radio transmission (operator commands, pilot
readbacks, controller injects, facility broadcasts) emits a Signal
PDU with:
- Radio Reference ID (speaker's entity; operator uses reserved
  entity 60000 so a federation observer can filter air-side from
  ground-side)
- Radio ID
- Encoding Scheme (raw binary data - payload is opaque bytes, no
  codec dependency)
- Data Length in bits + samples
- Payload: the ASCII transcript padded to a 32-bit boundary per
  §7.7.3.9

A federated observer sees the live radio picture as
spec-compliant Signal PDUs carrying readable transcript bytes.

### Standalone library architecture

The DIS module ships with a `test/CMakeLists.txt` that builds the
round-trip test suite outside Unreal. That is what proves the
codec is portable: the same source folder drops into a Unity
project, a headless C++ command-line tool, or an HLA/RPR-FOM
gateway with zero source changes. Only the `.Build.cs` swaps for
the `CMakeLists.txt`.

The automation tests exercise the pure API directly. They include
`ClearanceDIS/ClearanceDISPDU.h`, build POD structs by hand, call
Build/Parse, and check the byte-level output. They never touch
`UClearanceDISEmitter`. Spec conformance is verifiable independent
of Unreal, of the game, of the render layer.

## ClearanceDDS: OMG DDS via Fast DDS

One DomainParticipant, one Publisher, six Topics, six DataWriters
on Domain 0. Data types defined in OMG IDL, code-generated via
`fastddsgen`, wire-encoded as CDR (Common Data Representation)
inside RTPS 2.5.

```
Topic name                       IDL struct              Mirrors DIS PDU
clearance/aircraft/state         AircraftState           Entity State (Type 1)
clearance/weapons/fire           FireEvent               Fire         (Type 2)
clearance/weapons/detonation     DetonationEvent         Detonation   (Type 3)
clearance/radar/emission         EmissionSnapshot        Emission     (Type 23)
clearance/radio/transmitter      TransmitterState        Transmitter  (Type 25)
clearance/radio/signal           SignalEvent             Signal       (Type 26)
```

Each topic carries the same field set as its DIS PDU sibling: ECEF
metres for position, m/s for velocity, radians for orientation,
32-bit ASCII markings for callsigns. Field-for-field mapping. A
DIS-to-DDS bridge is a struct-to-struct copy.

**Reliability policy: Best Effort** on all six writers. Matches
DIS fire-and-forget UDP semantics: fresh data over guaranteed
delivery, which is the right call for real-time telemetry.
Reliable delivery would add back-pressure that is wrong for a
per-tick publish rate.

**Discovery: SIMPLE (multicast)** on domain 0, Fast DDS's default.
Participants find each other via UDP multicast with no central
broker.

**Static linking Fast DDS.** Dynamic linking initially hit a
Windows cross-DLL heap crash: Fast DDS's DLL allocated an
`std::vector` inside its type-registration path, then
ClearanceDDS's DLL tried to free it against UE's `PerModuleInline`
allocator. Different heaps, so the free was undefined behaviour
and crashed. Switched to statically linking
`libfastdds-3.6.lib` + `libfastcdr-2.3.lib` +
`foonathan_memory-0.7.4.lib` + OpenSSL statics into
`UnrealEditor-ClearanceDDS.dll`. One heap, one STL, no mismatch
possible.

## ClearanceRTI: OMG DDS via RTI Connext

Same schema, same wire semantics, second parallel wire on Domain 1
via RTI Connext DDS 7.7.0.

Both DDS runtimes co-exist in the same CLEARANCE process. A
federation observer sees the same six data primitives on both DDS
wire flavours plus the DIS legacy wire simultaneously. Same source
of truth, three parallel wires.

**Why the parallel wire matters.** Fast DDS is the reference
open-source implementation; Connext is the commercial market
leader. They are wire-compatible (both speak OMG RTPS) but ship as
separate runtimes with separate discovery domains and separate
`DomainParticipant` instances. Having a working RTI adapter next
to the Fast DDS one demonstrates the schema is genuinely
vendor-neutral OMG DDS, not accidentally Fast-DDS-specific.

Connext also validates the module boundary discipline. The
`FClearanceRTIPublisher` PImpl hides all `dds::domain::*` and
`dds::pub::*` types from the caller, same as Fast DDS's facade
hides `<fastdds/dds/domain/*>`.

## ClearanceHLA: IEEE 1516-2010 via OpenRTI

CLEARANCE joins as a **federate** in an HLA federation execution
named `CLEARANCE`, publishing the `ATCManagedAircraft` object
class from the CLEARANCE RPR-FOM extension XML with attribute
updates on `Marking`, `EntityIdentifier`, `WorldLocation{X,Y,Z}`,
`SquawkCode`, `FlightPhase`, `ActiveClearance`, and `ATCFacility`.

### RTI runtime

OpenRTI 0.10.0 `rtinode.exe`, vendored under
`Plugins/ClearanceSim/ThirdParty/OpenRTI/bin/`. Standalone process
that federates connect to. Default listen TCP `127.0.0.1:14321`.
Launched from a separate terminal before Join.

### Federation execution

Named `CLEARANCE`, created idempotently on first Join. Subsequent
joins from other federates attach to the existing execution
instead of creating a duplicate.

### Federate

`CLEARANCE-Instructor` is the CLEARANCE-side federate name.
Multiple simultaneous CLEARANCE instances distinguish themselves
by appending a suffix.

### Object class hierarchy

The full path in the FOM Module XML:

```
HLAobjectRoot
 └── BaseEntity
      └── PhysicalEntity
           └── Platform
                └── Aircraft                    (SISO RPR-FOM 2.0)
                     └── ATCManagedAircraft     (CLEARANCE extension)
```

The `ATCManagedAircraft` subclass inherits every RPR-FOM Aircraft
attribute and adds the ATC-specific ones. Extension via subclass,
not modification, so the FOM remains RPR-FOM-conformant.

### Attribute encoding

Every published attribute maps to an rti1516e HLA data type:

| Attribute        | HLA data type       | Semantic                                 |
|------------------|---------------------|------------------------------------------|
| Marking          | HLAopaqueData       | 11-char ASCII callsign                   |
| EntityIdentifier | HLAfixedRecord      | {Site, App, Entity} triple, all 16-bit   |
| WorldLocationX/Y/Z | HLAfloat64BE      | ECEF metres, big-endian doubles          |
| SquawkCode       | HLAinteger16BE      | Mode A / 3 SSR code, big-endian short    |
| FlightPhase      | FlightPhaseEnum     | CLEARANCE's own EFlightPhase enum        |
| ActiveClearance  | HLAunicodeString    | Human-readable ATC clearance text        |
| ATCFacility      | HLAunicodeString    | ICAO facility identifier (e.g. EGLL_TWR) |

### The federate loop

`FClearanceHLAFederate::Impl` owns:
- `RTIambassadorFactory` and the `RTIambassador` singleton
- A `NullFederateAmbassador`-derived callback receiver (empty for
  publish-only MVP, wired up when subscribe support lands)
- Object class handle + attribute handles, resolved at Join by
  string names against the loaded FOM
- Per-callsign `ObjectInstanceHandle` map, registered lazily on
  first update

All rti1516e Exception types are caught and swallowed at the
Impl boundary. Matches DIS best-effort semantics. A
`GLastJoinError` diagnostic string is exposed via a static getter
so the operator UI can surface the failure reason.

## Data flow inside CLEARANCE

CLEARANCE's own types (`FAircraftState`, `FRadarEmission`,
`FWeaponsFireEvent`, `FWeaponsDetonationEvent`, `FRadioTransmitter`,
`FVoiceCommsEvent`) are the source of truth. Each federation
emitter has a `MarshalTo*` helper that reads the CLEARANCE struct
and writes the standard's on-wire form. No federation type is ever
passed as sim-side state; the federation layer is strictly
downstream.

That separation is why any of the four wires can be added or
removed without touching the sim's core loop. It is also why the
same authoritative struct hits every wire without divergence: a
DIS observer sees the aircraft at the same ECEF coordinate as a
DDS observer and an HLA observer, because all three came from the
same source struct on the same tick.

## Vendor SDK integration notes

Getting four independent commercial runtimes to co-exist in one
UE5 process required real toolchain work, not just header includes.

### OpenRTI

Cloned upstream `https://github.com/onox/OpenRTI.git`, built from
source against MSVC 2026 + Windows SDK 10.0.26100. Vendored under
`Plugins/ClearanceSim/ThirdParty/OpenRTI/`. Bugs and fixes:

- **CMake 4.x compat.** OpenRTI's top-level `CMakeLists.txt`
  called `project()` before `cmake_minimum_required(VERSION 2.8.12)`,
  and CMake 4 removed compat for <3.5. Patched to insert
  `cmake_minimum_required(VERSION 3.5)` as line 1.
- **VS 2026 generator.** Default generator "Visual Studio 17 2022"
  fails on VS 18. Used `-G "Visual Studio 18 2026"`.
- **PowerShell arg-splitting.** `-DCMAKE_POLICY_VERSION_MINIMUM=3.5`
  got split on `.` under PowerShell's argument parser. Used the
  arg-array pattern `@("-D...=3.5")` to force single-token
  pass-through.
- **`auto_ptr` vs `unique_ptr` ABI mismatch (the sneaky one).**
  `rti1516e/RTI/SpecificConfig.h` gates `RTI_UNIQUE_PTR` on
  `__cplusplus < 201703L`. MSVC reports `__cplusplus == 199711L`
  by default even in C++17 mode unless `/Zc:__cplusplus` is set.
  OpenRTI built without the flag exported `createRTIambassador`
  returning `std::auto_ptr<RTIambassador>`, but the consumer (UE,
  C++20) saw `std::unique_ptr` in the header. Link failed at
  RTIambassador creation. Fixed by rebuilding OpenRTI with
  `CXXFLAGS = /EHsc /Zc:__cplusplus` so header and DLL agree on
  unique_ptr.
- **`<windows.h>` pollution from rti1516e headers.** Same class of
  problem as RTI Connext: `<windows.h>` transitively leaks into UE
  headers and breaks `UE::Cook::FCookDependency`. Fixed by
  wrapping every OpenRTI include with UE's
  `AllowWindowsPlatformTypes.h` + `THIRD_PARTY_INCLUDES_START` +
  `THIRD_PARTY_INCLUDES_END` + `HideWindowsPlatformTypes.h` guard
  set.

### Fast DDS

- **Cross-DLL heap mismatch.** Detailed under ClearanceDDS above.
  Resolved by static-linking Fast DDS, fastcdr,
  foonathan_memory, and OpenSSL into `UnrealEditor-ClearanceDDS.dll`.

### RTI Connext

- **Windows.h pollution.** Same `AllowWindowsPlatformTypes.h` guard
  pattern as OpenRTI, applied around every RTI Connext include.
- **DLL delay-load.** RTI's own DLLs delay-load into
  `UnrealEditor-ClearanceRTI.dll` so a Connext-less machine still
  loads the CLEARANCE editor cleanly (the RTI wire just fails
  gracefully at Start).

## What this repo does not include

- **Vendor SDKs.** eProsima Fast DDS, RTI Connext DDS, OpenRTI.
  Each carries its own licence. They are linked at CLEARANCE
  build time from `Plugins/ClearanceSim/ThirdParty/`.
- **Runtime QoS and discovery config beyond schema-level defaults.**
  Domain IDs, multicast group addresses, transport tuning all live
  in the parent CLEARANCE project's editor settings.
- **Consumer-side federates.** The video demo uses Wireshark for
  DIS, RTI Administration Console for DDS/RTI, and OpenRTI's
  `rtinode.exe` for HLA. No standalone peer federate is included
  in this repo.
- **The rest of CLEARANCE.** Everything the four wires publish
  (aircraft dynamics, radar sim, comms transcript, weapons events,
  scoring, replay) lives in the parent simulator, not here.
