// Pure C++ implementations of the six DIS PDU wire formats. No Unreal types,
// no floating-point library beyond IEEE 754 bit reinterpretation. Every
// serialiser cites the IEEE 1278.1 section it implements so a reviewer can
// walk field-by-field back to the standard. - TripleA

#include "ClearanceDIS/ClearanceDISPDU.h"

#include <cmath>
#include <cstring>

namespace
{
	// ---- Byte writers (big-endian, network order per §7.2) ----
	inline void WriteU8(std::vector<std::uint8_t>& B, std::uint8_t V) { B.push_back(V); }

	inline void WriteU16BE(std::vector<std::uint8_t>& B, std::uint16_t V)
	{
		B.push_back(static_cast<std::uint8_t>((V >> 8) & 0xFF));
		B.push_back(static_cast<std::uint8_t>(V & 0xFF));
	}

	inline void WriteU32BE(std::vector<std::uint8_t>& B, std::uint32_t V)
	{
		B.push_back(static_cast<std::uint8_t>((V >> 24) & 0xFF));
		B.push_back(static_cast<std::uint8_t>((V >> 16) & 0xFF));
		B.push_back(static_cast<std::uint8_t>((V >>  8) & 0xFF));
		B.push_back(static_cast<std::uint8_t>(V & 0xFF));
	}

	inline void WriteU64BE(std::vector<std::uint8_t>& B, std::uint64_t V)
	{
		for (int i = 7; i >= 0; --i) { B.push_back(static_cast<std::uint8_t>((V >> (i * 8)) & 0xFF)); }
	}

	inline void WriteFloatBE(std::vector<std::uint8_t>& B, float V)
	{
		std::uint32_t Bits = 0;
		std::memcpy(&Bits, &V, sizeof(Bits));
		WriteU32BE(B, Bits);
	}

	inline void WriteDoubleBE(std::vector<std::uint8_t>& B, double V)
	{
		std::uint64_t Bits = 0;
		std::memcpy(&Bits, &V, sizeof(Bits));
		WriteU64BE(B, Bits);
	}

	// ---- Byte readers with bounds tracking ----
	inline std::uint8_t ReadU8(const std::uint8_t* Buf, std::size_t Len, std::size_t& Cur, bool& Ok)
	{
		if (Cur + 1 > Len) { Ok = false; return 0; }
		return Buf[Cur++];
	}

	inline std::uint16_t ReadU16BE(const std::uint8_t* Buf, std::size_t Len, std::size_t& Cur, bool& Ok)
	{
		if (Cur + 2 > Len) { Ok = false; return 0; }
		const std::uint16_t V = static_cast<std::uint16_t>((std::uint16_t(Buf[Cur]) << 8) | std::uint16_t(Buf[Cur + 1]));
		Cur += 2;
		return V;
	}

	inline std::uint32_t ReadU32BE(const std::uint8_t* Buf, std::size_t Len, std::size_t& Cur, bool& Ok)
	{
		if (Cur + 4 > Len) { Ok = false; return 0; }
		const std::uint32_t V =
			(std::uint32_t(Buf[Cur    ]) << 24) |
			(std::uint32_t(Buf[Cur + 1]) << 16) |
			(std::uint32_t(Buf[Cur + 2]) <<  8) |
			 std::uint32_t(Buf[Cur + 3]);
		Cur += 4;
		return V;
	}

	inline std::uint64_t ReadU64BE(const std::uint8_t* Buf, std::size_t Len, std::size_t& Cur, bool& Ok)
	{
		if (Cur + 8 > Len) { Ok = false; return 0; }
		std::uint64_t V = 0;
		for (int i = 0; i < 8; ++i) { V = (V << 8) | std::uint64_t(Buf[Cur + i]); }
		Cur += 8;
		return V;
	}

