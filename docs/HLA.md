# HLA (IEEE 1516-2010)

`ClearanceHLA` is the High Level Architecture binding of the
CLEARANCE authoritative tick. Fourth sibling to DIS, Fast DDS, and
RTI Connext. Publishes an `ATCManagedAircraft` object class into a
federation execution over a standard RTI ambassador.

## Standard

IEEE 1516-2010, *Standard for Modeling and Simulation (M&S) High
Level Architecture (HLA)*. Covers the Framework and Rules
(1516-2010), Federate Interface Specification (1516.1-2010), and
Object Model Template (1516.2-2010).

## Runtime

OpenRTI 0.10.0, built from source against MSVC 2026 and Windows
SDK 10.0.26100. Vendored under
`Plugins/ClearanceSim/ThirdParty/OpenRTI/` with headers, libs, DLLs,
and the standalone `rtinode.exe` executable that federates connect
to (default `127.0.0.1:14321`).

## Why HLA alongside DDS

HLA is the DoD-mandated federated-simulation standard, with roughly
fifteen years of NATO / MOD / DoD training rig deployment. It
covers ownership management, time management, and declaration
management concerns that DDS does not model at the API level.
Having HLA working live alongside DIS and the two DDS bindings
covers the entire defence M&S standards landscape a training
programme might specify.

## Object model

`ClearanceRPR-FOM.xml` is an RPR-FOM 2.0 derived FOM extension
authored for CLEARANCE. It introduces the `ATCManagedAircraft`
object class under
`HLAobjectRoot.BaseEntity.PhysicalEntity.Platform.Aircraft` with
four ATC-specific attributes:

| Attribute | Data type | Transport | Semantics |
|---|---|---|---|
| `SquawkCode` | `HLAinteger16BE` | `HLAbestEffort` | SSR Mode A/3 code |
| `FlightPhase` | `HLAinteger16BE` | `HLAbestEffort` | Enroute / Approach / Landing / GoAround / Departing / Exiting |
| `ActiveClearance` | `HLAopaqueData` | `HLAreliable` | Encoded active clearance text |
| `ATCFacility` | `HLAopaqueData` | `HLAreliable` | Facility handling the aircraft |

Plus the inherited RPR-FOM `Marking` and `EntityIdentifier`
attributes for identification and the standard `WorldLocationX/Y/Z`
for position.

The mix of `HLAreliable` and `HLAbestEffort` transports demonstrates
the QoS split that a subscribing federate observes: best-effort
attributes batch into one reflection call and reliable attributes
batch into a separate reflection call, per IEEE 1516-2010.

## Module layout

```
Plugins/ClearanceSim/Source/ClearanceHLA/
  ClearanceHLA.Build.cs
  Public/
    ClearanceHLA/
      ClearanceHLAExport.h
      ClearanceHLAFederate.h          engine-free public API
  Private/
    ClearanceHLAModule.cpp
    ClearanceHLAFederate.cpp          rti1516e impl (PImpl)
```

Public API centres on the `AircraftStateWire` POD and six methods on
`FClearanceHLAFederate`:

- `CreateFederation(federation, fomPath)` — idempotent, returns
  success if the federation already exists.
- `Join(federation, federate, fomPath)` — returns a `unique_ptr` to
  a live federate; nullptr on failure (see `GetLastJoinError()`).
- `RegisterAircraftInstance(callsign)` — lazy registration on first
  update, exposed for explicit pre-registration.
- `UpdateAircraftAttributes(state)` — encode plus push the attribute
  map.
- `PublishAircraftState(state)` — register-then-update convenience.
- `Resign()` — clean teardown.

rti1516e Exception types are caught and swallowed (matches DIS
best-effort semantics); a static `GetLastJoinError()` diagnostic
exposes the message text for UI surfacing.

## Runtime integration

`UClearanceHLAEmitter` is the Unreal-side adapter, fourth sibling to
the DIS, Fast DDS, and RTI Connext emitters. Same emit-tick shape,
same Start / Stop lifecycle, same identity fields. Holds an opaque
`FClearanceHLAFederate*` managed manually (raw pointer, same
rationale as `UClearanceRTIEmitter`).

