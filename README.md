# clearance-federation

Four federation-standard publisher modules from CLEARANCE, a UE5 air
traffic control and defence training simulator I built. Each module
wraps a different federation standard on top of the same sim tick.

This repo is a read-only mirror of the modules as they live inside
CLEARANCE. It doesn't build on its own. It's here so the architecture
is visible without navigating the full game project.

Companion Model-Based Design repos from the same simulator:

- Simulink autopilot: https://github.com/abdullahabduljabbarab/autopilot-mbd
- Simulink radar: https://github.com/abdullahabduljabbarab/radar-mbd

## Modules

| Module         | Standard          | Runtime          | What it publishes                                        |
|----------------|-------------------|------------------|----------------------------------------------------------|
| `ClearanceDIS` | IEEE 1278.1       | in-house codec   | Entity State, Emission, Fire, Detonation, Signal, Transmitter PDUs over UDP multicast |
| `ClearanceDDS` | OMG DDS           | Fast DDS         | AircraftState, EmissionSnapshot, TransmitterState, weapons events over RTPS |
| `ClearanceRTI` | OMG DDS           | RTI Connext DDS  | Same schema as ClearanceDDS, second wire for RTI Connext demos |
| `ClearanceHLA` | IEEE 1516-2010    | OpenRTI          | HLA-Evolved federate, RPR-FOM 2.0 via FOM Module XML     |

All four run at once, off the same tick, publishing the same
underlying sim state to four independent wires. Any of them can be
started or stopped independently.

## Layout

```
clearance-federation/
  ARCHITECTURE.md
  LICENSE
  ClearanceDIS/
    Private/     codec implementation
    Public/      PDU structs, wire API
    test/        standalone CMake test, no UE dependency
  ClearanceDDS/
    IDL/         AirspaceTelemetry.idl schema
    Private/
    Public/
  ClearanceRTI/
    IDL/
    Private/
    Public/
  ClearanceHLA/
    Private/
    Public/
```

## Standards

- IEEE 1278.1-2012 (DIS Application Protocols)
- OMG DDS 1.4
- OMG DDS-RTPS 2.5
- OMG DDS-XTypes 1.3
- IEEE 1516-2010 (HLA-Evolved)
- SISO-STD-001-2015 (RPR-FOM 2.0)

## Video walkthrough

Federation stack running live against CLEARANCE, Wireshark decoding
1278.1 packets, RTI Admin Console discovering the DDS participant:

*link after upload*

## License

MIT, see [`LICENSE`](LICENSE). Vendor SDKs (Fast DDS, RTI Connext,
OpenRTI) carry their own licences and are not vendored here.