	inline float ReadFloatBE(const std::uint8_t* Buf, std::size_t Len, std::size_t& Cur, bool& Ok)
	{
		const std::uint32_t Bits = ReadU32BE(Buf, Len, Cur, Ok);
		float V = 0.f;
		std::memcpy(&V, &Bits, sizeof(V));
		return V;
	}

	inline double ReadDoubleBE(const std::uint8_t* Buf, std::size_t Len, std::size_t& Cur, bool& Ok)
	{
		const std::uint64_t Bits = ReadU64BE(Buf, Len, Cur, Ok);
		double V = 0.0;
		std::memcpy(&V, &Bits, sizeof(V));
		return V;
	}

	// DIS timestamp: 31-bit fraction of an hour past the top of the hour, LSB=0
	// for "relative" (not UTC-synced) per §7.2.2 table 7-2. - TripleA
	inline std::uint32_t DerivedTimestamp(double SimTimeSeconds)
	{
		const double SecondsInHour = std::fmod(SimTimeSeconds, 3600.0);
		return static_cast<std::uint32_t>((SecondsInHour * (2147483648.0 / 3600.0))) & 0xFFFFFFFEu;
	}

	// Common header - 12 bytes. Every PDU starts with this. - TripleA
	inline void WriteHeader(std::vector<std::uint8_t>& B, std::uint8_t ExerciseId,
		std::uint8_t PduType, std::uint8_t ProtoFamily, std::uint16_t PduLength,
		double SimTimeSeconds)
	{
		WriteU8(B, 6);                              // Protocol version (6 = IEEE 1278.1A-1998)
		WriteU8(B, ExerciseId);
		WriteU8(B, PduType);
		WriteU8(B, ProtoFamily);
		WriteU32BE(B, DerivedTimestamp(SimTimeSeconds));
		WriteU16BE(B, PduLength);
		WriteU16BE(B, 0);                           // padding
	}

	// Returns true on well-formed header AND matching type/family/length. - TripleA
	inline bool ReadAndCheckHeader(const std::uint8_t* Buf, std::size_t Len, std::size_t& Cur,
		std::uint8_t ExpectedPduType, std::uint8_t ExpectedProtoFamily)
	{
		bool Ok = true;
		const std::uint8_t  ProtoVersion = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok);            // Exercise
		const std::uint8_t  PduType      = ReadU8(Buf, Len, Cur, Ok);
		const std::uint8_t  ProtoFamily  = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU32BE(Buf, Len, Cur, Ok);         // Timestamp
		const std::uint16_t PduLength    = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok);         // padding
		if (!Ok || ProtoVersion == 0)                                      { return false; }
		if (PduType != ExpectedPduType || ProtoFamily != ExpectedProtoFamily) { return false; }
		if (PduLength != static_cast<std::uint16_t>(Len))                    { return false; }
		return true;
	}
}

