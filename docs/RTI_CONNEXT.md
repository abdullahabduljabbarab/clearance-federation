# RTI Connext DDS

`ClearanceRTI` is the RTI Connext DDS binding of the CLEARANCE
authoritative tick, sitting in parallel with the Fast DDS binding.
Same IDL schema, same authoritative source struct, different vendor
runtime.

## Standard

- OMG Data Distribution Service (DDS) for Real-Time Systems.
- OMG DDS-RTPS wire protocol 2.5.
- Same IDL schema as the Fast DDS binding.

## Runtime

RTI Connext DDS 7.7.0, evaluation license. Static-linked against
`nddscpp2z.lib`, `nddscz.lib`, and `nddscorez.lib` from the VS2017
flavour of the SDK.

## Why a second DDS vendor

DDS is a specification, not a single implementation. Real defence
integration programmes routinely combine an open-source DDS vendor
(Fast DDS, OpenDDS) with a commercial vendor (RTI Connext, ADLINK
OpenSplice). The pair verifies that CLEARANCE's DDS surface is
interoperable across vendors on the RTPS wire and that the
architecture does not accidentally depend on a single vendor's
non-standard behaviour.

RTI Connext is also the commercial DDS runtime that BAE Warton's
Tempest, Lockheed Martin's F-35 pipeline, and Boeing's E-7 programme
actually ship on. Having both bindings live in one process makes the
architecture legible to the same programme managers who read
graduate portfolios.

## Topic schema

Identical to the Fast DDS binding: six topics under `clearance/*`,
same IDL POD types, same wire header layout. The RTI IDL module is
renamed to `ClearanceRTI` and the generated header file to
`AirspaceTelemetryRTI.hpp` so the two codegen outputs coexist inside
the ClearanceSim unity build without collision.

## Module layout

```
Plugins/ClearanceSim/Source/ClearanceRTI/
  ClearanceRTI.Build.cs
  IDL/
    AirspaceTelemetryRTI.idl          module ClearanceRTI { ... }
  Public/
    ClearanceRTI/
      ClearanceRTIPublisher.h         engine-free public API
  Private/
    ClearanceRTIPublisher.cpp
    Generated/                        rtiddsgen output
```

Public API mirrors the Fast DDS binding shape:

- `FClearanceRTIPublisher::Create(uint32 DomainId)`
- Per-topic publish methods
- `GetTotalPublishedCount()`
- `GetLastCreateError()` static diagnostic

RTI runtime types (`dds::domain::DomainParticipant`,
`dds::pub::Publisher`, `dds::pub::DataWriter`) live behind PImpl.

## Runtime integration

`UClearanceRTIEmitter` is the Unreal-side adapter, third sibling to
`UClearanceDISEmitter` and `UClearanceDDSEmitter`. Same emit-tick
shape, same Start / Stop lifecycle, same identity fields.
`SimulationController` owns one instance and calls `EmitStates` from
the same authoritative tick that feeds every other wire.

Default domain is 1, so RTI sits next to Fast DDS (default domain 0)
without stepping on discovery. Both can run concurrently in the same
process.

The Fast DDS emitter's `TUniquePtr<FClearancePublisher>` pattern does
not compile for the RTI emitter, because the UHT-generated
`.gen.cpp` instantiates the destructor in a translation unit that
sees only the forward declaration of the publisher. Switched to a
raw pointer with manual delete in the destructor and `BeginDestroy`.

## Independent verification

- **RTI Administration Console** discovers the CLEARANCE
  DomainParticipant on domain 1, graphs the six DataWriters routed
  to their topic columns under `clearance/*`, and stamps the vendor
  in the Entity Info panel as
  `Real-Time Innovations, Inc. (RTI) – Connext DDS (0x0101)`.
- **Wireshark on loopback** with filter
  `rtps.guidPrefix.vendorId == 0x0101` shows continuous DATA(p)
  discovery and payload flow.
- **PublishedTotal counter** in the CLEARANCE Output Log ticks past
  1000 samples within the first few seconds of an EMIT session.
- **Manual verification procedure MP-02** in the CLEARANCE V&V plan
  captures the Admin Console session and steps through the
  discovered writers against the source aircraft state.

## Build integration notes

Getting RTI Connext to link cleanly against a UE plugin module took
the bulk of the initial ship time. The consolidated list of blockers
and fixes lives in [DEVLOG.md](../DEVLOG.md), but the design-relevant
takeaways are:

- **`RTI_UNIX` gate uses `#if defined`, not `#if`.** Define
  `RTI_WIN32` only. Do not define `RTI_UNIX`, even to zero.
- **IDL and header names must not collide.** Two DDS vendors
  generating headers into the same include path collide by filename;
  renaming the IDL module and the generated header prevents this.
- **RTI Modern C++ codegen uses public POD fields, not fluent
  setters.** Direct field assignment where the Fast DDS binding
  would use setter calls.
- **`NDDS_USER_DLL_EXPORT` in `PrivateDefinitions`.** Without it, the
  generated struct decorations do not resolve to
  `__declspec(dllexport)` and the import library is empty of
  generated-type symbols.
- **Windows.h leakage via RTI headers.** Same UE platform-types
  guard set as the OpenRTI includes.
- **Evaluation license.**
  `DomainParticipant(DomainId)` throws `dds::core::Error` without an
  `rti_license.dat`. Catch handler exposes the message via
  `GetLastCreateError()`. `RTI_LICENSE_FILE` environment variable
  controls path per RTI convention.

## Notable design decisions

**Static link, not shared.** Same rationale as the Fast DDS binding:
one heap per module DLL, no cross-DLL STL destructor issues,
predictable UE hot-reload behaviour.

**Parallel to Fast DDS, not layered.** Neither binding wraps the
other. They are two independent code paths reading from the same
snapshot and marshalling separately. Enabling both writes twice on
the wire; disabling one has no effect on the other.

**SDK path via `NDDSHOME`.** RTI's own convention. Defaults to
`C:\Program Files\rti_connext_dds-7.7.0`. Set at build time and used
by `ClearanceRTI.Build.cs` for include and library resolution.

## Known limitations

- Requires a valid RTI evaluation or commercial license at runtime.
  Without a license the DomainParticipant throws on creation and
  the emitter reports the error through `GetLastCreateError()` for
  UI surfacing.
- Publish-only for v1.0. A parallel `UClearanceRTIReceiver` mirror
  of the Fast DDS receiver is designed but not shipped in v1.0.
- No RTI Security profile applied.
