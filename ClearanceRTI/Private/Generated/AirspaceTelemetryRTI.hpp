

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from AirspaceTelemetryRTI.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef AirspaceTelemetryRTI_1287320769_hpp
#define AirspaceTelemetryRTI_1287320769_hpp

#include <iosfwd>

#if defined(NDDS_USER_DLL_EXPORT) && defined(RTI_WIN32)
#undef RTIUSERDllExport
#define RTIUSERDllExport __declspec(dllexport)
#endif

#if !defined(RTI_WIN32) && defined(NDDS_USER_SYMBOL_EXPORT)
#undef RTIUSERDllExport
#define RTIUSERDllExport __attribute__((visibility("default")))
#endif

#include "dds/core/SafeEnumeration.hpp"
#include "dds/core/String.hpp"
#include "dds/core/array.hpp"
#include "dds/core/vector.hpp"
#include "dds/core/External.hpp"
#include "rti/core/LongDouble.hpp"
#include "rti/core/Pointer.hpp"
#include "rti/core/array.hpp"
#include "rti/topic/TopicTraits.hpp"

#include "omg/types/string_view.hpp"

#include "omg/types/sequence.hpp"
#include "omg/types/optional.hpp"

#ifndef NDDS_STANDALONE_TYPE
#include "cdr/cdr_typeCode.h"
#include "dds/domain/DomainParticipant.hpp"
#include "dds/topic/TopicTraits.hpp"
#include "dds/core/xtypes/DynamicType.hpp"
#include "dds/core/xtypes/StructType.hpp"
#include "dds/core/xtypes/UnionType.hpp"
#include "dds/core/xtypes/EnumType.hpp"
#include "dds/core/xtypes/AliasType.hpp"
#include "rti/util/StreamFlagSaver.hpp"
#include "rti/domain/PluginSupport.hpp"
#endif

#if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
#undef RTIUSERDllExport
#define RTIUSERDllExport
#endif

#if defined(NDDS_USER_DLL_EXPORT) && defined(RTI_WIN32)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#if !defined(RTI_WIN32) && defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __attribute__((visibility("default")))
#endif

namespace ClearanceRTI {

    struct NDDSUSERDllExport WireHeader {
        uint8_t ExerciseId {};
        uint16_t SiteId {};
        uint16_t ApplicationId {};
        double SimTimeSeconds {};

        WireHeader();

        WireHeader(uint8_t ExerciseId_,uint16_t SiteId_,uint16_t ApplicationId_,double SimTimeSeconds_);

    };

    NDDSUSERDllExport bool operator == (const WireHeader& a, const WireHeader& b);
    NDDSUSERDllExport bool operator != (const WireHeader& a, const WireHeader& b);
    NDDSUSERDllExport void swap(WireHeader& a, WireHeader& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const WireHeader& sample);

    struct NDDSUSERDllExport AircraftState {
        ::ClearanceRTI::WireHeader Header {};
        uint16_t EntityNumber {};
        std::string Marking {};
        uint8_t ForceId {};
        uint8_t EntityKind {};
        uint8_t EntityDomain {};
        uint16_t EntityCountry {};
        uint8_t EntityCategory {};
        uint8_t EntitySubcategory {};
        uint8_t EntitySpecific {};
        uint8_t EntityExtra {};
        double XMeters {};
        double YMeters {};
        double ZMeters {};
        float VxMps {};
        float VyMps {};
        float VzMps {};
        float PsiRad {};
        float ThetaRad {};
        float PhiRad {};
        uint8_t TrueAffiliation {};
        uint16_t SquawkCode {};
        uint8_t ActiveEmergency {};
        uint8_t FlightPhase {};

        AircraftState();

        AircraftState(const ::ClearanceRTI::WireHeader& Header_,uint16_t EntityNumber_,const ::omg::types::string_view& Marking_,uint8_t ForceId_,uint8_t EntityKind_,uint8_t EntityDomain_,uint16_t EntityCountry_,uint8_t EntityCategory_,uint8_t EntitySubcategory_,uint8_t EntitySpecific_,uint8_t EntityExtra_,double XMeters_,double YMeters_,double ZMeters_,float VxMps_,float VyMps_,float VzMps_,float PsiRad_,float ThetaRad_,float PhiRad_,uint8_t TrueAffiliation_,uint16_t SquawkCode_,uint8_t ActiveEmergency_,uint8_t FlightPhase_);

    };