namespace ClearanceDIS
{
	// ============================================================================
	// Entity State PDU (Type 1) - §7.3.4
	// ============================================================================
	std::vector<std::uint8_t> BuildEntityStatePDU(const FEntityState& S, const FWireParams& P)
	{
		const std::uint16_t PduLength = 144;
		std::vector<std::uint8_t> Out;
		Out.reserve(PduLength);

		WriteHeader(Out, P.ExerciseId, /*PduType*/ 1, /*Family*/ 1, PduLength, P.SimTimeSeconds);

		// Entity ID
		WriteU16BE(Out, P.SiteId);
		WriteU16BE(Out, P.ApplicationId);
		WriteU16BE(Out, S.EntityNumber);

		// Force ID + articulation param count
		WriteU8(Out, S.ForceId);
		WriteU8(Out, 0);

		// Entity Type (8 bytes)
		WriteU8(Out, S.EntityKind);
		WriteU8(Out, S.EntityDomain);
		WriteU16BE(Out, S.EntityCountry);
		WriteU8(Out, S.EntityCategory);
		WriteU8(Out, S.EntitySubcategory);
		WriteU8(Out, S.EntitySpecific);
		WriteU8(Out, S.EntityExtra);

		// Alternative Entity Type - same as above for simulation use
		WriteU8(Out, S.EntityKind);
		WriteU8(Out, S.EntityDomain);
		WriteU16BE(Out, S.EntityCountry);
		WriteU8(Out, S.EntityCategory);
		WriteU8(Out, S.EntitySubcategory);
		WriteU8(Out, S.EntitySpecific);
		WriteU8(Out, S.EntityExtra);

		// Linear velocity, world location, orientation
		WriteFloatBE(Out, S.VxMps);
		WriteFloatBE(Out, S.VyMps);
		WriteFloatBE(Out, S.VzMps);
		WriteDoubleBE(Out, S.XMeters);
		WriteDoubleBE(Out, S.YMeters);
		WriteDoubleBE(Out, S.ZMeters);
		WriteFloatBE(Out, S.PsiRad);
		WriteFloatBE(Out, S.ThetaRad);
		WriteFloatBE(Out, S.PhiRad);

		// Entity Appearance (32-bit bitfield) + dead reckoning (40 bytes)
		WriteU32BE(Out, 0);
		WriteU8(Out, 2);                            // DRM(F,P,W) - constant linear velocity
		for (int i = 0; i < 15; ++i) { WriteU8(Out, 0); }
		WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f);   // linear accel
		WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f);   // angular vel

		// Marking (12 bytes: 1 charset + 11 chars, zero-padded)
		WriteU8(Out, 1);                            // ASCII
		const std::size_t Take = std::min<std::size_t>(11, S.Marking.size());
		for (std::size_t i = 0; i < Take; ++i) { WriteU8(Out, static_cast<std::uint8_t>(S.Marking[i])); }
		for (std::size_t i = Take; i < 11; ++i) { WriteU8(Out, 0); }

		// Capabilities (4 bytes, zero for baseline)
		WriteU32BE(Out, 0);

		return Out;
	}

	// ============================================================================
	// Fire PDU (Type 2) - §7.3.3
	// ============================================================================
	std::vector<std::uint8_t> BuildFirePDU(const FFireEvent& E, const FWireParams& P)
	{
		const std::uint16_t PduLength = 96;
		std::vector<std::uint8_t> Out;
		Out.reserve(PduLength);

		WriteHeader(Out, P.ExerciseId, /*PduType*/ 2, /*Family*/ 2, PduLength, P.SimTimeSeconds);

		// Firing / Target / Munition entity IDs
		WriteU16BE(Out, P.SiteId);
		WriteU16BE(Out, P.ApplicationId);
		WriteU16BE(Out, E.FiringEntity);
		WriteU16BE(Out, P.SiteId);
		WriteU16BE(Out, P.ApplicationId);
		WriteU16BE(Out, E.TargetEntity);
		WriteU16BE(Out, P.SiteId);
		WriteU16BE(Out, P.ApplicationId);
		WriteU16BE(Out, E.MunitionEntity);

		// Event ID
		WriteU16BE(Out, P.SiteId);
		WriteU16BE(Out, P.ApplicationId);
		WriteU16BE(Out, E.EventNumber);

		// Fire Mission Index (0 for single shots)
		WriteU32BE(Out, 0);

		// Location in world coordinates
		WriteDoubleBE(Out, E.XMeters);
		WriteDoubleBE(Out, E.YMeters);
		WriteDoubleBE(Out, E.ZMeters);

		// Burst Descriptor (§7.3.3 table 7-4)
		WriteU8(Out, 2);                            // Kind = Munition
		WriteU8(Out, 2);                            // Domain = Air
		WriteU16BE(Out, 225);                       // Country = US
		WriteU8(Out, E.MunitionKind);
		WriteU8(Out, 0);
		WriteU8(Out, 0);
		WriteU8(Out, 0);
		WriteU16BE(Out, E.WarheadKind);
		WriteU16BE(Out, E.FuseKind);
		WriteU16BE(Out, E.Quantity);
		WriteU16BE(Out, E.Rate);

		// Velocity + Range
		WriteFloatBE(Out, E.VxMps);
		WriteFloatBE(Out, E.VyMps);
		WriteFloatBE(Out, E.VzMps);
		WriteFloatBE(Out, E.RangeMeters);

		return Out;
	}

	bool ParseFirePDU(const std::uint8_t* Buf, std::size_t Len, FFireEvent& Out)
	{
		std::size_t Cur = 0;
		if (!ReadAndCheckHeader(Buf, Len, Cur, /*PduType*/ 2, /*Family*/ 2)) { return false; }

		bool Ok = true;
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.FiringEntity   = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.TargetEntity   = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.MunitionEntity = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.EventNumber    = ReadU16BE(Buf, Len, Cur, Ok);

		(void)ReadU32BE(Buf, Len, Cur, Ok);           // Fire Mission Index

		Out.XMeters = ReadDoubleBE(Buf, Len, Cur, Ok);
		Out.YMeters = ReadDoubleBE(Buf, Len, Cur, Ok);
		Out.ZMeters = ReadDoubleBE(Buf, Len, Cur, Ok);

		(void)ReadU8(Buf, Len, Cur, Ok);              // Kind
		(void)ReadU8(Buf, Len, Cur, Ok);              // Domain
		(void)ReadU16BE(Buf, Len, Cur, Ok);           // Country
		Out.MunitionKind = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok);
		Out.WarheadKind = ReadU16BE(Buf, Len, Cur, Ok);
		Out.FuseKind    = ReadU16BE(Buf, Len, Cur, Ok);
		Out.Quantity    = ReadU16BE(Buf, Len, Cur, Ok);
		Out.Rate        = ReadU16BE(Buf, Len, Cur, Ok);

		Out.VxMps = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.VyMps = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.VzMps = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.RangeMeters = ReadFloatBE(Buf, Len, Cur, Ok);

		return Ok;
	}

	// ============================================================================
	// Detonation PDU (Type 3) - §7.3.4
	// ============================================================================
	std::vector<std::uint8_t> BuildDetonationPDU(const FDetonationEvent& E, const FWireParams& P)
	{
		const std::uint16_t PduLength = 104;
		std::vector<std::uint8_t> Out;
		Out.reserve(PduLength);

		WriteHeader(Out, P.ExerciseId, /*PduType*/ 3, /*Family*/ 2, PduLength, P.SimTimeSeconds);

		WriteU16BE(Out, P.SiteId); WriteU16BE(Out, P.ApplicationId); WriteU16BE(Out, E.FiringEntity);
		WriteU16BE(Out, P.SiteId); WriteU16BE(Out, P.ApplicationId); WriteU16BE(Out, E.TargetEntity);
		WriteU16BE(Out, P.SiteId); WriteU16BE(Out, P.ApplicationId); WriteU16BE(Out, E.MunitionEntity);

		WriteU16BE(Out, P.SiteId); WriteU16BE(Out, P.ApplicationId); WriteU16BE(Out, E.EventNumber);

		// Velocity, World Location, Burst Descriptor
		WriteFloatBE(Out, E.VxMps); WriteFloatBE(Out, E.VyMps); WriteFloatBE(Out, E.VzMps);
		WriteDoubleBE(Out, E.XMeters); WriteDoubleBE(Out, E.YMeters); WriteDoubleBE(Out, E.ZMeters);

		WriteU8(Out, 2); WriteU8(Out, 2); WriteU16BE(Out, 225);
		WriteU8(Out, E.MunitionKind); WriteU8(Out, 0); WriteU8(Out, 0); WriteU8(Out, 0);
		WriteU16BE(Out, E.WarheadKind); WriteU16BE(Out, E.FuseKind);
		WriteU16BE(Out, E.Quantity);    WriteU16BE(Out, E.Rate);

		// Location in Entity Coordinates (12 bytes - zeros for CLEARANCE)
		WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f);

		// Detonation Result (1) + Num Articulation Params (1) + Padding (2)
		WriteU8(Out, E.DetonationResult);
		WriteU8(Out, 0);
		WriteU16BE(Out, 0);

		return Out;
	}

	bool ParseDetonationPDU(const std::uint8_t* Buf, std::size_t Len, FDetonationEvent& Out)
	{
		std::size_t Cur = 0;
		if (!ReadAndCheckHeader(Buf, Len, Cur, /*PduType*/ 3, /*Family*/ 2)) { return false; }

		bool Ok = true;
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.FiringEntity   = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.TargetEntity   = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.MunitionEntity = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.EventNumber    = ReadU16BE(Buf, Len, Cur, Ok);

		Out.VxMps = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.VyMps = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.VzMps = ReadFloatBE(Buf, Len, Cur, Ok);

		Out.XMeters = ReadDoubleBE(Buf, Len, Cur, Ok);
		Out.YMeters = ReadDoubleBE(Buf, Len, Cur, Ok);
		Out.ZMeters = ReadDoubleBE(Buf, Len, Cur, Ok);

		(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.MunitionKind = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok);
		Out.WarheadKind = ReadU16BE(Buf, Len, Cur, Ok);
		Out.FuseKind    = ReadU16BE(Buf, Len, Cur, Ok);
		Out.Quantity    = ReadU16BE(Buf, Len, Cur, Ok);
		Out.Rate        = ReadU16BE(Buf, Len, Cur, Ok);

		(void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok);

		Out.DetonationResult = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok);              // NumArticulationParameters
		(void)ReadU16BE(Buf, Len, Cur, Ok);           // Pad

		return Ok;
	}

	// ============================================================================
	// Emission PDU (Type 23) - §7.6.2
	// ============================================================================
	std::vector<std::uint8_t> BuildEmissionPDU(const FEmissionSnapshot& S, const FWireParams& P)
	{
		// Fixed 100 bytes + 8 bytes per Track/Jam entry.
		const std::uint16_t PduLength = static_cast<std::uint16_t>(100 + 8 * S.PaintedEntityNumbers.size());
		std::vector<std::uint8_t> Out;
		Out.reserve(PduLength);

		WriteHeader(Out, P.ExerciseId, /*PduType*/ 23, /*Family*/ 6, PduLength, P.SimTimeSeconds);

		// Emitting Entity ID
		WriteU16BE(Out, P.SiteId);
		WriteU16BE(Out, P.ApplicationId);
		WriteU16BE(Out, S.EmittingEntity);

		// Event ID (unused for continuous emission - all zeros)
		WriteU16BE(Out, 0); WriteU16BE(Out, 0); WriteU16BE(Out, 0);

		// State Update Indicator + Number of Emitter Systems + Padding
		WriteU8(Out, 0);                            // 0 = state update
		WriteU8(Out, 1);                            // one emitter system
		WriteU16BE(Out, 0);                         // padding

		// ==== Emitter System (fixed 20 bytes + 52 bytes beam block) ====
		WriteU8(Out, 20);                           // System data length in 32-bit words? Actually bytes/4 - store 20/4=5
		WriteU8(Out, 1);                            // Number of beams
		WriteU16BE(Out, 0);                         // Padding

		// Emitter System (Name / Function / Number)
		WriteU16BE(Out, S.EmitterName);
		WriteU8(Out, S.EmitterFunction);
		WriteU8(Out, 1);                            // emitter number

		// Location w.r.t. entity (12 bytes zero for CLEARANCE)
		WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f);

		// ==== Beam block ====
		WriteU8(Out, 13);                           // Beam Data Length (32-bit words)
		WriteU8(Out, 1);                            // Beam ID Number
		WriteU16BE(Out, 0);                         // Beam Parameter Index

		// Frequency block per §7.6.2 - centre + range (Hz) + ERP + PRF + PW + azimuth (rad)
		const float CenterFreq = 0.5f * (S.FrequencyLowHz + S.FrequencyHighHz);
		const float FreqRange  = S.FrequencyHighHz - S.FrequencyLowHz;
		WriteFloatBE(Out, CenterFreq);
		WriteFloatBE(Out, FreqRange);
		WriteFloatBE(Out, S.EffectiveRadiatedPowerDbm);
		WriteFloatBE(Out, S.PulseRepetitionFreqHz);
		WriteFloatBE(Out, S.PulseWidthMicrosec);
		WriteFloatBE(Out, S.BeamAzimuthRad);
		WriteFloatBE(Out, 0.f);                     // Azimuth Sweep
		WriteFloatBE(Out, 0.f);                     // Elevation Center
		WriteFloatBE(Out, 0.f);                     // Elevation Sweep
		WriteFloatBE(Out, 0.f);                     // Beam Sweep Sync

		WriteU8(Out, S.BeamFunction);
		WriteU8(Out, static_cast<std::uint8_t>(S.PaintedEntityNumbers.size()));
		WriteU8(Out, 0);                            // High Density Track/Jam
		WriteU8(Out, 0);                            // Beam Status
		WriteU32BE(Out, 0);                         // Jamming Technique

		// Track/Jam data (8 bytes per painted entity)
		for (const std::uint16_t Ent : S.PaintedEntityNumbers)
		{
			WriteU16BE(Out, P.SiteId);
			WriteU16BE(Out, P.ApplicationId);
			WriteU16BE(Out, Ent);
			WriteU8(Out, 1);                        // Emitter Number
			WriteU8(Out, 1);                        // Beam Number
		}

		return Out;
	}

	bool ParseEmissionPDU(const std::uint8_t* Buf, std::size_t Len, FEmissionSnapshot& Out)
	{
		std::size_t Cur = 0;
		if (!ReadAndCheckHeader(Buf, Len, Cur, /*PduType*/ 23, /*Family*/ 6)) { return false; }

		bool Ok = true;
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.EmittingEntity = ReadU16BE(Buf, Len, Cur, Ok);

		// Event ID
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);

		(void)ReadU8(Buf, Len, Cur, Ok);            // State Update Indicator
		(void)ReadU8(Buf, Len, Cur, Ok);            // Number of Emitter Systems
		(void)ReadU16BE(Buf, Len, Cur, Ok);         // padding

		// Emitter System header (4 bytes) + emitter details (8 bytes)
		(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.EmitterName     = ReadU16BE(Buf, Len, Cur, Ok);
		Out.EmitterFunction = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok);            // emitter number

		// Location w.r.t. entity (12 bytes - skip)
		(void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok);

		// Beam block
		(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);

		const float CenterFreq = ReadFloatBE(Buf, Len, Cur, Ok);
		const float FreqRange  = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.FrequencyLowHz  = CenterFreq - 0.5f * FreqRange;
		Out.FrequencyHighHz = CenterFreq + 0.5f * FreqRange;
		Out.EffectiveRadiatedPowerDbm = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.PulseRepetitionFreqHz     = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.PulseWidthMicrosec        = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.BeamAzimuthRad            = ReadFloatBE(Buf, Len, Cur, Ok);
		(void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok);
		(void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok);

		Out.BeamFunction = ReadU8(Buf, Len, Cur, Ok);
		const std::uint8_t NTargets = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU32BE(Buf, Len, Cur, Ok);

		Out.PaintedEntityNumbers.clear();
		Out.PaintedEntityNumbers.reserve(NTargets);
		for (std::uint8_t i = 0; i < NTargets; ++i)
		{
			(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
			const std::uint16_t Ent = ReadU16BE(Buf, Len, Cur, Ok);
			(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok);
			Out.PaintedEntityNumbers.push_back(Ent);
		}

		return Ok;
	}

	// ============================================================================
	// Signal PDU (Type 26) - §7.7.3
	// ============================================================================
	std::vector<std::uint8_t> BuildSignalPDU(const FSignalEvent& E, const FWireParams& P)
	{
		// Cap payload at 200 bytes to leave UDP MTU headroom.
		constexpr std::size_t kMaxPayload = 200;
		const std::size_t Payload = std::min(kMaxPayload, E.Data.size());
		const std::size_t Padded  = (Payload + 3) & ~std::size_t(3);
		const std::uint16_t PduLength = static_cast<std::uint16_t>(12 + 20 + Padded);

		std::vector<std::uint8_t> Out;
		Out.reserve(PduLength);
		WriteHeader(Out, P.ExerciseId, /*PduType*/ 26, /*Family*/ 4, PduLength, P.SimTimeSeconds);

		// Radio Reference ID
		WriteU16BE(Out, P.SiteId);
		WriteU16BE(Out, P.ApplicationId);
		WriteU16BE(Out, E.OwnerEntity);
		// Radio ID
		WriteU16BE(Out, E.RadioId);

		// Encoding Scheme: class 1 (Raw Binary Data) in top 2 bits, type 0. §7.7.3.5
		const std::uint16_t EncodingScheme = static_cast<std::uint16_t>(1) << 14;
		WriteU16BE(Out, EncodingScheme);
		WriteU16BE(Out, 0);                         // TDL Type
		WriteU32BE(Out, 0);                         // Sample Rate (0 for raw binary)
		WriteU16BE(Out, static_cast<std::uint16_t>(Payload * 8));   // Data Length in bits
		WriteU16BE(Out, 0);                         // Samples

		for (std::size_t i = 0; i < Payload; ++i) { Out.push_back(E.Data[i]); }
		for (std::size_t i = Payload; i < Padded; ++i) { Out.push_back(0); }

		return Out;
	}

	bool ParseSignalPDU(const std::uint8_t* Buf, std::size_t Len, FSignalEvent& Out)
	{
		std::size_t Cur = 0;
		if (!ReadAndCheckHeader(Buf, Len, Cur, /*PduType*/ 26, /*Family*/ 4)) { return false; }

		bool Ok = true;
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.OwnerEntity = ReadU16BE(Buf, Len, Cur, Ok);
		Out.RadioId     = ReadU16BE(Buf, Len, Cur, Ok);

		(void)ReadU16BE(Buf, Len, Cur, Ok);         // encoding scheme
		(void)ReadU16BE(Buf, Len, Cur, Ok);         // TDL type
		(void)ReadU32BE(Buf, Len, Cur, Ok);         // sample rate
		const std::uint16_t DataLenBits = ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok);         // samples

		const std::size_t DataBytes = DataLenBits / 8;
		if (!Ok || Cur + DataBytes > Len) { return false; }

		Out.Data.assign(Buf + Cur, Buf + Cur + DataBytes);
		return Ok;
	}

	// ============================================================================
	// Transmitter PDU (Type 25) - §7.7.2
	// ============================================================================
	std::vector<std::uint8_t> BuildTransmitterPDU(const FTransmitterState& R, const FWireParams& P)
	{
		const std::uint16_t PduLength = 104;
		std::vector<std::uint8_t> Out;
		Out.reserve(PduLength);

		WriteHeader(Out, P.ExerciseId, /*PduType*/ 25, /*Family*/ 4, PduLength, P.SimTimeSeconds);

		// Radio Reference ID
		WriteU16BE(Out, P.SiteId); WriteU16BE(Out, P.ApplicationId); WriteU16BE(Out, R.OwnerEntity);
		// Radio ID
		WriteU16BE(Out, R.RadioId);

		// Radio Entity Type (Kind 7 Radio, Domain 2 Air, Country 225 US, Cat 5 VHF/UHF)
		WriteU8(Out, 7); WriteU8(Out, 2); WriteU16BE(Out, 225);
		WriteU8(Out, 5); WriteU8(Out, 0); WriteU8(Out, 0); WriteU8(Out, 0);

		// Transmit State + Input Source + Padding
		WriteU8(Out, R.TransmitState);
		WriteU8(Out, 1);                            // Input Source = Pilot
		WriteU16BE(Out, 0);

		// Antenna Location (3 doubles)
		WriteDoubleBE(Out, R.AntennaXMeters);
		WriteDoubleBE(Out, R.AntennaYMeters);
		WriteDoubleBE(Out, R.AntennaZMeters);
		// Relative Antenna Location (12 bytes - zero)
		WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f); WriteFloatBE(Out, 0.f);
		// Antenna Pattern Type (0 = Omni) + Pattern Length (0)
		WriteU16BE(Out, 0); WriteU16BE(Out, 0);

		WriteU64BE(Out, R.FrequencyHz);
		WriteFloatBE(Out, R.BandwidthHz);
		WriteFloatBE(Out, R.PowerDbm);

		// Modulation Type (4 x u16 per §7.7.2.15)
		WriteU16BE(Out, 0);                         // Spread Spectrum
		WriteU16BE(Out, 2);                         // Major Modulation = Amplitude
		WriteU16BE(Out, 2);                         // Detail = AM
		WriteU16BE(Out, 1);                         // System = Generic

		WriteU16BE(Out, 0);                         // Crypto System = No Encryption
		WriteU16BE(Out, 0);                         // Crypto Key ID
		WriteU8(Out, 0);                            // Modulation Parameter Length
		WriteU8(Out, 0);                            // padding
		WriteU16BE(Out, 0);                         // padding

		return Out;
	}

	bool ParseTransmitterPDU(const std::uint8_t* Buf, std::size_t Len, FTransmitterState& Out)
	{
		std::size_t Cur = 0;
		if (!ReadAndCheckHeader(Buf, Len, Cur, /*PduType*/ 25, /*Family*/ 4)) { return false; }

		bool Ok = true;
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		Out.OwnerEntity = ReadU16BE(Buf, Len, Cur, Ok);
		Out.RadioId     = ReadU16BE(Buf, Len, Cur, Ok);

		// Radio Entity Type (skip)
		for (int i = 0; i < 8; ++i) { (void)ReadU8(Buf, Len, Cur, Ok); }

		Out.TransmitState = ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok);            // Input Source
		(void)ReadU16BE(Buf, Len, Cur, Ok);         // padding

		Out.AntennaXMeters = ReadDoubleBE(Buf, Len, Cur, Ok);
		Out.AntennaYMeters = ReadDoubleBE(Buf, Len, Cur, Ok);
		Out.AntennaZMeters = ReadDoubleBE(Buf, Len, Cur, Ok);
		(void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok); (void)ReadFloatBE(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);

		Out.FrequencyHz = ReadU64BE(Buf, Len, Cur, Ok);
		Out.BandwidthHz = ReadFloatBE(Buf, Len, Cur, Ok);
		Out.PowerDbm    = ReadFloatBE(Buf, Len, Cur, Ok);

		// Modulation Type + Crypto (skip)
		for (int i = 0; i < 4; ++i) { (void)ReadU16BE(Buf, Len, Cur, Ok); }
		(void)ReadU16BE(Buf, Len, Cur, Ok); (void)ReadU16BE(Buf, Len, Cur, Ok);
		(void)ReadU8(Buf, Len, Cur, Ok); (void)ReadU8(Buf, Len, Cur, Ok);
		(void)ReadU16BE(Buf, Len, Cur, Ok);

		return Ok;
	}
}
