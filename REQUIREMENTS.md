# Requirements

Every requirement covered by the CLEARANCE automation test suite,
grouped by domain and traced to the specific test that verifies it.
Each REQ-ID is tagged in a leading comment on the test that owns it,
so the source is authoritative. This doc just tabulates.

The tests themselves live in the parent CLEARANCE simulator under
`Plugins/ClearanceSim/Source/ClearanceSim/Private/Tests/`. This
showcase repo mirrors the requirements structure so the traceability
story is visible without cloning the whole simulator.

Companion to [`V_AND_V_PLAN.md`](V_AND_V_PLAN.md), which is the
strategy behind how the requirements get verified.

## Numbering scheme

```
REQ-<DOMAIN>-<###>
```

| Prefix        | Domain                                                  |
|---------------|---------------------------------------------------------|
| `REQ-DIS-`    | IEEE 1278.1 DIS wire-format compliance                  |
| `REQ-FED-`    | Federation, RPR-FOM, cross-vendor affiliation mapping   |
| `REQ-COMMS-`  | ATC comms: phraseology, readback, instruction gate      |
| `REQ-SAFETY-` | Doctrinal separation, wake, envelope compliance         |
| `REQ-SCORE-`  | Scoring and difficulty adjustment                       |
| `REQ-SIM-`    | Session recorder, playback, checkpoint                  |
| `REQ-RADAR-`  | Monostatic radar range equation and detection physics   |

Numbers ascend inside a domain and are never reused. Deprecated
REQ-IDs stay in place with a `[DEPRECATED]` marker.

## REQ-DIS: IEEE 1278.1 wire-format compliance

Verified by the tests under `ClearanceDIS*Tests.cpp`. Every
requirement here traces to a specific section of IEEE 1278.1-2012.

| ID          | Requirement                                                                                              | Verified by                                    | Source              |
|-------------|----------------------------------------------------------------------------------------------------------|------------------------------------------------|---------------------|
| REQ-DIS-001 | Entity State PDU serialises to exactly 144 bytes for a valid entity with no articulations                | `Clearance.DIS.EntityStatePDU.Roundtrip`       | IEEE 1278.1 §7.3.4  |
| REQ-DIS-002 | Entity State PDU header carries PDU type 1 and protocol family 1 (Entity Information)                    | `Clearance.DIS.EntityStatePDU.Roundtrip`       | IEEE 1278.1 §5.2    |
| REQ-DIS-003 | Entity State PDU header carries protocol version 7 (IEEE 1278.1-2012)                                    | `Clearance.DIS.EntityStatePDU.Roundtrip`       | IEEE 1278.1 §5.2.24 |
| REQ-DIS-004 | Entity State PDU writes ForceId as a single uint8 at spec offset 18                                      | `Clearance.Federation.RPRFOM.ForceId.*`        | IEEE 1278.1 §7.3.4.6|
| REQ-DIS-005 | Fire PDU serialises to exactly 96 bytes                                                                  | `Clearance.DIS.FirePDU.Roundtrip`              | IEEE 1278.1 §7.3.3  |
| REQ-DIS-006 | Fire PDU round-trips firing entity, target entity, munition entity, event number, munition kind, warhead kind, fuse kind, quantity, range, world location, and velocity byte-exactly | `Clearance.DIS.FirePDU.Roundtrip`              | IEEE 1278.1 §7.3.3  |
| REQ-DIS-007 | Fire PDU parser rejects buffers shorter than the fixed 96 bytes                                          | `Clearance.DIS.FirePDU.MalformedRejection`     | IEEE 1278.1 §7.3.3  |
| REQ-DIS-008 | Detonation PDU serialises to exactly 104 bytes for a proximate-detonation result                         | `Clearance.DIS.DetonationPDU.Roundtrip`        | IEEE 1278.1 §7.3.4  |
| REQ-DIS-009 | Detonation PDU round-trips firing / target / munition entity IDs matching the paired Fire event          | `Clearance.DIS.DetonationPDU.Roundtrip`        | IEEE 1278.1 §7.3.4  |
| REQ-DIS-010 | Detonation PDU parser rejects buffers shorter than the fixed 104 bytes                                   | `Clearance.DIS.DetonationPDU.MalformedRejection` | IEEE 1278.1 §7.3.4|
| REQ-DIS-011 | Emission PDU serialises the fixed 100-byte header plus one variable-length track/jam block per painted entity | `Clearance.DIS.EmissionPDU.Roundtrip`          | IEEE 1278.1 §7.6.2  |
| REQ-DIS-012 | Emission PDU round-trips emitter name, function, frequency low/high, ERP, PRF, pulse width, and beam azimuth byte-exactly | `Clearance.DIS.EmissionPDU.Roundtrip`          | IEEE 1278.1 §7.6.2  |
| REQ-DIS-013 | Emission PDU enumerates every painted entity's Entity ID in the Track/Jam list                           | `Clearance.DIS.EmissionPDU.Roundtrip`          | IEEE 1278.1 §7.6.2  |
| REQ-DIS-014 | Emission PDU parser rejects buffers with truncated track/jam blocks                                      | `Clearance.DIS.EmissionPDU.MalformedRejection` | IEEE 1278.1 §7.6.2  |
| REQ-DIS-015 | Transmitter PDU serialises to exactly 104 bytes                                                          | `Clearance.DIS.TransmitterPDU.Roundtrip`       | IEEE 1278.1 §7.7.2  |
| REQ-DIS-016 | Transmitter PDU round-trips radio entity ID, transmit state, input source, modulation, transmit frequency, and transmit power | `Clearance.DIS.TransmitterPDU.Roundtrip`       | IEEE 1278.1 §7.7.2  |
| REQ-DIS-017 | Transmitter PDU encodes operator entities as ForceId 0 with entity number 60000 (`kOperatorGroundStationEntity`) | `Clearance.DIS.TransmitterPDU.OperatorEntity`  | CLEARANCE convention|
| REQ-DIS-018 | Transmitter PDU parser rejects buffers shorter than the fixed 104 bytes                                  | `Clearance.DIS.TransmitterPDU.MalformedRejection` | IEEE 1278.1 §7.7.2|
| REQ-DIS-019 | Signal PDU header is exactly 32 bytes; payload is padded to a 32-bit boundary per §7.7.3                  | `Clearance.DIS.SignalPDU.PaddingBoundary`      | IEEE 1278.1 §7.7.3  |
| REQ-DIS-020 | Signal PDU round-trips radio reference ID, encoding class, TDL type, sample rate, and payload bytes      | `Clearance.DIS.SignalPDU.Roundtrip`            | IEEE 1278.1 §7.7.3  |
| REQ-DIS-021 | Signal PDU routes to the operator ground-station entity for operator-side voice transmissions            | `Clearance.DIS.SignalPDU.OperatorEntity`       | CLEARANCE convention|
| REQ-DIS-022 | Signal PDU parser rejects buffers with declared payload length exceeding the buffer bounds               | `Clearance.DIS.SignalPDU.MalformedRejection`   | IEEE 1278.1 §7.7.3  |

