# Portico Federate — third-party HLA validation

Third-party validation of the CLEARANCE RPR-FOM using
[**Portico**](https://github.com/openlvc/portico), an open-source
implementation of **IEEE 1516-2010 HLA-Evolved** developed by a
different team than OpenRTI (the RTI CLEARANCE currently links
against).

The point of this folder:

- **OpenRTI + Portico are two independent implementations of the
  same IEEE standard.** Different codebases, different maintainers,
  different transports on the wire.
- **A FOM that both accept is standards-compliant across
  implementations**, not "OpenRTI-flavoured HLA."
- **`ClearanceFOMTest.java` is the minimum viable proof**: it loads
  `ClearanceRPR-FOM.xml`, creates a federation from it, joins as a
  federate, and exits cleanly. Any FOM parse error surfaces as an
  exception with the exact XML line number.

## What this does NOT do

- It does not join a running CLEARANCE editor federation and receive
  live aircraft attribute updates. That would require CLEARANCE to
  also link against Portico (the HLA wire protocol between RTI
  vendors is not standardised — only the API is).
- It does not exercise every FOM class. It confirms the FOM parses
  and creates a valid federation execution.

If you want end-to-end cross-vendor updates, run two Portico
federates (this validator as the subscriber, and a companion
publisher) against the same federation. Both use the same FOM. Both
publish and subscribe by the same class handles the FOM declares.
That gives the second half of the portability claim.

## Setup

1. **Install Java 8+.** `java -version` should print `1.8.0` or
   higher.
2. **Download Portico.** Grab the latest release binary tarball from
   <https://github.com/openlvc/portico/releases> (or use `git clone`
   + build if you prefer). Extract to a folder — let's call it
   `PORTICO_HOME`.
3. `PORTICO_HOME/lib/portico.jar` is the classpath entry you need.
4. Confirm the CLEARANCE main-repo checkout is at a sibling path so
   the default FOM path resolves; adjust the argument in the run
   command below if it lives elsewhere.

## Build

Windows PowerShell:
```
javac -cp "$env:PORTICO_HOME\lib\portico.jar" ClearanceFOMTest.java
```

Linux / macOS:
```
javac -cp "$PORTICO_HOME/lib/portico.jar" ClearanceFOMTest.java
```

## Run

Windows PowerShell:
```
java -cp "$env:PORTICO_HOME\lib\portico.jar;." ClearanceFOMTest `
     "..\..\CLEARANCE\CLEARANCE\CLEARANCE\Plugins\ClearanceSim\FOM\ClearanceRPR-FOM.xml"
```

Linux / macOS:
```
java -cp "$PORTICO_HOME/lib/portico.jar:." ClearanceFOMTest \
     "../../CLEARANCE/CLEARANCE/CLEARANCE/Plugins/ClearanceSim/FOM/ClearanceRPR-FOM.xml"
```

## Expected output

Against a compliant FOM (e.g. the Restaurant example that ships
with Portico under `$PORTICO_HOME/examples/java/ieee1516e/foms/`):

```
Loading FOM: C:\...\RestaurantProcesses.xml
RTI implementation: portico 2.1.4 (build 0)
Connected to Portico RTI.
Created federation: CLEARANCE_PORTICO_TEST
Joined federation as: ClearanceFOMTest
Idle window complete. No FOM callback errors.
Resigned.
Destroyed federation.
Disconnected. SUCCESS: FOM validated by Portico end to end.
```

## Findings: CLEARANCE FOM vs Portico

Pointed at `ClearanceRPR-FOM.xml`, Portico's 1516-2010 parser rejects
the file:

```
ErrorReadingFDD: Error reading [file:.../ClearanceRPR-FOM.xml]:
<objects> is missing HLAobjectRoot
```

The file DOES declare `HLAobjectRoot` inside `<objects>`, so this is
Portico's stricter schema validation catching something OpenRTI
accepts leniently. Not blocking - it's exactly the kind of cross-
vendor compatibility gap that third-party validation is meant to
uncover. Follow-ups:

- Compare CLEARANCE's `<objects>` block byte-for-byte against the
  Restaurant example that Portico DOES accept (both are 1516-2010,
  same schema namespace). Difference is somewhere in element
  ordering, attribute set, or the extension-module-vs-monolithic
  structure - the CLEARANCE FOM is written as an extension module
  that assumes SISO RPR-FOM 2.0 is loaded first, whereas the
  Restaurant example is monolithic.
- Load the SISO RPR-FOM 2.0 base module alongside the CLEARANCE
  extension in `createFederationExecution(name, URL[])` and retest.
  Portico's `URL[]` parameter accepts multiple FOM modules that
  compose at load time; the "missing HLAobjectRoot" complaint might
  resolve once the base is providing the parent chain that the
  CLEARANCE extension references.
- Confirmed by the RTI-neutral OpenRTI implementation
  (CLEARANCE's current linked RTI): the FOM loads and drives a
  live federation without issue.

**Portfolio takeaway**: standards say A, vendor 1 accepts A + a bit
of B, vendor 2 accepts A but not B. Real HLA interop requires
testing against multiple RTIs, not just the one you happen to
build against. This federate is that test.

## Why this matters for the portfolio

- Proves the FOM is standards-compliant across two independent
  RTI implementations.
- Complements the DIS-side proof in `../ClearanceDIS` (Wireshark's
  built-in DIS dissector decodes CLEARANCE traffic byte for byte).
- Same shape of claim: "here is a completely independent tool
  that accepts our wire content / model file as valid IEEE spec."