Server RPCs on `AClearanceOperatorPC`:

- `Server_InjectStartHLAJoin(FederationName, FederateName, FomModulePath)`
- `Server_InjectStopHLAJoin()`

Console commands:

- `clearance.hla.join [federation] [federate] [fomPath]`
- `clearance.hla.resign`

`rtinode.exe` must be running before Join. Documented in
`ThirdParty/OpenRTI/README.md`.

## Independent verification

DDS runtimes ship visualisation tools out of the box (RTI Admin
Console for Connext; Fast DDS Monitor for eProsima). HLA does not:
the wire protocol between federates and the RTI is
implementation-specific and undocumented, so Wireshark and generic
monitoring tools cannot dissect it.

The independent evidence for HLA is a second federate:

- **`StandaloneHLASubscriber`** at
  `Plugins/ClearanceSim/StandaloneHLASubscriber/clearance_hla_subscriber.exe`.
  Statically linked to the vendored OpenRTI SDK, joins the CLEARANCE
  federation, subscribes to
  `ATCManagedAircraft.{SquawkCode, FlightPhase, ActiveClearance, ATCFacility}`,
  pumps `evokeMultipleCallbacks` on a 10 ms cycle, prints one line
  per received sample.

Live output sample:

```
[connect] rtinode contact established
[create]  federation exists (fine)
[join]    joined as 'CLEARANCE-Subscriber'
[subscribe] listening for ATCManagedAircraft updates...

[HLA-SUB] #1  BAW101 -> ATCManagedAircraft  Squawk=0    Phase=Enroute Facility=CLR_APP
[HLA-SUB] #2          -> ATCManagedAircraft  Squawk=1200 Phase=Enroute Facility=
[HLA-SUB] #3  AAL102 -> ATCManagedAircraft  Squawk=0    Phase=Enroute Facility=CLR_APP
```

The alternating pattern reflects the FOM's per-attribute
`<transportation>` declarations working end to end.

## Cross-vendor status

OpenRTI accepts the composed FOM and CLEARANCE federates as
expected. Third-party FOM validation against
[Portico](https://github.com/openlvc/portico) currently rejects the
FOM composition during FDD loading. That gap is documented in
[PORTICO_GAP.md](PORTICO_GAP.md) rather than presented as solved
interoperability. The CLEARANCE-provided
[`PorticoFederate/`](../PorticoFederate/) folder contains the
minimum-viable FOM validator used to reproduce the failure.

## Notable design decisions

**Same isolation discipline as DDS bindings.** Pure C++ public API,
rti1516e types behind PImpl, engine-free surface. The Unreal side
is a thin adapter.

**Lazy object registration.** `UpdateAircraftAttributes` registers
the object instance if it does not already exist. The exposed
`RegisterAircraftInstance` allows explicit pre-registration for
scenarios that want to declare the full fleet up front.

**RTI-generated names.** IEEE 1516-2010 requires
`reserveObjectInstanceName` and a callback before the named
`registerObjectInstance` overload will accept the name. CLEARANCE
uses the auto-name overload (`registerObjectInstance(handle)`) and
maintains an `InstanceByCallsign` map locally for O(log N) tick
lookups. Peer federates see RTI-generated names like `HLA1234` in
`discoverObjectInstance` but the class and attribute values are what
matter for a training exercise.

## Known limitations

- Publish-only for v1.0. A subscribing implementation on the
  `UClearanceHLAEmitter` side is designed but not shipped in v1.0.
- Object registration uses RTI-generated names rather than the
  aircraft callsign, for the reason described above. Callsign
  identification travels via the RPR-FOM `Marking` attribute.
- Cross-vendor FOM validation against Portico is not resolved. See
  [PORTICO_GAP.md](PORTICO_GAP.md).
- No time management (TAR / TARA) requested. CLEARANCE joins as a
  publish-only federate under implicit real-time coordination.
- No DDM (Data Distribution Management) subscription filtering.
  Regions are not declared.