## REQ-FED: federation affiliation mapping

DIS ForceId values are inherited by SISO RPR-FOM 2.0 for HLA, so
drift in these mappings breaks federation with any conforming
third-party sim (KDIS, MAK VR-Forces, VBS4, Portico test federates,
commercial RTIs).

| ID          | Requirement                                                                                              | Verified by                                              | Source                     |
|-------------|----------------------------------------------------------------------------------------------------------|----------------------------------------------------------|----------------------------|
| REQ-FED-001 | ForceId 0 represents Other/Unknown affiliation                                                           | `Clearance.Federation.RPRFOM.ForceId.Other`              | IEEE 1278.1 §7.3.4.6       |
| REQ-FED-002 | ForceId 1 represents Friendly affiliation                                                                | `Clearance.Federation.RPRFOM.ForceId.Friendly`           | IEEE 1278.1 §7.3.4.6       |
| REQ-FED-003 | ForceId 2 represents Opposing (Hostile) affiliation                                                      | `Clearance.Federation.RPRFOM.ForceId.Hostile`            | IEEE 1278.1 §7.3.4.6       |
| REQ-FED-004 | ForceId 3 represents Neutral affiliation                                                                 | `Clearance.Federation.RPRFOM.ForceId.Neutral`            | IEEE 1278.1 §7.3.4.6       |
| REQ-FED-005 | Entity State PDU wire encoding writes ForceId byte-exactly at spec offset 18 for every legal value       | `Clearance.Federation.RPRFOM.ForceId.*`                  | IEEE 1278.1 §7.3.4         |
| REQ-FED-006 | Non-standard (extended-enum) ForceId values are preserved on the wire, not clamped to a spec value       | `Clearance.Federation.RPRFOM.ForceId.UnknownPreserved`   | Interop convention         |

## REQ-COMMS: ATC comms and instruction validation

Requirements from the phraseology and instruction-validator layers.
The validator is a stateless gatekeeper: it decides whether an
instruction is physically feasible before the mover ever sees it.

