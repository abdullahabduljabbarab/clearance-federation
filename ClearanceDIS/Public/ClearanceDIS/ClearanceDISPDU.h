// ============================================================================
// ClearanceDISPDU.h - IEEE 1278.1 Distributed Interactive Simulation wire
// format library. Public API for the ClearanceDIS module.
//
// Six PDU types across four protocol families:
//   Entity Information family (§7.3.4)   - Entity State PDU  (Type 1)
//   Warfare family (§7.3.3 / §7.3.4)     - Fire (2), Detonation (3)
//   Distributed Emission family (§7.6.2) - Emission PDU      (Type 23)
//   Radio Communications family (§7.7)   - Transmitter (25), Signal (26)
//
// This header is the entire public API. No other include is required to
// serialise or parse any of the supported PDU types. Depends on the C++
// standard library only - <cstdint>, <string>, <vector>, <string_view>. No
// third-party libraries, no game engine types, no build-system assumptions
// beyond a standard C++17 compiler.
//
// Portability. The same source folder can be linked into an Unreal Engine
// build (as this project uses it), a Unity native plugin, a headless C++
// federate, or an HLA / RPR-FOM gateway. Only the .Build.cs / CMakeLists.txt
// changes at the build system level. No source changes needed. - TripleA
// ============================================================================

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

// ----------------------------------------------------------------------------
// CLEARANCEDIS_API - DLL export/import macro.
//
// When integrated into Unreal Engine, the Unreal Build Tool auto-defines this
// macro as __declspec(dllexport) while compiling this module and
// __declspec(dllimport) while consuming its public API from another module.
// The block below is a defensive fallback so the header remains valid when
// consumed outside Unreal - a standalone build defines CLEARANCEDIS_BUILDING
// while compiling the .cpp, leaves it undefined while consuming. - TripleA
// ----------------------------------------------------------------------------
#ifndef CLEARANCEDIS_API
	#if defined(_MSC_VER)
		#ifdef CLEARANCEDIS_BUILDING
			#define CLEARANCEDIS_API __declspec(dllexport)
		#else
			#define CLEARANCEDIS_API __declspec(dllimport)
		#endif
	#elif defined(__GNUC__) || defined(__clang__)
		#define CLEARANCEDIS_API __attribute__((visibility("default")))
	#else
		#define CLEARANCEDIS_API
	#endif
#endif

namespace ClearanceDIS
{
	// ========================================================================
	//  Common per-federate identifiers - appear in every PDU header.
	// ========================================================================
	struct FWireParams
	{
		std::uint8_t  ExerciseId     = 1;
		std::uint16_t SiteId         = 1;
		std::uint16_t ApplicationId  = 1;
		double        SimTimeSeconds = 0.0;   // Drives the DIS timestamp (§7.2.2)
	};

	// ========================================================================
	//  PDU input / output structs. All coordinates in ECEF metres, velocities
	//  in m/s, orientation in radians - the DIS-native units. The caller does
	//  any unit conversion from sim-native units at the module boundary.
	// ========================================================================

	// Entity State PDU (Type 1, §7.3.4)
	struct FEntityState
	{
		std::string   Marking;                    // ASCII, up to 11 chars used
		std::uint16_t EntityNumber      = 0;      // Derived via HashCallsignToEntityNumber
		std::uint8_t  ForceId           = 0;      // 0=other 1=friendly 2=hostile 3=neutral
		std::uint8_t  EntityKind        = 1;      // Annex A: 1=Platform
		std::uint8_t  EntityDomain      = 2;      // 2=Air
		std::uint16_t EntityCountry     = 225;    // 225=US
		std::uint8_t  EntityCategory    = 1;
		std::uint8_t  EntitySubcategory = 0;
		std::uint8_t  EntitySpecific    = 0;
		std::uint8_t  EntityExtra       = 0;
		double        XMeters = 0.0, YMeters = 0.0, ZMeters = 0.0;
		float         VxMps   = 0.f, VyMps   = 0.f, VzMps   = 0.f;
		float         PsiRad  = 0.f, ThetaRad = 0.f, PhiRad = 0.f;
	};