    NDDSUSERDllExport bool operator == (const AircraftState& a, const AircraftState& b);
    NDDSUSERDllExport bool operator != (const AircraftState& a, const AircraftState& b);
    NDDSUSERDllExport void swap(AircraftState& a, AircraftState& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const AircraftState& sample);

    struct NDDSUSERDllExport FireEvent {
        ::ClearanceRTI::WireHeader Header {};
        uint16_t FiringEntity {};
        uint16_t TargetEntity {};
        uint16_t MunitionEntity {};
        uint16_t EventNumber {};
        double XMeters {};
        double YMeters {};
        double ZMeters {};
        float VxMps {};
        float VyMps {};
        float VzMps {};
        uint8_t MunitionKind {};
        uint16_t WarheadKind {};
        uint16_t FuseKind {};
        uint16_t Quantity {};
        uint16_t Rate {};
        float RangeMeters {};

        FireEvent();

        FireEvent(const ::ClearanceRTI::WireHeader& Header_,uint16_t FiringEntity_,uint16_t TargetEntity_,uint16_t MunitionEntity_,uint16_t EventNumber_,double XMeters_,double YMeters_,double ZMeters_,float VxMps_,float VyMps_,float VzMps_,uint8_t MunitionKind_,uint16_t WarheadKind_,uint16_t FuseKind_,uint16_t Quantity_,uint16_t Rate_,float RangeMeters_);

    };

    NDDSUSERDllExport bool operator == (const FireEvent& a, const FireEvent& b);
    NDDSUSERDllExport bool operator != (const FireEvent& a, const FireEvent& b);
    NDDSUSERDllExport void swap(FireEvent& a, FireEvent& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const FireEvent& sample);

    struct NDDSUSERDllExport DetonationEvent {
        ::ClearanceRTI::WireHeader Header {};
        uint16_t FiringEntity {};
        uint16_t TargetEntity {};
        uint16_t MunitionEntity {};
        uint16_t EventNumber {};
        double XMeters {};
        double YMeters {};
        double ZMeters {};
        float VxMps {};
        float VyMps {};
        float VzMps {};
        uint8_t MunitionKind {};
        uint16_t WarheadKind {};
        uint16_t FuseKind {};
        uint16_t Quantity {};
        uint16_t Rate {};
        uint8_t DetonationResult {};

        DetonationEvent();

        DetonationEvent(const ::ClearanceRTI::WireHeader& Header_,uint16_t FiringEntity_,uint16_t TargetEntity_,uint16_t MunitionEntity_,uint16_t EventNumber_,double XMeters_,double YMeters_,double ZMeters_,float VxMps_,float VyMps_,float VzMps_,uint8_t MunitionKind_,uint16_t WarheadKind_,uint16_t FuseKind_,uint16_t Quantity_,uint16_t Rate_,uint8_t DetonationResult_);

    };

    NDDSUSERDllExport bool operator == (const DetonationEvent& a, const DetonationEvent& b);
    NDDSUSERDllExport bool operator != (const DetonationEvent& a, const DetonationEvent& b);
    NDDSUSERDllExport void swap(DetonationEvent& a, DetonationEvent& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const DetonationEvent& sample);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    // On Windows, dll-export template instantiations of standard types used by
    // other dll-exported types
    template class NDDSUSERDllExport std::allocator< uint16_t >;
    template class NDDSUSERDllExport std::vector< uint16_t >;
    #endif
    struct NDDSUSERDllExport EmissionSnapshot {
        ::ClearanceRTI::WireHeader Header {};
        uint16_t EmittingEntity {};
        double PositionMetersX {};
        double PositionMetersY {};
        double PositionMetersZ {};
        uint16_t EmitterName {};
        uint8_t EmitterFunction {};
        float FrequencyLowHz {};
        float FrequencyHighHz {};
        float EffectiveRadiatedPowerDbm {};
        float PulseRepetitionFreqHz {};
        float PulseWidthMicrosec {};
        float BeamAzimuthRad {};
        uint8_t BeamFunction {};
        ::omg::types::bounded_sequence< uint16_t, 100L > PaintedEntityNumbers {};

