# DIS (IEEE 1278.1)

`ClearanceDIS` is the in-house byte-level Distributed Interactive
Simulation codec that carries the CLEARANCE authoritative tick out
to the network. It ships as a standalone C++ module (no Unreal
dependencies), consumed both by the game plugin and by external
test executables.

## Standard

IEEE 1278.1-2012, *Standard for Distributed Interactive Simulation
- Application Protocols*. UDP multicast delivery per the DIS
convention.

## PDU coverage

Six PDU types cover the entity motion, weapons, radio, and
electronic warfare strands of a training exercise:

| PDU | Type | Purpose |
|---|---|---|
| Entity State | 1 | Aircraft position, orientation, velocity, dead reckoning, marking |
| Fire | 2 | Weapons release event |
| Detonation | 3 | Weapons detonation event |
| Electromagnetic Emission | 23 | Radar emitter beams, PRF, waveform |
| Transmitter | 25 | Radio transmitter frequency, modulation, power, antenna position |
| Signal | 26 | Voice or data payload carried on the transmitter |

The Entity State PDU carries the RPR-FOM aligned `ForceId` at byte
offset 18 so a peer federate can read affiliation from a raw PDU
capture without additional decoding.

## Module layout

```
Plugins/ClearanceSim/Source/ClearanceDIS/
  ClearanceDIS.Build.cs
  Public/
    ClearanceDIS/                     public C++ API
  Private/
    codec sources
  test/                               google-test coverage
```

Public API surface:

- `BuildEntityStatePDU`, `ParseEntityStatePDU` and equivalents for
  each PDU type.
- Wire header `FDISHeader` (12 bytes, per §5.2.32) with exercise ID,
  PDU type, protocol family, timestamp, PDU length.
- Round-trip helpers used by both the runtime and the automation
  tests.

Every PDU marshaller and parser is exercised by google-test cases
under `ClearanceDIS/test/` and by the Unreal-side automation tests
under `Plugins/ClearanceSim/Source/ClearanceSim/Private/Tests/`.

## Runtime integration

The Unreal side of DIS is `UClearanceDISEmitter` and
`UClearanceDISReceiver`, adapters that own an `FUdpSocket` and call
`ClearanceDIS::BuildX` / `ParseX` per tick. Server-authoritative:
both adapters live on the simulation controller and are stopped when
the session ends.

Sockets:

- Emitter builds through `FUdpSocketBuilder` with
  `.WithMulticastLoopback()` (so same-host peers receive)
  and `.WithMulticastTtl(1)` (so packets stay on the local link, per
  DIS training-range convention).
- Receiver binds the DIS port and calls `.JoinedToGroup(224.0.0.1)`.
  Without the group join, the kernel drops multicast traffic to the
  socket even with loopback set on the sender.

Two-federate host setup: both instances open the instructor panel,
each sets a distinct Site ID via
`Server_InjectSetFederateSiteId(SiteId)`, hits DIS EMIT and RECV,
loads a scenario. Peer aircraft appear on scope tagged with `SITE N`
chips.

## Independent verification

A serialiser reading its own output is not sufficient interoperability
evidence. The DIS wire is verified through third-party tooling:

- **Wireshark** with the DIS dissector enabled on the multicast group.
  Every PDU decodes as its declared type with byte offsets matching
  the spec (§5.2 PDU headers, §5.3 Entity Information/Interaction
  family, §5.4 Warfare family, §5.5 Communications family).
- **Manual verification procedure MP-01** in the CLEARANCE V&V plan
  captures a Wireshark session and steps through the PDU field
  values against the source aircraft state.
- **Third-party DIS tooling exchange.** External DIS-capable
  simulators consume the CLEARANCE Entity State PDUs and render the
  aircraft in their own worlds.

Every one of the six PDU types has a Wireshark dissection reference
attached to the V&V material.

## Notable design decisions

**Zero engine dependency in the codec.** The `ClearanceDIS` module
compiles as pure C++17 and does not include anything from Unreal.
This is what lets the same codec be linked into standalone test
executables and third-party consumers without dragging the engine
along. The Unreal-side adapters are a thin layer bridging into
`FSocket`.

**Cumulative counters live on the emitter and receiver.**
`LastPacketsSent` and `LastPacketsReceived` are monotonic across the
run, reset only on `Start()`, not on every `Poll()` call. Panel
rate-sampling in the instructor UI computes deltas over one-second
windows and clamps negative deltas (from a counter reset on Stop) to
zero so the panel reads `0/s` after teardown rather than a garbage
value.

**Ownership protection on inbound updates.** The receiver refuses to
overwrite a locally-owned aircraft (one with `bIsExternal == false`).
Two federates on the same scenario cannot clobber each other's
authoritative state; each side sees the peer's aircraft as external
display-only tracks.

## Automation coverage

DIS-side automation lives under
`Plugins/ClearanceSim/Source/ClearanceSim/Private/Tests/`:

- `ClearanceDISEmissionTests.cpp` (REQ-DIS-011 through 014).
  Emission PDU round-trip and malformed input rejection.
- `ClearanceDISFireDetonationTests.cpp` (REQ-DIS-005 through 010).
  Fire and Detonation PDU round-trips.
- `ClearanceDISSignalTests.cpp` (REQ-DIS-019 through 022). Signal
  PDU padding and operator-entity routing.
- `ClearanceDISTransmitterTests.cpp` (REQ-DIS-015 through 018).
  Transmitter PDU round-trip.

Full mapping in the main-repo
[Requirements](https://github.com/abdullahabduljabbarab/CLEARANCE/blob/main/Docs/Verification/Requirements.md).

## Known limitations

- The codec covers six PDU types. It does not implement the full
  IEEE 1278.1 PDU inventory (Data, Comment, Repair Request,
  Aggregate State, Environmental Process, etc.). The subset covers
  the training exercise strands that CLEARANCE actually generates.
- Dead reckoning is limited to DRM(FPW) and DRM(RPW) for aircraft;
  higher-order dead reckoning models are not implemented.
- Encryption per IEEE 1278.1 §5.5.2 Encryption Header is not
  supported. All Signal PDUs are transmitted with Encryption
  Algorithm 0 (No Encryption).