	// Fire PDU (Type 2, §7.3.3)
	struct FFireEvent
	{
		std::uint16_t FiringEntity   = 0;
		std::uint16_t TargetEntity   = 0;
		std::uint16_t MunitionEntity = 0;
		std::uint16_t EventNumber    = 0;
		double        XMeters = 0.0, YMeters = 0.0, ZMeters = 0.0;
		float         VxMps   = 0.f, VyMps   = 0.f, VzMps   = 0.f;
		std::uint8_t  MunitionKind = 1;
		std::uint16_t WarheadKind  = 1000;
		std::uint16_t FuseKind     = 1000;
		std::uint16_t Quantity     = 1;
		std::uint16_t Rate         = 0;
		float         RangeMeters  = 0.f;
	};

	// Detonation PDU (Type 3, §7.3.4). Pairs with Fire by EventNumber.
	struct FDetonationEvent
	{
		std::uint16_t FiringEntity     = 0;
		std::uint16_t TargetEntity     = 0;
		std::uint16_t MunitionEntity   = 0;
		std::uint16_t EventNumber      = 0;
		double        XMeters = 0.0, YMeters = 0.0, ZMeters = 0.0;
		float         VxMps   = 0.f, VyMps   = 0.f, VzMps   = 0.f;
		std::uint8_t  MunitionKind     = 1;
		std::uint16_t WarheadKind      = 1000;
		std::uint16_t FuseKind         = 1000;
		std::uint16_t Quantity         = 1;
		std::uint16_t Rate             = 0;
		std::uint8_t  DetonationResult = 1;       // §7.3.4 table 7-4
	};

	// Emission PDU (Type 23, §7.6.2). One radar's full snapshot.
	struct FEmissionSnapshot
	{
		std::uint16_t EmittingEntity = 0;
		double        PositionMetersX = 0.0, PositionMetersY = 0.0, PositionMetersZ = 0.0;
		std::uint16_t EmitterName    = 4830;      // ASR-9 civil surveillance
		std::uint8_t  EmitterFunction = 3;        // Surveillance
		float         FrequencyLowHz     = 0.f;
		float         FrequencyHighHz    = 0.f;
		float         EffectiveRadiatedPowerDbm = 0.f;
		float         PulseRepetitionFreqHz     = 0.f;
		float         PulseWidthMicrosec        = 0.f;
		float         BeamAzimuthRad     = 0.f;
		std::uint8_t  BeamFunction       = 2;     // Search
		std::vector<std::uint16_t> PaintedEntityNumbers;
	};

	// Signal PDU (Type 26, §7.7.3). Opaque raw-binary payload.
	struct FSignalEvent
	{
		std::uint16_t OwnerEntity = 0;
		std::uint16_t RadioId     = 1;
		std::vector<std::uint8_t> Data;
	};

	// Transmitter PDU (Type 25, §7.7.2). Radio heartbeat.
	struct FTransmitterState
	{
		std::uint16_t OwnerEntity      = 0;
		std::uint16_t RadioId          = 1;
		std::uint64_t FrequencyHz      = 121500000;   // 121.500 MHz ATC guard
		float         BandwidthHz      = 25000.f;
		float         PowerDbm         = 40.f;
		std::uint8_t  TransmitState    = 1;           // 0=off 1=on-idle 2=on-transmitting
		double        AntennaXMeters = 0.0, AntennaYMeters = 0.0, AntennaZMeters = 0.0;
	};

	// Reserved entity number for operator / ground-station traffic. Both
	// Signal and Transmitter emitters use this so a federation receiver can
	// filter air-side from ground-side by entity number alone.
	inline constexpr std::uint16_t kOperatorGroundStationEntity = 60000;