| ID           | Requirement                                                                                              | Verified by                                              | Source                          |
|--------------|----------------------------------------------------------------------------------------------------------|----------------------------------------------------------|---------------------------------|
| REQ-COMMS-001| A valid feasible instruction on a valid aircraft state returns Accepted                                   | `Clearance.Comms.Validator.AcceptedBaseline`             | ICAO Doc 4444 (PANS-ATM)        |
| REQ-COMMS-002| An instruction on an aircraft with `bIsValid=false` returns `Rejected_InvalidCallsign`                   | `Clearance.Comms.Validator.RejectInvalidCallsign`        | CLEARANCE design                |
| REQ-COMMS-003| A system-issued go-around (`bIsGoAround=true`) bypasses envelope checks and always returns Accepted      | `Clearance.Comms.Validator.GoAroundBypasses`             | ICAO safety-override doctrine   |
| REQ-COMMS-004| An instruction to an aircraft in the `Exiting` flight phase returns `Rejected_AircraftExited`            | `Clearance.Comms.Validator.RejectExiting`                | CLEARANCE design                |
| REQ-COMMS-005| An AltitudeChange above the aircraft category's service ceiling returns `Rejected_PhysicallyImpossible`  | `Clearance.Comms.Validator.RejectAltitudeAboveCeiling`   | Aircraft type certification data|
| REQ-COMMS-006| An AltitudeChange below zero ft returns `Rejected_PhysicallyImpossible`                                  | `Clearance.Comms.Validator.RejectAltitudeNegative`       | CLEARANCE design                |
| REQ-COMMS-007| A SpeedChange below the aircraft category's minimum operating speed returns `Rejected_PhysicallyImpossible` | `Clearance.Comms.Validator.RejectSpeedBelowMin`         | Aircraft type certification data|
| REQ-COMMS-008| A SpeedChange above the aircraft category's max operating speed returns `Rejected_PhysicallyImpossible` | `Clearance.Comms.Validator.RejectSpeedAboveMax`         | Aircraft type certification data|
| REQ-COMMS-009| NaN and non-finite (Inf) target values are rejected as `Rejected_PhysicallyImpossible`                   | `Clearance.Comms.Validator.RejectNonFinite`              | IEEE 754 float handling         |
| REQ-COMMS-010| Military airframes (`bIsMilitary=true`) use the fighter envelope (Vmax ~1050 kts, ceiling 50000 ft) instead of the civil wake-category envelope | `Clearance.Comms.Validator.MilitaryEnvelope`             | CLEARANCE design (F-35-ish)     |

## REQ-SAFETY: separation and envelope doctrine

Tuning constants pinned to ICAO doctrine. Monotonic ordering
invariants guard against inversions when someone edits the numbers.

| ID            | Requirement                                                                                              | Verified by                                              | Source                          |
|---------------|----------------------------------------------------------------------------------------------------------|----------------------------------------------------------|---------------------------------|
| REQ-SAFETY-001| Advisory horizontal separation is 8 nm                                                                   | `Clearance.Safety.HorizontalSeparation`                  | ICAO Doc 4444                   |
| REQ-SAFETY-002| Warning horizontal separation is 5 nm                                                                    | `Clearance.Safety.HorizontalSeparation`                  | ICAO Doc 4444                   |
| REQ-SAFETY-003| Critical horizontal separation is 3 nm                                                                   | `Clearance.Safety.HorizontalSeparation`                  | ICAO Doc 4444                   |
| REQ-SAFETY-004| Vertical minimum is 1000 ft (RVSM airspace)                                                              | `Clearance.Safety.VerticalMinimum`                       | ICAO RVSM (Annex 2 App 4)       |
| REQ-SAFETY-005| Wake separation matrix matches ICAO Doc 4444 §5.8: Light-behind-Heavy 6 nm, Medium-behind-Heavy 5 nm, Light-behind-Medium 5 nm, Heavy-behind-Heavy 4 nm, standard minimum 3 nm | `Clearance.Safety.WakeSeparationMatrix`                  | ICAO Doc 4444 §5.8              |
| REQ-SAFETY-006| Alert level thresholds are strictly monotonic: Advisory > Warning > Critical (nm)                        | `Clearance.Safety.HorizontalSeparation`                  | Ordering invariant              |
| REQ-SAFETY-007| Every wake category's max operating speed exceeds its min operating speed and lies within 50..500 kts   | `Clearance.Safety.CategoryPerformance`                   | Aircraft type certification data|
| REQ-SAFETY-008| Military fighter envelope strictly exceeds the Heavy civil category on max operating speed and service ceiling | `Clearance.Safety.CategoryPerformance`                   | F-35 published performance      |
| REQ-SAFETY-009| `GetEffectivePerformance(cat, bIsMilitary)` routes to the fighter envelope when `bIsMilitary=true` and to the wake-category envelope otherwise | `Clearance.Safety.EffectivePerformanceRouting`           | CLEARANCE design                |

