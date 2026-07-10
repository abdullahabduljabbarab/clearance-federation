// Standalone self-test for the ClearanceDIS wire-format library. Runs
// outside Unreal - no UE test framework dependency, just <cassert>. The
// same round-trip properties are also exercised by the UE-side
// IMPLEMENT_SIMPLE_AUTOMATION_TEST suite under Private/Tests/, but those
// need the editor. This binary is what CI runs on every push.
//
// Each test asserts one property of one PDU shape. Non-zero exit code
// on failure so ctest picks it up. - TripleA

#include "ClearanceDIS/ClearanceDISPDU.h"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string_view>
#include <vector>

namespace
{
	// Track pass/fail so we can print a summary before exiting. - TripleA
	int g_pass = 0;
	int g_fail = 0;

	void expect(const char* label, bool ok)
	{
		if (ok) { ++g_pass; std::printf("  PASS  %s\n", label); }
		else    { ++g_fail; std::printf("  FAIL  %s\n", label); }
	}

	ClearanceDIS::FWireParams make_params()
	{
		ClearanceDIS::FWireParams P;
		P.ExerciseId    = 1;
		P.SiteId        = 42;
		P.ApplicationId = 7;
		P.SimTimeSeconds = 128.5;
		return P;
	}

	// ------------------------------------------------------------------
	//  REQ-DIS-005..007 - Fire PDU: fixed 96 bytes, round-trips every
	//  field, parser rejects short buffers.
	// ------------------------------------------------------------------
	void test_fire_pdu()
	{
		std::printf("Fire PDU:\n");

		const auto firing = ClearanceDIS::HashCallsignToEntityNumber("VIPER01");
		const auto target = ClearanceDIS::HashCallsignToEntityNumber("UNK001");

		ClearanceDIS::FFireEvent E;
		E.FiringEntity   = firing;
		E.TargetEntity   = target;
		E.EventNumber    = 42;
		E.MunitionEntity = ClearanceDIS::DeriveMunitionEntityNumber(firing, 42);
		E.XMeters = 120.0 * 1852.0;
		E.YMeters =  80.0 * 1852.0;
		E.ZMeters = 25000.0 * 0.3048;
		E.VxMps   = 500.f * 0.514444f;
		E.VyMps   = 300.f * 0.514444f;
		E.VzMps   = -50.f * 0.514444f;
		E.MunitionKind = 1;
		E.WarheadKind  = 1000;
		E.FuseKind     = 1000;
		E.Quantity     = 1;
		E.Rate         = 0;
		E.RangeMeters  = 20000.f;

		const auto wire = ClearanceDIS::BuildFirePDU(E, make_params());
		expect("length is fixed 96 bytes (spec §7.3.3)", wire.size() == 96);
		expect("PDU type byte is 2 (Fire)",              wire[2] == 2);
		expect("Protocol family byte is 2 (Warfare)",    wire[3] == 2);

		ClearanceDIS::FFireEvent out;
		expect("parser accepts well-formed Fire PDU",
			ClearanceDIS::ParseFirePDU(wire.data(), wire.size(), out));
		expect("FiringEntity round-trips",   out.FiringEntity   == E.FiringEntity);
		expect("TargetEntity round-trips",   out.TargetEntity   == E.TargetEntity);
		expect("MunitionEntity round-trips", out.MunitionEntity == E.MunitionEntity);
		expect("EventNumber round-trips",    out.EventNumber    == E.EventNumber);
		expect("WarheadKind round-trips",    out.WarheadKind    == E.WarheadKind);

		// Malformed rejection - short buffer.
		expect("parser rejects buffer < 96 bytes",
			!ClearanceDIS::ParseFirePDU(wire.data(), 32, out));
	}

