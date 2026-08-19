# Development log

Chronological engineering journal for the four federation wires
integrated into CLEARANCE. Most recent first. Focused on federation
work only; the main simulator's devlog lives at
[CLEARANCE/Docs/DEVLOG.md](https://github.com/abdullahabduljabbarab/CLEARANCE/blob/main/Docs/DEVLOG.md).

Companion per-wire deep dives:

- [docs/DIS.md](docs/DIS.md)
- [docs/FASTDDS.md](docs/FASTDDS.md)
- [docs/RTI_CONNEXT.md](docs/RTI_CONNEXT.md)
- [docs/HLA.md](docs/HLA.md)
- [docs/PORTICO_GAP.md](docs/PORTICO_GAP.md)

---

## 2026-07 — Four-wire federation

### 2026-07-08 — HLA standalone subscriber verifies fourth wire end to end

`StandaloneHLASubscriber` is a companion executable joining the same
CLEARANCE federation from a separate process. It statically links the
vendored OpenRTI SDK, subscribes to
`ATCManagedAircraft.{SquawkCode, FlightPhase, ActiveClearance, ATCFacility}`,
pumps `evokeMultipleCallbacks` on a 10 ms cycle, and prints one line
per received sample.

HLA does not enjoy the introspection tooling that DDS ships with (no
Admin Console, no rtiddsspy equivalent, and Wireshark cannot dissect
the vendor-specific wire protocol). The subscriber is the visible
proof: a second federate written from the same
`FClearanceHLAFederate` codebase, subscribing to the FOM extension,
printing live attribute updates. Full publish → RTI → subscribe round
trip on the fourth wire with only code you can point to in the repo.

The alternating pattern in the output stream reflects the FOM's
per-attribute `<transportation>` declarations: `SquawkCode` and
`FlightPhase` are `HLAbestEffort` so they batch into one reflection
call; `ActiveClearance` and `ATCFacility` are `HLAreliable` so they
batch into a separate reflection call. Different transport groups
delivered separately per the IEEE 1516-2010 spec.

### 2026-07-08 — HLA (IEEE 1516-2010) as the fourth federation wire

Added `ClearanceHLA` as a fourth sibling to `ClearanceDIS`,
`ClearanceDDS`, and `ClearanceRTI`. Same isolation discipline: pure
C++ public API, RTI ambassador types hidden behind PImpl, engine-free
surface. Vendored dependencies live under
`Plugins/ClearanceSim/ThirdParty/OpenRTI/` (headers, libs, DLLs,
`rtinode.exe`).

Public API centres on the `AircraftStateWire` POD and six methods:
`CreateFederation`, `Join`, `RegisterAircraftInstance`,
`UpdateAircraftAttributes`, `PublishAircraftState`, `Resign`. The
impl reaches into rti1516e for the actual work through
`RTIambassadorFactory`, resolves object-class and attribute handles
at Join by string names, and encodes attribute values via
`HLAfloat64BE`, `HLAinteger16BE`, `HLAfixedRecord` (for the
EntityIdentifier triple), and `HLAopaqueData` (for the 11-character
Marking field).

Notable build integration issues resolved during the pass:

- **CMake 4 compatibility.** OpenRTI's top-level CMakeLists calls
  `project()` before `cmake_minimum_required(VERSION 2.8.12)`, and
  CMake 4 removed compatibility for versions earlier than 3.5.
  Patched by inserting `cmake_minimum_required(VERSION 3.5)` at line
  1 and removing the trailing legacy version line.
- **VS 2026 generator.** Default generator "Visual Studio 17 2022"
  fails on VS 18. Built with `-G "Visual Studio 18 2026"`.
- **`auto_ptr` vs `unique_ptr` ABI mismatch.**
  `rti1516e/RTI/SpecificConfig.h` gates `RTI_UNIQUE_PTR` on
  `__cplusplus < 201703L`. MSVC reports `__cplusplus == 199711L` by
  default even in C++17 mode unless `/Zc:__cplusplus` is set. OpenRTI
  built without the flag exported `createRTIambassador` returning
  `std::auto_ptr<RTIambassador>`, but the consumer (Unreal, C++20)
  saw `std::unique_ptr` in the header. Fix: rebuilt OpenRTI with
  `CXXFLAGS = "/EHsc /Zc:__cplusplus"` so the header and DLL agree
  on `unique_ptr`.
- **Windows.h pollution from rti1516e headers.** Same class of
  problem as RTI Connext. Fixed by wrapping every OpenRTI include
  with UE's `AllowWindowsPlatformTypes.h` /
  `THIRD_PARTY_INCLUDES_START` / ...END / `HideWindowsPlatformTypes.h`
  guard set.

Post-Join bugs caught during live verification and fixed:

- **Cross-DLL heap crash in RTI exception catches.** Original catch
  blocks stored `Ex.what()` into a local `std::wstring`. The returned
  string's heap buffer was allocated inside `librti1516e.dll`'s CRT;
  when the local wstring destructed in the ClearanceHLA DLL, UE's
  `PerModuleInline.inl` routed the free through `FMemory::Free`,
  which crashes freeing a non-UE-heap buffer. Fix: never call
  `Ex.what()`; the catch handlers just log which HLA API threw
  without the RTI-side message text.
- **`registerObjectInstance` NameNotReserved throw.** IEEE 1516-2010
  requires calling `reserveObjectInstanceName(name)` and waiting for
  `objectInstanceNameReservationSucceeded` before the named
  `registerObjectInstance(handle, name)` overload will accept the
  name. CLEARANCE was calling the named overload directly with the
  aircraft callsign, so the RTI threw `ObjectInstanceNameNotReserved`
  on every call and `UpdatesTotal` stayed at zero forever. Fix: use
  the auto-name overload `registerObjectInstance(handle)`.
- **Windows DLL load order for OpenRTI.** `librti1516e.dll` and
  `libfedtime1516e.dll` import each other. Windows `LoadLibrary` with
  a full path can't resolve the pair one at a time. Fix: added
  `FPlatformProcess::PushDllDirectory(BinariesDir)` before the loads
  and `PopDllDirectory` after.
- **stderr wide-orientation UB.** Diagnostic logging originally used
  `std::fwprintf(stderr, L"...", ...)`. UE puts `stderr` in
  byte-oriented mode via its own logging; calling wide-orientated
  `fwprintf` on it is undefined behaviour. Fix: routed diagnostics
  through `UE_LOG`.

### 2026-07-08 — RTI Connext DDS as the third federation wire

Added `ClearanceRTI` as a sibling to `ClearanceDDS`, running the same
IDL schema through RTI's commercial runtime (7.7.0, evaluation
license). Discovered by the RTI Administration Console on domain 1
with the CLEARANCE participant tagged
`Real-Time Innovations, Inc. (RTI) – Connext DDS (0x0101)`, six
DataWriters graphed under `clearance/*`. Wireshark on loopback with
filter `rtps.guidPrefix.vendorId == 0x0101` shows continuous DATA(p)
discovery and payload flow.

