# Architecture

How the four federation modules connect to CLEARANCE and to their
respective wire formats.

## One source, four wires

Every module reads the same source of truth: the simulation
controller's per-tick snapshot of aircraft state, radar emissions,
comms traffic, and weapons events. On the sim's server tick each
enabled emitter marshals that snapshot into its wire format and
writes to its transport. No emitter modifies sim state; they're all
read-only downstream consumers.

```
                                +--> ClearanceDIS  -> UDP multicast (IEEE 1278.1)
   Sim tick                     |
   (server)  -> Snapshot -----+ +--> ClearanceDDS  -> RTPS via Fast DDS
                              |
                              | +--> ClearanceRTI  -> RTPS via RTI Connext
                              |
                              +--> ClearanceHLA  -> RPR-FOM object updates via OpenRTI
```

Each emitter is independently start/stoppable from the operator
console. Enabling DDS does not enable DIS; enabling both does not
double-encode the snapshot, they read from the same source struct
and marshal separately.

## ClearanceDIS

Standalone C++ wire codec plus a thin UE plugin module that owns the
UDP socket and the emit scheduler.

**Wire codec** lives in `Private/DISWireFormat.cpp` and
`Public/ClearanceDIS/ClearanceDISPDU.h`. Pure C++, `cstdint`,
`std::vector`, `std::string`. Zero UE dependencies. Test in
`test/test_wire_format.cpp` builds via CMake with no engine
required, so the codec is trivially reusable outside CLEARANCE.

**PDU coverage**:

| PDU type | Purpose                                    |
|----------|--------------------------------------------|
| 1        | Entity State                               |
| 2        | Fire                                       |
| 3        | Detonation                                 |
| 23       | Emission                                   |
| 25       | Transmitter                                |
| 26       | Signal                                     |

All fixed-length fields, big-endian, IEEE 754 doubles, ECEF
coordinates for entity position, per the standard.

**Emitter module** (`Private/ClearanceDISEmitterModule.cpp` and the
`UClearanceDISEmitter` UObject in the parent CLEARANCE project)
handles socket lifetime, target host/port, and per-tick scheduling.
Entity State is a heartbeat, Fire and Detonation are one-shots keyed
by weapons events, Emission is one-per-radar-per-tick, and Signal
is chunked from the voice pipeline.

## ClearanceDDS

Fast DDS publisher and subscriber over RTPS multicast.

**Schema** lives in `IDL/AirspaceTelemetry.idl`. Fast DDS's IDL
compiler generates the C++ pub/sub types at build time. Topics:

| Topic                          | Payload                              |
|--------------------------------|--------------------------------------|
| `clearance/aircraft/state`     | AircraftState                        |
| `clearance/radar/emission`     | EmissionSnapshot                     |
| `clearance/radio/transmitter`  | TransmitterState                     |
| `clearance/weapons/fire`       | FireEvent                            |
| `clearance/weapons/detonation` | DetonationEvent                      |

Publisher runs on the sim tick, subscriber runs in the same process
so the federation demo works out of the box without a peer sim.
Real deployments swap the subscriber for a remote peer on the same
domain.

## ClearanceRTI

Same schema as ClearanceDDS, published through RTI Connext DDS
instead of Fast DDS. Two independent wires publishing the same
sim state at the same time, which is the pattern for demonstrating
that the schema is vendor-neutral OMG DDS and not accidentally
Fast-DDS-specific.

RTI Administration Console discovers the participant, walks the
Publisher, and lists the six DataWriters live during the federation
demo.

## ClearanceHLA

OpenRTI federate joining an HLA-Evolved federation. Uses SISO
RPR-FOM 2.0 (Real-time Platform Reference FOM) as the base object
model, with a CLEARANCE-specific FOM Module XML extending it for
sim-specific attributes.

**Object flow**: aircraft in the sim map to
`BaseEntity.PhysicalEntity.Platform.Aircraft` in RPR-FOM, updated
each tick with published attributes matching the object class.
Interactions cover Fire, Detonation, MunitionDetonation, and
comms events per the RPR-FOM interaction hierarchy.

FOM Module XML is authored to the IEEE 1516-2010 schema so it
validates against the standards-body XSD without modification.

## Data flow inside CLEARANCE

CLEARANCE's own types (`FAircraftState`, `FRadarEmission`,
`FWeaponsFireEvent` and friends) are the source of truth. Each
federation emitter has a `MarshalTo*` helper that reads the
CLEARANCE struct and writes the standard's on-wire form. No
federation type is ever passed as sim-side state; the federation
layer is strictly downstream.

That separation is why any of the four wires can be added or
removed without touching the sim's core loop.

## What this repo doesn't include

- The vendor SDKs (Fast DDS, RTI Connext, OpenRTI). Each carries
  its own licence; they're linked at CLEARANCE build time.
- Runtime QoS / discovery config beyond schema-level defaults.
  Domain IDs, multicast group addresses, transport tuning all
  live in the CLEARANCE editor project settings.
- The consumer side (peer federate, HLA RTIG, DDS Spy). The video
  demo uses Wireshark for DIS, RTI Admin Console for DDS/RTI, and
  OpenRTI's console for HLA.