	// ------------------------------------------------------------------
	//  REQ-DIS-008..010 - Detonation PDU: fixed 104 bytes.
	// ------------------------------------------------------------------
	void test_detonation_pdu()
	{
		std::printf("Detonation PDU:\n");

		ClearanceDIS::FDetonationEvent D;
		D.FiringEntity     = ClearanceDIS::HashCallsignToEntityNumber("VIPER01");
		D.TargetEntity     = ClearanceDIS::HashCallsignToEntityNumber("UNK001");
		D.MunitionEntity   = 12345;
		D.EventNumber      = 42;
		D.XMeters          = 100.0;
		D.YMeters          = 200.0;
		D.ZMeters          = 5000.0;
		D.VxMps            = 100.f;
		D.VyMps            = 50.f;
		D.VzMps            = -25.f;
		D.MunitionKind     = 1;
		D.WarheadKind      = 1000;
		D.FuseKind         = 1000;
		D.Quantity         = 1;
		D.Rate             = 0;
		D.DetonationResult = 2;

		const auto wire = ClearanceDIS::BuildDetonationPDU(D, make_params());
		expect("length is fixed 104 bytes (spec §7.3.4)", wire.size() == 104);
		expect("PDU type byte is 3 (Detonation)",         wire[2] == 3);

		ClearanceDIS::FDetonationEvent out;
		expect("parser accepts well-formed Detonation PDU",
			ClearanceDIS::ParseDetonationPDU(wire.data(), wire.size(), out));
		expect("FiringEntity round-trips",     out.FiringEntity     == D.FiringEntity);
		expect("DetonationResult round-trips", out.DetonationResult == D.DetonationResult);
		expect("EventNumber round-trips",      out.EventNumber      == D.EventNumber);

		expect("parser rejects buffer < 104 bytes",
			!ClearanceDIS::ParseDetonationPDU(wire.data(), 50, out));
	}

	// ------------------------------------------------------------------
	//  REQ-DIS-004 - Entity State PDU: ForceId at spec offset 18.
	//  Covers the RPR-FOM affiliation mapping requirement without needing
	//  a public Entity State parser. - TripleA
	// ------------------------------------------------------------------
	void test_entity_state_forceid()
	{
		std::printf("Entity State PDU ForceId spec offset:\n");

		for (std::uint8_t force = 0; force <= 3; ++force)
		{
			ClearanceDIS::FEntityState S;
			S.EntityNumber      = ClearanceDIS::HashCallsignToEntityNumber("TEST01");
			S.ForceId           = force;
			S.EntityKind        = 1;
			S.EntityDomain      = 2;
			S.EntityCountry     = 225;
			S.EntityCategory    = 1;
			S.EntitySubcategory = 0;
			S.EntitySpecific    = 0;
			S.EntityExtra       = 0;
			S.XMeters = 0.0; S.YMeters = 0.0; S.ZMeters = 5000.0;
			S.VxMps   = 0.f; S.VyMps   = 0.f; S.VzMps   = 0.f;
			S.PsiRad  = 0.f; S.ThetaRad = 0.f; S.PhiRad = 0.f;
			S.Marking = "TEST01";

			const auto wire = ClearanceDIS::BuildEntityStatePDU(S, make_params());
			char label[80];
			std::snprintf(label, sizeof(label),
				"ForceId=%u written at byte 18 per §7.3.4.6", (unsigned)force);
			expect(label, wire.size() > 18 && wire[18] == force);
		}
	}

	// ------------------------------------------------------------------
	//  REQ-DIS-001 - Entity State PDU: fixed 144 bytes.
	// ------------------------------------------------------------------
	void test_entity_state_size()
	{
		std::printf("Entity State PDU size:\n");

		ClearanceDIS::FEntityState S;
		S.EntityNumber      = 12345;
		S.ForceId           = 1;
		S.EntityKind        = 1;
		S.EntityDomain      = 2;
		S.EntityCountry     = 225;
		S.EntityCategory    = 1;
		S.EntitySubcategory = 0;
		S.EntitySpecific    = 0;
		S.EntityExtra       = 0;
		S.XMeters = 0.0; S.YMeters = 0.0; S.ZMeters = 5000.0;
		S.VxMps   = 0.f; S.VyMps   = 0.f; S.VzMps   = 0.f;
		S.PsiRad  = 0.f; S.ThetaRad = 0.f; S.PhiRad = 0.f;
		S.Marking = "TEST01";

		const auto wire = ClearanceDIS::BuildEntityStatePDU(S, make_params());
		expect("length is fixed 144 bytes (spec §7.3.4)", wire.size() == 144);
		expect("PDU type byte is 1 (Entity State)",       wire[2] == 1);
		expect("Protocol version byte is 6 (IEEE 1278.1A-1998)", wire[0] == 6);
	}