	// ========================================================================
	//  Deterministic entity number derivation.
	//
	//  FNV-1a 32-bit hash of the callsign's UTF-8 bytes, mapped into the 1-65535
	//  DIS entity number range (0 is reserved for "no such entity" per §6.2.28).
	//  The same callsign always maps to the same entity number regardless of
	//  build target, so federation observers can pair traffic across sessions
	//  by entity number alone. - TripleA
	// ========================================================================
	inline constexpr std::uint32_t kFnv1aOffsetBasis = 2166136261u;
	inline constexpr std::uint32_t kFnv1aPrime       = 16777619u;

	inline std::uint32_t Fnv1a32(std::string_view Text) noexcept
	{
		std::uint32_t Hash = kFnv1aOffsetBasis;
		for (const char C : Text)
		{
			Hash ^= static_cast<std::uint32_t>(static_cast<std::uint8_t>(C));
			Hash *= kFnv1aPrime;
		}
		return Hash;
	}

	inline std::uint16_t HashCallsignToEntityNumber(std::string_view Callsign) noexcept
	{
		if (Callsign.empty()) { return 0; }
		return static_cast<std::uint16_t>((Fnv1a32(Callsign) % 65535u) + 1u);
	}

	// Munition entity number derives from firing entity + event number so a
	// Fire PDU and its matching Detonation PDU carry the same munition ID
	// without either side needing shared state. - TripleA
	inline std::uint16_t DeriveMunitionEntityNumber(std::uint16_t FiringEntity, std::uint32_t EventNumber) noexcept
	{
		const std::uint32_t Mixed = (static_cast<std::uint32_t>(FiringEntity) * 65521u) ^ EventNumber;
		return static_cast<std::uint16_t>((Mixed % 65535u) + 1u);
	}

	// ========================================================================
	//  Serialisers - each builds a spec-conformant byte buffer ready for UDP.
	// ========================================================================
	CLEARANCEDIS_API std::vector<std::uint8_t> BuildEntityStatePDU(const FEntityState& S,       const FWireParams& Params);
	CLEARANCEDIS_API std::vector<std::uint8_t> BuildFirePDU       (const FFireEvent& E,         const FWireParams& Params);
	CLEARANCEDIS_API std::vector<std::uint8_t> BuildDetonationPDU (const FDetonationEvent& E,   const FWireParams& Params);
	CLEARANCEDIS_API std::vector<std::uint8_t> BuildEmissionPDU   (const FEmissionSnapshot& S,  const FWireParams& Params);
	CLEARANCEDIS_API std::vector<std::uint8_t> BuildSignalPDU     (const FSignalEvent& E,       const FWireParams& Params);
	CLEARANCEDIS_API std::vector<std::uint8_t> BuildTransmitterPDU(const FTransmitterState& R,  const FWireParams& Params);

	// ========================================================================
	//  Parsers - decode a raw byte buffer back into a POD struct. Return false
	//  on protocol version / PDU type / family / length mismatch or on
	//  truncated input. Buffer can come from any transport (UDP recvfrom, TCP
	//  stream, replay file, memory buffer). - TripleA
	// ========================================================================
	CLEARANCEDIS_API bool ParseFirePDU       (const std::uint8_t* Buf, std::size_t Len, FFireEvent& Out);
	CLEARANCEDIS_API bool ParseDetonationPDU (const std::uint8_t* Buf, std::size_t Len, FDetonationEvent& Out);
	CLEARANCEDIS_API bool ParseEmissionPDU   (const std::uint8_t* Buf, std::size_t Len, FEmissionSnapshot& Out);
	CLEARANCEDIS_API bool ParseSignalPDU     (const std::uint8_t* Buf, std::size_t Len, FSignalEvent& Out);
	CLEARANCEDIS_API bool ParseTransmitterPDU(const std::uint8_t* Buf, std::size_t Len, FTransmitterState& Out);
}