## REQ-SCORE: scoring and difficulty

`UClearanceScoring` runs as a plain UObject with no world dependency,
so these requirements verify the reward/penalty table and session
bookkeeping.

| ID           | Requirement                                                                                              | Verified by                                              | Source                          |
|--------------|----------------------------------------------------------------------------------------------------------|----------------------------------------------------------|---------------------------------|
| REQ-SCORE-001| Every `EIncidentType` maps to a point delta matching the scoring table (`Points*` for reward, `Penalty*` for penalty) | `Clearance.Scoring.PointsPerIncident`                    | CLEARANCE scoring policy        |
| REQ-SCORE-002| `LogIncident` appends exactly one `FIncidentRecord` per call to the session log                          | `Clearance.Scoring.IncidentLog`                          | CLEARANCE design                |
| REQ-SCORE-003| `ResetSession` clears score, log, per-category counters, and resets spawn interval to `BaseSpawnIntervalSeconds` | `Clearance.Scoring.ResetSession`                         | CLEARANCE design                |
| REQ-SCORE-004| A `SuccessfulHandoff` shrinks the spawn interval by exactly `DifficultySecondsPerHandled` seconds        | `Clearance.Scoring.DifficultyRamp`                       | CLEARANCE design                |
| REQ-SCORE-005| The spawn interval clamps at `MinSpawnIntervalSeconds` regardless of the number of successful handoffs   | `Clearance.Scoring.DifficultyRamp`                       | CLEARANCE design                |
| REQ-SCORE-006| `GetEfficiency()` returns a value in [0, 100] regardless of the sequence of incidents recorded           | `Clearance.Scoring.RecordInstruction`                    | Bounds invariant                |

## REQ-SIM: session recorder and playback

Recorder captures per-tick snapshots and timestamped events. Testable
without a world; the `ApplySnapshotTo` path (which requires an
AirspaceManager actor) is exercised via integration tests only.

| ID         | Requirement                                                                                              | Verified by                                              | Source                          |
|------------|----------------------------------------------------------------------------------------------------------|----------------------------------------------------------|---------------------------------|
| REQ-SIM-001| `StartRecording()` sets `IsRecording()` true; `StopRecording()` sets it false                            | `Clearance.Recorder.StartStop`                           | CLEARANCE design                |
| REQ-SIM-002| `CaptureSnapshot` appends one snapshot per call while recording; is a no-op when not recording           | `Clearance.Recorder.StartStop`                           | CLEARANCE design                |
| REQ-SIM-003| `GetDurationSeconds()` returns `(last snapshot timestamp - first snapshot timestamp)`; zero for empty timelines | `Clearance.Recorder.Duration`                         | CLEARANCE design                |
| REQ-SIM-004| `FindSnapshotAt(secondsFromStart)` returns the most recent snapshot with absolute time <= `(firstTimestamp + secondsFromStart)`, clamping to the first snapshot on negative input and to the last on overshoots | `Clearance.Recorder.PoseBack`                         | CLEARANCE design                |
| REQ-SIM-005| `FindSnapshotAt` returns `nullptr` only when the timeline is empty                                       | `Clearance.Recorder.PoseBack`                            | CLEARANCE design                |
| REQ-SIM-006| Every field of `FAircraftState` captured in a snapshot is identical to the input under `FindSnapshotAt` at the same time | `Clearance.Recorder.PoseBack`                            | CLEARANCE design                |
| REQ-SIM-007| `LogEvent` appends to the events list while recording; `GetEventsInRange(from, to)` returns events with timestamps inclusively in `[from, to]` | `Clearance.Recorder.EventsInRange`                       | CLEARANCE design                |
| REQ-SIM-008| `ClearRecording` empties snapshots and events but leaves the `IsRecording` flag untouched. Callers who want to halt call `StopRecording()` explicitly | `Clearance.Recorder.Clear`                               | CLEARANCE design                |

## REQ-RADAR: radar range equation

Verified by `ClearanceRadarEquationTests.cpp`. Traces to Skolnik,
*Introduction to Radar Systems*, 3rd ed., ch. 2-4 (the monostatic
pulse-radar equation and single-pulse detection theory).