	// ------------------------------------------------------------------
	//  REQ-DIS-011..013 - Emission PDU: Type 23, Distributed Emission
	//  Regeneration family (6). Painted-target list round-trips.
	// ------------------------------------------------------------------
	void test_emission_pdu()
	{
		std::printf("Emission PDU:\n");

		ClearanceDIS::FEmissionSnapshot S;
		S.EmittingEntity  = ClearanceDIS::HashCallsignToEntityNumber("ATCTOWER");
		S.PositionMetersX = 100.0; S.PositionMetersY = 200.0; S.PositionMetersZ = 30.0;
		S.EmitterName     = 4830;    // ASR-9 civil surveillance
		S.EmitterFunction = 3;
		S.FrequencyLowHz            = 2.7e9f;
		S.FrequencyHighHz           = 2.9e9f;
		S.EffectiveRadiatedPowerDbm = 78.f;
		S.PulseRepetitionFreqHz     = 1200.f;
		S.PulseWidthMicrosec        = 1.f;
		S.BeamAzimuthRad = 0.f;
		S.BeamFunction   = 2;
		S.PaintedEntityNumbers = {
			ClearanceDIS::HashCallsignToEntityNumber("DLH101"),
			ClearanceDIS::HashCallsignToEntityNumber("BAW472"),
			ClearanceDIS::HashCallsignToEntityNumber("VIPER01"),
		};

		const auto wire = ClearanceDIS::BuildEmissionPDU(S, make_params());
		expect("length >= minimum Emission PDU size", wire.size() >= 28);
		expect("PDU type byte is 23 (Emission)",       wire[2] == 23);
		expect("Protocol family byte is 6 (Emission Regen)", wire[3] == 6);

		ClearanceDIS::FEmissionSnapshot out;
		expect("parser accepts well-formed Emission PDU",
			ClearanceDIS::ParseEmissionPDU(wire.data(), wire.size(), out));
		expect("EmittingEntity round-trips", out.EmittingEntity == S.EmittingEntity);
		expect("Painted-target count round-trips",
			out.PaintedEntityNumbers.size() == S.PaintedEntityNumbers.size());
		expect("First painted target round-trips",
			!out.PaintedEntityNumbers.empty() &&
			out.PaintedEntityNumbers[0] == S.PaintedEntityNumbers[0]);

		expect("parser rejects buffer < 28 bytes",
			!ClearanceDIS::ParseEmissionPDU(wire.data(), 12, out));
	}

	// ------------------------------------------------------------------
	//  REQ-DIS-014..016 - Signal PDU: Type 26, Radio Communications (4).
	//  Opaque payload preserved verbatim.
	// ------------------------------------------------------------------
	void test_signal_pdu()
	{
		std::printf("Signal PDU:\n");

		ClearanceDIS::FSignalEvent E;
		E.OwnerEntity = ClearanceDIS::HashCallsignToEntityNumber("ATCTOWER");
		E.RadioId     = 1;
		// ASCII payload standing in for a voice-over-IP header.
		const char* txt = "CLEARANCE DELIVERY";
		E.Data.assign(reinterpret_cast<const std::uint8_t*>(txt),
		              reinterpret_cast<const std::uint8_t*>(txt) + 18);

		const auto wire = ClearanceDIS::BuildSignalPDU(E, make_params());
		expect("PDU type byte is 26 (Signal)",              wire[2] == 26);
		expect("Protocol family byte is 4 (Radio Comms)",   wire[3] == 4);

		ClearanceDIS::FSignalEvent out;
		expect("parser accepts well-formed Signal PDU",
			ClearanceDIS::ParseSignalPDU(wire.data(), wire.size(), out));
		expect("OwnerEntity round-trips",         out.OwnerEntity == E.OwnerEntity);
		expect("RadioId round-trips",             out.RadioId     == E.RadioId);
		expect("Data payload length round-trips", out.Data.size() == E.Data.size());
		expect("Data payload bytes round-trip verbatim",
			!out.Data.empty() &&
			std::memcmp(out.Data.data(), E.Data.data(), E.Data.size()) == 0);
	}

	// ------------------------------------------------------------------
	//  REQ-DIS-017..019 - Transmitter PDU: Type 25, Radio Comms (4).
	//  Frequency / antenna position / transmit-state fields.
	// ------------------------------------------------------------------
	void test_transmitter_pdu()
	{
		std::printf("Transmitter PDU:\n");

		ClearanceDIS::FTransmitterState R;
		R.OwnerEntity     = ClearanceDIS::HashCallsignToEntityNumber("ATCTOWER");
		R.RadioId         = 1;
		R.FrequencyHz     = 121500000ull;   // ATC guard 121.500 MHz
		R.BandwidthHz     = 25000.f;
		R.PowerDbm        = 40.f;
		R.TransmitState   = 2;              // on-transmitting
		R.AntennaXMeters  = 10.0;
		R.AntennaYMeters  = 20.0;
		R.AntennaZMeters  = 30.0;

		const auto wire = ClearanceDIS::BuildTransmitterPDU(R, make_params());
		expect("PDU type byte is 25 (Transmitter)",         wire[2] == 25);
		expect("Protocol family byte is 4 (Radio Comms)",   wire[3] == 4);

		ClearanceDIS::FTransmitterState out;
		expect("parser accepts well-formed Transmitter PDU",
			ClearanceDIS::ParseTransmitterPDU(wire.data(), wire.size(), out));
		expect("OwnerEntity round-trips",   out.OwnerEntity   == R.OwnerEntity);
		expect("FrequencyHz round-trips",   out.FrequencyHz   == R.FrequencyHz);
		expect("TransmitState round-trips", out.TransmitState == R.TransmitState);
	}

