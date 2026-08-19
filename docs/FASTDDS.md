# Fast DDS

`ClearanceDDS` is the eProsima Fast DDS binding of the CLEARANCE
authoritative tick. Same six data primitives as the DIS wire, same
authoritative source struct, different transport and different
representation.

## Standard

- OMG Data Distribution Service (DDS) for Real-Time Systems.
- OMG DDS-RTPS wire protocol 2.5 for interoperability with any
  other DDS 1.4 vendor.
- IDL 4.2 for schema definition.

## Runtime

eProsima Fast DDS 3.6.1, statically linked.

## Topic schema

Six topics, one per data primitive, under a `clearance/` root:

| Topic | Type | Notes |
|---|---|---|
| `clearance/aircraft/state` | `ClearanceDDS::AircraftState` | Full ATC state per aircraft |
| `clearance/weapons/fire` | `ClearanceDDS::WeaponsFireEvent` | Discrete |
| `clearance/weapons/detonation` | `ClearanceDDS::WeaponsDetonationEvent` | Discrete |
| `clearance/radar/emission` | `ClearanceDDS::RadarEmission` | Republished per tick |
| `clearance/comms/transmitter` | `ClearanceDDS::RadioTransmitter` | Republished while active |
| `clearance/comms/signal` | `ClearanceDDS::VoiceCommsEvent` | Discrete |

Continuous state (Aircraft, Radar Emission, Transmitter) is
republished every server tick; discrete events (Fire, Detonation,
Signal) are published when they occur.

The IDL POD types are generated via `fastddsgen` from
`ClearanceDDS/IDL/AirspaceTelemetry.idl`. The wire header
(exercise ID, site ID, application ID, timestamp) is a POD prepended
to every payload so a subscriber can loopback-filter its own
publications.

## Module layout

```
Plugins/ClearanceSim/Source/ClearanceDDS/
  ClearanceDDS.Build.cs
  IDL/
    AirspaceTelemetry.idl             OMG IDL schema
  Public/
    ClearanceDDS/
      ClearancePublisher.h            engine-free public API
      Generated/                      fastddsgen output (typed API)
  Private/
    ClearancePublisher.cpp
    Generated/                        fastddsgen output (impls)
```

Public API centres on `FClearancePublisher`:

- `Create(uint32 DomainId)` factory returning a `TUniquePtr`.
- `PublishAircraftState(...)`, `PublishFireEvent(...)`,
  `PublishDetonationEvent(...)`, `PublishEmission(...)`,
  `PublishTransmitter(...)`, `PublishSignal(...)`.
- `GetTotalPublishedCount()` for rate-sampling in the UI.
- `GetLastCreateError()` static diagnostic for the
  DomainParticipant init path.

Fast DDS runtime types (`DomainParticipant`, `Publisher`,
`DataWriter`, `TypeSupport`) live behind a PImpl in the private
sources; the public header includes only the IDL POD types plus
standard C++.

## Runtime integration

`UClearanceDDSEmitter` is the Unreal-side adapter. Holds the
`FClearancePublisher*`, exposes Start / Stop / EmitStates / identity
setters (Site ID, Application ID, Exercise ID). Simulation controller
owns one instance and calls `EmitStates` from the same authoritative
tick that feeds every other wire.

Receiver counterpart is `UClearanceDDSReceiver`, which owns a
`FClearanceSubscriber`, subscribes to `clearance/aircraft/state`,
filters loopback samples by the WireHeader's Site ID and
Application ID, and enqueues external aircraft to a mutex-guarded
queue drained on the game thread.

Static-linked against Fast DDS to keep a single heap boundary in the
module DLL and avoid cross-DLL STL destructor issues.

## Independent verification

- **Standalone Fast DDS subscriber.** A C++ executable statically
  linked against the same Fast DDS SDK subscribes to
  `clearance/aircraft/state` on the same domain. It receives
  aircraft state as `AircraftState` samples and prints one line per
  update. Independent proof from a separate process that the
  publications are on the wire in the declared IDL shape.
- **Fast DDS Monitor / rtiddsspy equivalents** can enumerate the
  DomainParticipant, its six DataWriters, and their sample counts.
- **Manual verification procedure MP-03** in the CLEARANCE V&V plan
  covers standalone subscriber capture.
- **Wireshark with the RTPS dissector** decodes DATA(p), DATA(w),
  and payload packets on domain multicast. Vendor ID field decodes
  as `eProsima – Fast DDS` for CLEARANCE participants.

## Notable design decisions

**IDL schema shared with the RTI Connext binding.**
`AirspaceTelemetry.idl` is the canonical schema. The RTI binding
uses a renamed copy (`AirspaceTelemetryRTI.idl` under module
`ClearanceRTI`) so both codegen outputs coexist in the same
translation unit without symbol collision, but the field layout and
semantics stay identical. Consequence: a DDS-DDS bridge across
vendors is a field-for-field copy.

**Extended IDL to carry ATC state.** Baseline DDS-native
publications would include only motion primitives. CLEARANCE
publishes the full ATC state peers need for a real ATC picture
(`TrueAffiliation`, `SquawkCode`, `ActiveEmergency`, `FlightPhase`),
field-mapped to mirror the `ATCManagedAircraft` HLA subclass. That
alignment means a DIS-DDS-HLA bridge is a struct-to-struct copy for
every field, not a lossy conversion.

**Ownership protection on inbound updates.** Same discipline as the
DIS receiver: the DDS receiver refuses to overwrite a locally-owned
aircraft. Peer federates can add new external tracks or update ones
they already own; they cannot touch what the local operator owns.

## Automation coverage

DDS-side automation is covered by the general federation and
telemetry tests. The IDL schema field mapping is covered by
`ClearanceRPRFOMMappingTests.cpp`, which locks the ForceId byte
offset used by the DIS PDUs and the ATC state semantics shared with
HLA.

## Known limitations

- No QoS profile customisation exposed to the operator. All topics
  use `RELIABLE_RELIABILITY_QOS` and `VOLATILE_DURABILITY_QOS`. A
  late-joining subscriber sees the next sample, not the last known
  state. Adjustable in the source but not surfaced in the UI.
- Content filtering topics are not used. Loopback filtering happens
  in application code by comparing the WireHeader identity fields.
- No transport security (DDS Security 1.1) profile is applied.
