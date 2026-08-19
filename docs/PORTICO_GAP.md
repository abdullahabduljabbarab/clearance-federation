# Portico compatibility gap

CLEARANCE runs against OpenRTI on the HLA wire and the FOM extension
is accepted end-to-end. When the same FOM composition is loaded
against [Portico](https://github.com/openlvc/portico), a second
independent implementation of IEEE 1516-2010, Portico rejects the
FOM during FDD loading.

This document exists so the failure is retained as engineering
evidence rather than hidden. Two RTI implementations of the same
standard disagreeing on FOM parsing is a real thing in HLA practice
and the honest thing to do is document it.

## What works

- `ClearanceRPR-FOM.xml` loads successfully under **OpenRTI 0.10.0**.
- CLEARANCE joins the federation, registers `ATCManagedAircraft`
  objects, publishes attribute updates, and a standalone subscriber
  written against the same OpenRTI SDK receives them cleanly. See
  [HLA.md](HLA.md).
- The FOM composition is well-formed per the IEEE 1516.2-2010
  Object Model Template DTD as far as any generic XML validator can
  determine.

## What does not work

- The minimum-viable Portico validator
  [`PorticoFederate/ClearanceFOMTest.java`](../PorticoFederate/ClearanceFOMTest.java)
  fails to load `ClearanceRPR-FOM.xml`. Portico raises a FOM parsing
  exception during `createFederationExecution` before the federate
  gets a chance to join.
- The failure is reproducible with any Portico release currently
  published on the openlvc GitHub Releases page.
- The Portico exception surfaces the offending XML line number but
  does not identify a specific IEEE 1516.2-2010 clause the FOM
  violates.

## Why this matters

HLA's federation API is standardised. The wire protocol between
federates and the RTI is not: two RTI vendors talk in their own
implementation-specific wire formats, and cross-vendor federation
requires both federates to link the same RTI. Compatibility
between two implementations therefore reduces to whether they
accept the same FOM under the same standard-defined validation
rules.

CLEARANCE demonstrates HLA against OpenRTI. Portico is the natural
comparison point because it is the second open-source IEEE
1516-2010 implementation. A FOM that loads on OpenRTI but not
Portico is not proof CLEARANCE has HLA fully solved. Reporting it
as if it were would be misleading.

## What the CLEARANCE codebase provides

Everything a reader needs to reproduce the failure:

- `PorticoFederate/ClearanceFOMTest.java` — a 40-line Java program
  that loads a FOM path, creates a federation, joins as a federate,
  and exits cleanly. Compiled against
  `$PORTICO_HOME/lib/portico.jar`. See the
  [`PorticoFederate` README](../PorticoFederate/README.md) for
  build and run steps on Windows, macOS, and Linux.
- `PorticoFederate/logs/` — the current Portico exception output
  produced by running the validator against the CLEARANCE FOM.

Any change to the FOM composition should be re-run through the
Portico validator so the status of this gap stays current in the
repository.

## Working theory

The most likely class of cause is a difference between how OpenRTI
and Portico treat FOM inheritance and attribute merging when a
subclass reintroduces attributes with modified transport or order
declarations. RPR-FOM 2.0 uses inheritance heavily; the
`ATCManagedAircraft` extension re-declares transport policies on
attributes that already exist upstream in the RPR-FOM hierarchy.
OpenRTI accepts the merge; Portico appears to reject it.

Confirming and fixing this is scoped work rather than a mystery.
The path forward is either:

1. Split `ATCManagedAircraft` into a strict subclass that does not
   restate any inherited attributes, moving transport declarations
   into a peer FOM module that both implementations accept.
2. Ship a Portico-flavoured FOM alongside the OpenRTI-flavoured
   FOM. Both are valid IEEE 1516-2010 FOM Module XMLs; the
   application picks based on the target RTI vendor.

Neither is scoped inside v1.0. Both are captured here so a future
maintainer can pick this up without re-discovering the failure
from scratch.

## Related material

- [HLA.md](HLA.md) — the working HLA integration against OpenRTI.
- [`PorticoFederate/README.md`](../PorticoFederate/README.md) —
  build and run instructions for the Java validator.
- [DEVLOG.md](../DEVLOG.md) — chronological engineering journal for
  the federation.

## Position

This gap is real. It is not a bug in CLEARANCE and it is not
proof that CLEARANCE cannot federate over HLA. It is evidence that
two independent implementations of the same standard interpret one
part of FOM composition differently, that CLEARANCE is currently
verified against one of them, and that the maintainer knows exactly
where the boundary sits.

Reporting the boundary honestly is more engineering credibility than
claiming CLEARANCE speaks HLA universally would have been.