Build integration issues resolved during the pass:

- **`RTI_UNIX=0` still triggered Unix code paths.** RTI headers use
  `#if defined(RTI_UNIX)` which returns true regardless of value.
  Fix: never define `RTI_UNIX`. Only define `RTI_WIN32`.
- **IDL namespace collision with ClearanceDDS.** Both modules had
  `module ClearanceDDS { ... }` in their IDL, so RTI's generated
  `ClearanceDDS::AircraftState` collided with Fast DDS's. Fix:
  renamed RTI's IDL module to `ClearanceRTI`.
- **Header filename collision.** Both DDS runtimes generated a file
  named `AirspaceTelemetry.hpp` in different include paths. First
  include won and RTI's version was never seen inside the
  ClearanceSim unity build. Fix: renamed the RTI IDL to
  `AirspaceTelemetryRTI.idl` so the generated header lands as
  `AirspaceTelemetryRTI.hpp`.
- **RTI headers leaked Windows.h macros.** Fixed with the same UE
  platform-types guard set used later for OpenRTI.
- **RTI Modern C++ codegen uses public fields.** Fast DDS's codegen
  emits fluent setters (`H.ExerciseId(x)`). RTI's emits POD fields
  (`H.ExerciseId = x`). Fix: rewrote the adapter's type conversions
  to use direct field assignment.
- **UHT-generated `.gen.cpp` chokes on `TUniquePtr<T>` with
  forward-declared T.** Fix: switched to raw pointer with manual
  delete in destructor and BeginDestroy.
- **RTI-generated types were not exported from the DLL.** The `.lib`
  import library had no entries for `AircraftState::AircraftState()`
  etc. Fix: added `PrivateDefinitions.Add("NDDS_USER_DLL_EXPORT")`
  to `ClearanceRTI.Build.cs` so the generated struct decorations
  resolve to `__declspec(dllexport)` when built into this module.
- **Evaluation license.** Modern C++ `DomainParticipant(DomainId)`
  throws `dds::core::Error` without an
  `rti_license.dat`. Handled with `catch (const dds::core::Exception&)`
  in `Init()`, exposing a `GetLastCreateError()` accessor. License
  location controlled via the `RTI_LICENSE_FILE` environment
  variable per RTI convention.