| ID           | Requirement                                                                                              | Verified by                                       | Source                          |
|--------------|----------------------------------------------------------------------------------------------------------|---------------------------------------------------|---------------------------------|
| REQ-RADAR-001| Received power follows the R^4 range law: doubling range divides received power by 16                    | `Clearance.Radar.Equation.R4RangeLaw`             | Skolnik §2.1                    |
| REQ-RADAR-002| Received power is linear in target radar cross-section (sigma)                                           | `Clearance.Radar.Equation.RcsScaling`             | Skolnik §2.1                    |
| REQ-RADAR-003| Receiver thermal noise floor equals k*T*B*F (Boltzmann * temperature * bandwidth * noise figure)         | `Clearance.Radar.Equation.NoiseFloorKtbf`         | Skolnik §2.4                    |
| REQ-RADAR-004| Wavelength equals c/f (speed of light / frequency). Validated at S-band (2.8 GHz) and X-band (10 GHz)    | `Clearance.Radar.Equation.Wavelength`             | Physics constant                |
| REQ-RADAR-005| Probability of detection at SNR = required-SNR equals 0.5 exactly (logistic centred on threshold)        | `Clearance.Radar.Equation.PdAtCentre`             | CLEARANCE design                |
| REQ-RADAR-006| Probability of detection is monotonically non-decreasing across a 60 dB SNR sweep                       | `Clearance.Radar.Equation.PdMonotonic`            | Skolnik §2.5                    |
| REQ-RADAR-007| Default parameters (1.4 MW peak, 34 dB antennas, 6 dB loss, 3 dB NF, 290 K, 1 MHz B, 2.8 GHz, 13 dB required SNR) place the Pd = 0.5 crossing for a 10 m^2 target between 40 and 200 nm; Pd(Heavy 100 m^2) > Pd(Light 1 m^2) at 40 nm | `Clearance.Radar.Equation.DefaultCalibration` | ASR-9 specification             |
| REQ-RADAR-008| dB to linear conversion round-trips within numerical tolerance for standard test values (0, 3, 6, 10, 13, 30, 60, -20, -40 dB); LinearFromDb(0) = 1 exactly; DbFromLinear(0) returns the -1000 dB sentinel (not NaN or -inf) | `Clearance.Radar.Equation.DbRoundTrip`            | CLEARANCE design                |

## Coverage summary

| Domain     | REQs   | Tests  | Ratio    |
|------------|--------|--------|----------|
| DIS        | 22     | 14     | 1.57:1   |
| FED        | 6      | 5      | 1.20:1   |
| COMMS      | 10     | 10     | 1.00:1   |
| SAFETY     | 9      | 5      | 1.80:1   |
| SCORE      | 6      | 5      | 1.20:1   |
| SIM        | 8      | 5      | 1.60:1   |
| RADAR      | 8      | 8      | 1.00:1   |
| **Total**  | **69** | **52** | **1.33:1** |

A ratio above 1 means individual tests cover multiple related
requirements. For example, one recorder test verifies both
`FindSnapshotAt` semantics and `FRecordedSnapshot::States` round-trip.
That's expected. A test that only ever covered one requirement would
be an over-testing smell.

### Uncovered subsystems (deferred to integration or manual pass)

- **Conflict detector**: requires an `AClearanceAirspaceManager`
  actor spawned in a UWorld. Manual verification via the instructor
  scope during scenario runs.
- **TCAS RA**: same actor dependency as the conflict detector.
- **Chaff and wake turbulence detection**: same.
- **Phraseology `Interpret`**: requires a running
  `AClearanceSimulationController`. Manual verification via the
  `clearance.say` console command during scenarios.
- **HLA federation join lifecycle**: requires a running
  `rtinode.exe`. Manual verification in
  [`V_AND_V_PLAN.md`](V_AND_V_PLAN.md) §5.

Each of these has a manual verification procedure documented in the
V&V plan, not swept under the rug.

## Adding a new requirement

1. Write the test first. Tag the top comment block with the new
   `REQ-<DOMAIN>-<###>`.
2. Add a row to the domain's table above with the requirement text,
   the test that verifies it, and the source (IEEE / ICAO section
   reference, certification data source, or "CLEARANCE design").
3. Bump the count in the coverage summary table.

The convention is intentionally lightweight. Heavier process
wouldn't survive portfolio-project cadence, and V&V rigour is
proven by the test-tagging discipline, not by the doc's typography.