        EmissionSnapshot();

        EmissionSnapshot(const ::ClearanceRTI::WireHeader& Header_,uint16_t EmittingEntity_,double PositionMetersX_,double PositionMetersY_,double PositionMetersZ_,uint16_t EmitterName_,uint8_t EmitterFunction_,float FrequencyLowHz_,float FrequencyHighHz_,float EffectiveRadiatedPowerDbm_,float PulseRepetitionFreqHz_,float PulseWidthMicrosec_,float BeamAzimuthRad_,uint8_t BeamFunction_,const ::omg::types::bounded_sequence< uint16_t, 100L >& PaintedEntityNumbers_);

    };

    NDDSUSERDllExport bool operator == (const EmissionSnapshot& a, const EmissionSnapshot& b);
    NDDSUSERDllExport bool operator != (const EmissionSnapshot& a, const EmissionSnapshot& b);
    NDDSUSERDllExport void swap(EmissionSnapshot& a, EmissionSnapshot& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const EmissionSnapshot& sample);

    struct NDDSUSERDllExport TransmitterState {
        ::ClearanceRTI::WireHeader Header {};
        uint16_t OwnerEntity {};
        uint16_t RadioId {};
        uint64_t FrequencyHz {};
        float BandwidthHz {};
        float PowerDbm {};
        uint8_t TransmitState {};
        double AntennaXMeters {};
        double AntennaYMeters {};
        double AntennaZMeters {};

        TransmitterState();

        TransmitterState(const ::ClearanceRTI::WireHeader& Header_,uint16_t OwnerEntity_,uint16_t RadioId_,uint64_t FrequencyHz_,float BandwidthHz_,float PowerDbm_,uint8_t TransmitState_,double AntennaXMeters_,double AntennaYMeters_,double AntennaZMeters_);

    };

    NDDSUSERDllExport bool operator == (const TransmitterState& a, const TransmitterState& b);
    NDDSUSERDllExport bool operator != (const TransmitterState& a, const TransmitterState& b);
    NDDSUSERDllExport void swap(TransmitterState& a, TransmitterState& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const TransmitterState& sample);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    // On Windows, dll-export template instantiations of standard types used by
    // other dll-exported types
    template class NDDSUSERDllExport std::allocator< uint8_t >;
    template class NDDSUSERDllExport std::vector< uint8_t >;
    #endif
    struct NDDSUSERDllExport SignalEvent {
        ::ClearanceRTI::WireHeader Header {};
        uint16_t OwnerEntity {};
        uint16_t RadioId {};
        ::omg::types::bounded_sequence< uint8_t, 100L > Data {};

        SignalEvent();

        SignalEvent(const ::ClearanceRTI::WireHeader& Header_,uint16_t OwnerEntity_,uint16_t RadioId_,const ::omg::types::bounded_sequence< uint8_t, 100L >& Data_);

    };

    NDDSUSERDllExport bool operator == (const SignalEvent& a, const SignalEvent& b);
    NDDSUSERDllExport bool operator != (const SignalEvent& a, const SignalEvent& b);
    NDDSUSERDllExport void swap(SignalEvent& a, SignalEvent& b)  noexcept;

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const SignalEvent& sample);

} // namespace ClearanceRTI  

#ifdef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace topic {
    }
}
#else

namespace rti {
    namespace flat {
        namespace topic {
        }
    }
}
namespace dds {
    namespace topic {

        template<>
        struct topic_type_name< ::ClearanceRTI::WireHeader > {
            NDDSUSERDllExport static std::string value() {
                return "ClearanceRTI::WireHeader";
            }
        };