	// ------------------------------------------------------------------
	//  Determinism - the same struct in must produce byte-for-byte
	//  identical output every call. Guards against uninitialised padding
	//  or a wall-clock leak into the wire. Federation replay/record
	//  workflows depend on this. - TripleA
	// ------------------------------------------------------------------
	void test_determinism()
	{
		std::printf("Byte-for-byte determinism:\n");

		const auto P = make_params();

		ClearanceDIS::FFireEvent E;
		E.FiringEntity   = 100;
		E.TargetEntity   = 200;
		E.EventNumber    = 42;
		E.MunitionEntity = ClearanceDIS::DeriveMunitionEntityNumber(100, 42);
		E.WarheadKind    = 1000;
		E.RangeMeters    = 5000.f;
		expect("Fire PDU: two encodes are byte-identical",
			ClearanceDIS::BuildFirePDU(E, P) == ClearanceDIS::BuildFirePDU(E, P));

		ClearanceDIS::FDetonationEvent D;
		D.FiringEntity     = 100; D.TargetEntity = 200; D.EventNumber = 42;
		D.MunitionEntity   = ClearanceDIS::DeriveMunitionEntityNumber(100, 42);
		D.DetonationResult = 2;
		expect("Detonation PDU: two encodes are byte-identical",
			ClearanceDIS::BuildDetonationPDU(D, P) == ClearanceDIS::BuildDetonationPDU(D, P));

		ClearanceDIS::FEntityState S;
		S.EntityNumber = 12345; S.ForceId = 1;
		S.Marking = "TEST01";
		expect("Entity State PDU: two encodes are byte-identical",
			ClearanceDIS::BuildEntityStatePDU(S, P) == ClearanceDIS::BuildEntityStatePDU(S, P));

		ClearanceDIS::FEmissionSnapshot Em;
		Em.EmittingEntity = 500;
		Em.PaintedEntityNumbers = {100, 200, 300};
		expect("Emission PDU: two encodes are byte-identical",
			ClearanceDIS::BuildEmissionPDU(Em, P) == ClearanceDIS::BuildEmissionPDU(Em, P));

		ClearanceDIS::FSignalEvent Sg;
		Sg.OwnerEntity = 500;
		Sg.Data = {0xDE, 0xAD, 0xBE, 0xEF};
		expect("Signal PDU: two encodes are byte-identical",
			ClearanceDIS::BuildSignalPDU(Sg, P) == ClearanceDIS::BuildSignalPDU(Sg, P));

		ClearanceDIS::FTransmitterState Tx;
		Tx.OwnerEntity = 500; Tx.FrequencyHz = 121500000ull;
		expect("Transmitter PDU: two encodes are byte-identical",
			ClearanceDIS::BuildTransmitterPDU(Tx, P) == ClearanceDIS::BuildTransmitterPDU(Tx, P));
	}

	// ------------------------------------------------------------------
	//  Callsign hash stability. Same input → same output every time.
	//  Federate interop requires this to be deterministic across
	//  processes / builds. - TripleA
	// ------------------------------------------------------------------
	void test_callsign_hash_stability()
	{
		std::printf("Callsign hash stability:\n");
		const auto a1 = ClearanceDIS::HashCallsignToEntityNumber("DLH101");
		const auto a2 = ClearanceDIS::HashCallsignToEntityNumber("DLH101");
		expect("DLH101 hashes to identical value on repeat", a1 == a2);

		const auto b1 = ClearanceDIS::HashCallsignToEntityNumber("BAW472");
		expect("Different callsigns hash to different values", a1 != b1);

		const auto empty = ClearanceDIS::HashCallsignToEntityNumber("");
		expect("Empty callsign hashes to 0 (reserved unknown)", empty == 0);
	}
}

int main()
{
	std::printf("=== ClearanceDIS wire-format self-test ===\n\n");

	test_fire_pdu();
	test_detonation_pdu();
	test_entity_state_forceid();
	test_entity_state_size();
	test_emission_pdu();
	test_signal_pdu();
	test_transmitter_pdu();
	test_determinism();
	test_callsign_hash_stability();

	std::printf("\n=== Summary: %d passed, %d failed ===\n", g_pass, g_fail);
	return g_fail == 0 ? 0 : 1;
}