Static-linked against RTI's `nddscpp2z.lib`, `nddscz.lib`, and
`nddscorez.lib` from the VS2017 flavour of the 7.7.0 SDK; same
static-link pattern the ClearanceDDS module uses for Fast DDS so
there is a single heap in the module DLL and no cross-DLL STL
boundary. RTI SDK path is overridable via the `NDDSHOME` environment
variable (RTI's own convention).

### 2026-07-08 — Two-federate DIS federation live on one host

Closes out the DIS milestone. Two Play-Standalone CLEARANCE
processes on the same host now share an airspace picture over DIS
and DDS wires simultaneously.

Transport bug fixes:

- Emitter socket had `SO_BROADCAST` enabled but not
  `IP_MULTICAST_LOOP`. Sending to the default host multicast group
  `224.0.0.1` produced no packets a same-host peer could receive.
  Fix: added `.WithMulticastLoopback()` and `.WithMulticastTtl(1)`
  to the `FUdpSocketBuilder`.
- Receiver bound the port but never joined the multicast group.
  Even with loopback fixed, `IP_ADD_MEMBERSHIP` is required or the
  OS drops multicast traffic to the socket. Fix: added
  `.JoinedToGroup(224.0.0.1)` to the receiver's builder.

Replication fix:

- Panel getters were reading
  `CachedController->GetDISEmitter()->GetLastPacketsSent()` and
  equivalents, but `DISEmitter`, `DISReceiver`, `DDSEmitter`,
  `DDSReceiver` were `UPROPERTY()` without `Replicated`. Client-side
  proxy saw null subobject pointers, so every getter short-circuited
  to zero. Fix: eight new replicated fields on
  `AClearanceSimulationController` (`RepDISPacketsSent`,
  `RepDISPacketsReceived`, `RepDDSPacketsSent`, `RepDDSPacketsReceived`,
  `bRepDISEmitting`, `bRepDISReceiving`, `bRepDDSEmitting`,
  `bRepDDSReceiving`). Server tick mirrors the subobject values into
  these fields every frame. Panel getters read the replicated
  fields directly. Works in any client/server topology.

### 2026-07-07 — Full two-federate DIS and DDS federation with ownership

Ownership protection landed on both DIS and DDS receivers. Two
federates on the same scenario with matching callsigns would
previously clobber the operator's own classifications and injected
emergencies with the peer's default state. New guard:
`GetAircraftState(Callsign).bIsExternal == false` refuses the
inbound update, so peers can only add new external tracks or update
ones they already own.

Extended the `AirspaceTelemetry` IDL to carry the full ATC state
peers need for a real ATC picture (`TrueAffiliation`, `SquawkCode`,
`ActiveEmergency`, `FlightPhase`), field-mapped to mirror the
`ATCManagedAircraft` subclass in the shipped `ClearanceRPR-FOM.xml`.
A DIS-DDS-HLA bridge is now a struct-to-struct copy for every
field.

New `int32 OwnerSiteId` on `FAircraftState`: local aircraft show an
`OWN` chip in the instructor list, external aircraft show
`SITE N` chips with the peer's Site ID from the wire.

### 2026-07-07 — RPR-FOM extension XML shipped

`ClearanceRPR-FOM.xml`, an RPR-FOM derived HLA FOM extension
introducing the `ATCManagedAircraft` object class with attributes
`SquawkCode`, `FlightPhase`, `ActiveClearance`, and `ATCFacility`.
Attribute transportation declarations mix `HLAreliable` and
`HLAbestEffort` to demonstrate the QoS split visible to a subscribing
federate.

### 2026-07-07 — Fast DDS integration

`ClearanceDDS` publishes typed DDS topics generated from IDL over
eProsima Fast DDS / RTPS. Standalone consumers built at the same
time provide independent evidence outside the Unreal process.

### 2026-07-06 — DIS protocol layer isolation

Split the DIS codec into its own `ClearanceDIS` module with a pure
C++ public API and no Unreal dependencies. Enables the same codec to
be used by test executables and standalone tooling without pulling
in the engine.

### 2026-07-06 — DIS PDU family expansion

Added Emission (Type 23), Fire (Type 2), Detonation (Type 3), and
Signal (Type 26) PDUs alongside the existing Entity State. Six PDU
types cover the entity motion, weapons, radio, and electronic
warfare strands of a training exercise.

### 2026-07-06 — Transmitter PDU (Type 25)

Radio Communications family completed with the Transmitter PDU.
Covers frequency, modulation, transmit power, and the operator
antenna position so a peer federate can render radio activity
visually.

### 2026-07-06 — DIS emitter and receiver in CLEARANCE

The first federation wire wired into the sim. Server-authoritative
emitter runs off the same tick as everything else and marshals the
per-tick snapshot into DIS PDUs on UDP multicast. Receiver on a
paired socket subscribes to the same multicast group and enqueues
inbound state for game-thread application.