        template<>
        struct is_topic_type< ::ClearanceRTI::WireHeader > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::ClearanceRTI::WireHeader > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::ClearanceRTI::WireHeader& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::ClearanceRTI::WireHeader& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::ClearanceRTI::WireHeader& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::ClearanceRTI::WireHeader& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::ClearanceRTI::AircraftState > {
            NDDSUSERDllExport static std::string value() {
                return "ClearanceRTI::AircraftState";
            }
        };

        template<>
        struct is_topic_type< ::ClearanceRTI::AircraftState > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::ClearanceRTI::AircraftState > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::ClearanceRTI::AircraftState& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::ClearanceRTI::AircraftState& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::ClearanceRTI::AircraftState& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::ClearanceRTI::AircraftState& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::ClearanceRTI::FireEvent > {
            NDDSUSERDllExport static std::string value() {
                return "ClearanceRTI::FireEvent";
            }
        };

        template<>
        struct is_topic_type< ::ClearanceRTI::FireEvent > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::ClearanceRTI::FireEvent > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::ClearanceRTI::FireEvent& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::ClearanceRTI::FireEvent& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::ClearanceRTI::FireEvent& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::ClearanceRTI::FireEvent& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::ClearanceRTI::DetonationEvent > {
            NDDSUSERDllExport static std::string value() {
                return "ClearanceRTI::DetonationEvent";
            }
        };

        template<>
        struct is_topic_type< ::ClearanceRTI::DetonationEvent > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::ClearanceRTI::DetonationEvent > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::ClearanceRTI::DetonationEvent& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::ClearanceRTI::DetonationEvent& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::ClearanceRTI::DetonationEvent& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::ClearanceRTI::DetonationEvent& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::ClearanceRTI::EmissionSnapshot > {
            NDDSUSERDllExport static std::string value() {
                return "ClearanceRTI::EmissionSnapshot";
            }
        };

        template<>
        struct is_topic_type< ::ClearanceRTI::EmissionSnapshot > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::ClearanceRTI::EmissionSnapshot > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::ClearanceRTI::EmissionSnapshot& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::ClearanceRTI::EmissionSnapshot& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::ClearanceRTI::EmissionSnapshot& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::ClearanceRTI::EmissionSnapshot& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::ClearanceRTI::TransmitterState > {
            NDDSUSERDllExport static std::string value() {
                return "ClearanceRTI::TransmitterState";
            }
        };

        template<>
        struct is_topic_type< ::ClearanceRTI::TransmitterState > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::ClearanceRTI::TransmitterState > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::ClearanceRTI::TransmitterState& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::ClearanceRTI::TransmitterState& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::ClearanceRTI::TransmitterState& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::ClearanceRTI::TransmitterState& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::ClearanceRTI::SignalEvent > {
            NDDSUSERDllExport static std::string value() {
                return "ClearanceRTI::SignalEvent";
            }
        };

        template<>
        struct is_topic_type< ::ClearanceRTI::SignalEvent > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::ClearanceRTI::SignalEvent > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::ClearanceRTI::SignalEvent& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::ClearanceRTI::SignalEvent& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::ClearanceRTI::SignalEvent& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::ClearanceRTI::SignalEvent& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
    }
}

namespace rti { 
    namespace topic {

        template<>
        struct dynamic_type< ::ClearanceRTI::WireHeader > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::ClearanceRTI::WireHeader > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::ClearanceRTI::AircraftState > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::ClearanceRTI::AircraftState > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::ClearanceRTI::FireEvent > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::ClearanceRTI::FireEvent > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::ClearanceRTI::DetonationEvent > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::ClearanceRTI::DetonationEvent > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::ClearanceRTI::EmissionSnapshot > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::ClearanceRTI::EmissionSnapshot > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::ClearanceRTI::TransmitterState > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::ClearanceRTI::TransmitterState > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::ClearanceRTI::SignalEvent > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::ClearanceRTI::SignalEvent > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

    }
}

#endif // NDDS_STANDALONE_TYPE
#if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif // AirspaceTelemetryRTI_1287320769_hpp
