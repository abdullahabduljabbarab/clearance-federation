

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from AirspaceTelemetryRTI.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include <iosfwd>
#include <iomanip>
#include <atomic>
#include <cmath>
#include <limits>

#ifndef NDDS_STANDALONE_TYPE
#include "rti/topic/cdr/Serialization.hpp"
#include "AirspaceTelemetryRTIPlugin.hpp"
#else
#include "rti/topic/cdr/SerializationHelpers.hpp"
#endif

#include "AirspaceTelemetryRTI.hpp"

#include <rti/util/ostream_operators.hpp>

namespace ClearanceRTI {

    // ---- WireHeader:

    WireHeader::WireHeader() :
        ExerciseId (0) ,
        SiteId (0) ,
        ApplicationId (0) ,
        SimTimeSeconds (0.0)  {

    }

    WireHeader::WireHeader (uint8_t ExerciseId_,uint16_t SiteId_,uint16_t ApplicationId_,double SimTimeSeconds_) {
        ExerciseId = ExerciseId_;
        SiteId = SiteId_;
        ApplicationId = ApplicationId_;
        SimTimeSeconds = SimTimeSeconds_;
    }

    bool operator == (const WireHeader& a, const WireHeader& b) {

        if (a.ExerciseId != b.ExerciseId) {
            return false;
        }
        if (a.SiteId != b.SiteId) {
            return false;
        }
        if (a.ApplicationId != b.ApplicationId) {
            return false;
        }
        if (std::fabs(a.SimTimeSeconds - b.SimTimeSeconds) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.SimTimeSeconds - b.SimTimeSeconds) < (std::numeric_limits< double>::min)())) {
            return false;
        }

        return true;
    }

    bool operator != (const WireHeader& a, const WireHeader& b) {
        return !operator ==(a, b);
    }

    void swap(WireHeader& a, WireHeader& b) noexcept
    {
        using std::swap;

        swap(a.ExerciseId, b.ExerciseId);
        swap(a.SiteId, b.SiteId);
        swap(a.ApplicationId, b.ApplicationId);
        swap(a.SimTimeSeconds, b.SimTimeSeconds);

    }  
    std::ostream& operator << (std::ostream& o,const WireHeader& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "ExerciseId: " << std::hex<<(int)  sample.ExerciseId <<", ";
        o << "SiteId: " << sample.SiteId<<", ";
        o << "ApplicationId: " << sample.ApplicationId<<", ";
        o << "SimTimeSeconds: " << std::setprecision(15) << sample.SimTimeSeconds;
        o <<"]";
        return o;
    }

    // ---- AircraftState:

    AircraftState::AircraftState() :
        EntityNumber (0) ,
        Marking ("") ,
        ForceId (0) ,
        EntityKind (0) ,
        EntityDomain (0) ,
        EntityCountry (0) ,
        EntityCategory (0) ,
        EntitySubcategory (0) ,
        EntitySpecific (0) ,
        EntityExtra (0) ,
        XMeters (0.0) ,
        YMeters (0.0) ,
        ZMeters (0.0) ,
        VxMps (0.0f) ,
        VyMps (0.0f) ,
        VzMps (0.0f) ,
        PsiRad (0.0f) ,
        ThetaRad (0.0f) ,
        PhiRad (0.0f) ,
        TrueAffiliation (0) ,
        SquawkCode (0) ,
        ActiveEmergency (0) ,
        FlightPhase (0)  {

    }

    AircraftState::AircraftState (const ::ClearanceRTI::WireHeader& Header_,uint16_t EntityNumber_,const ::omg::types::string_view& Marking_,uint8_t ForceId_,uint8_t EntityKind_,uint8_t EntityDomain_,uint16_t EntityCountry_,uint8_t EntityCategory_,uint8_t EntitySubcategory_,uint8_t EntitySpecific_,uint8_t EntityExtra_,double XMeters_,double YMeters_,double ZMeters_,float VxMps_,float VyMps_,float VzMps_,float PsiRad_,float ThetaRad_,float PhiRad_,uint8_t TrueAffiliation_,uint16_t SquawkCode_,uint8_t ActiveEmergency_,uint8_t FlightPhase_) {
        Header = Header_;
        EntityNumber = EntityNumber_;
        Marking = Marking_;
        ForceId = ForceId_;
        EntityKind = EntityKind_;
        EntityDomain = EntityDomain_;
        EntityCountry = EntityCountry_;
        EntityCategory = EntityCategory_;
        EntitySubcategory = EntitySubcategory_;
        EntitySpecific = EntitySpecific_;
        EntityExtra = EntityExtra_;
        XMeters = XMeters_;
        YMeters = YMeters_;
        ZMeters = ZMeters_;
        VxMps = VxMps_;
        VyMps = VyMps_;
        VzMps = VzMps_;
        PsiRad = PsiRad_;
        ThetaRad = ThetaRad_;
        PhiRad = PhiRad_;
        TrueAffiliation = TrueAffiliation_;
        SquawkCode = SquawkCode_;
        ActiveEmergency = ActiveEmergency_;
        FlightPhase = FlightPhase_;
    }

    bool operator == (const AircraftState& a, const AircraftState& b) {

        if (a.Header != b.Header) {
            return false;
        }
        if (a.EntityNumber != b.EntityNumber) {
            return false;
        }
        if (a.Marking != b.Marking) {
            return false;
        }
        if (a.ForceId != b.ForceId) {
            return false;
        }
        if (a.EntityKind != b.EntityKind) {
            return false;
        }
        if (a.EntityDomain != b.EntityDomain) {
            return false;
        }
        if (a.EntityCountry != b.EntityCountry) {
            return false;
        }
        if (a.EntityCategory != b.EntityCategory) {
            return false;
        }
        if (a.EntitySubcategory != b.EntitySubcategory) {
            return false;
        }
        if (a.EntitySpecific != b.EntitySpecific) {
            return false;
        }
        if (a.EntityExtra != b.EntityExtra) {
            return false;
        }
        if (std::fabs(a.XMeters - b.XMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.XMeters - b.XMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.YMeters - b.YMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.YMeters - b.YMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.ZMeters - b.ZMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.ZMeters - b.ZMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.VxMps - b.VxMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VxMps - b.VxMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.VyMps - b.VyMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VyMps - b.VyMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.VzMps - b.VzMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VzMps - b.VzMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.PsiRad - b.PsiRad) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.PsiRad - b.PsiRad) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.ThetaRad - b.ThetaRad) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.ThetaRad - b.ThetaRad) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.PhiRad - b.PhiRad) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.PhiRad - b.PhiRad) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (a.TrueAffiliation != b.TrueAffiliation) {
            return false;
        }
        if (a.SquawkCode != b.SquawkCode) {
            return false;
        }
        if (a.ActiveEmergency != b.ActiveEmergency) {
            return false;
        }
        if (a.FlightPhase != b.FlightPhase) {
            return false;
        }

        return true;
    }

    bool operator != (const AircraftState& a, const AircraftState& b) {
        return !operator ==(a, b);
    }

    void swap(AircraftState& a, AircraftState& b) noexcept
    {
        using std::swap;

        swap(a.Header, b.Header);
        swap(a.EntityNumber, b.EntityNumber);
        swap(a.Marking, b.Marking);
        swap(a.ForceId, b.ForceId);
        swap(a.EntityKind, b.EntityKind);
        swap(a.EntityDomain, b.EntityDomain);
        swap(a.EntityCountry, b.EntityCountry);
        swap(a.EntityCategory, b.EntityCategory);
        swap(a.EntitySubcategory, b.EntitySubcategory);
        swap(a.EntitySpecific, b.EntitySpecific);
        swap(a.EntityExtra, b.EntityExtra);
        swap(a.XMeters, b.XMeters);
        swap(a.YMeters, b.YMeters);
        swap(a.ZMeters, b.ZMeters);
        swap(a.VxMps, b.VxMps);
        swap(a.VyMps, b.VyMps);
        swap(a.VzMps, b.VzMps);
        swap(a.PsiRad, b.PsiRad);
        swap(a.ThetaRad, b.ThetaRad);
        swap(a.PhiRad, b.PhiRad);
        swap(a.TrueAffiliation, b.TrueAffiliation);
        swap(a.SquawkCode, b.SquawkCode);
        swap(a.ActiveEmergency, b.ActiveEmergency);
        swap(a.FlightPhase, b.FlightPhase);

    }  
    std::ostream& operator << (std::ostream& o,const AircraftState& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "Header: " << sample.Header<<", ";
        o << "EntityNumber: " << sample.EntityNumber<<", ";
        o << "Marking: " << sample.Marking<<", ";
        o << "ForceId: " << std::hex<<(int)  sample.ForceId <<", ";
        o << "EntityKind: " << std::hex<<(int)  sample.EntityKind <<", ";
        o << "EntityDomain: " << std::hex<<(int)  sample.EntityDomain <<", ";
        o << "EntityCountry: " << sample.EntityCountry<<", ";
        o << "EntityCategory: " << std::hex<<(int)  sample.EntityCategory <<", ";
        o << "EntitySubcategory: " << std::hex<<(int)  sample.EntitySubcategory <<", ";
        o << "EntitySpecific: " << std::hex<<(int)  sample.EntitySpecific <<", ";
        o << "EntityExtra: " << std::hex<<(int)  sample.EntityExtra <<", ";
        o << "XMeters: " << std::setprecision(15) << sample.XMeters<<", ";
        o << "YMeters: " << std::setprecision(15) << sample.YMeters<<", ";
        o << "ZMeters: " << std::setprecision(15) << sample.ZMeters<<", ";
        o << "VxMps: " << std::setprecision(9) << sample.VxMps<<", ";
        o << "VyMps: " << std::setprecision(9) << sample.VyMps<<", ";
        o << "VzMps: " << std::setprecision(9) << sample.VzMps<<", ";
        o << "PsiRad: " << std::setprecision(9) << sample.PsiRad<<", ";
        o << "ThetaRad: " << std::setprecision(9) << sample.ThetaRad<<", ";
        o << "PhiRad: " << std::setprecision(9) << sample.PhiRad<<", ";
        o << "TrueAffiliation: " << std::hex<<(int)  sample.TrueAffiliation <<", ";
        o << "SquawkCode: " << sample.SquawkCode<<", ";
        o << "ActiveEmergency: " << std::hex<<(int)  sample.ActiveEmergency <<", ";
        o << "FlightPhase: " << std::hex<<(int)  sample.FlightPhase ;
        o <<"]";
        return o;
    }

    // ---- FireEvent:

    FireEvent::FireEvent() :
        FiringEntity (0) ,
        TargetEntity (0) ,
        MunitionEntity (0) ,
        EventNumber (0) ,
        XMeters (0.0) ,
        YMeters (0.0) ,
        ZMeters (0.0) ,
        VxMps (0.0f) ,
        VyMps (0.0f) ,
        VzMps (0.0f) ,
        MunitionKind (0) ,
        WarheadKind (0) ,
        FuseKind (0) ,
        Quantity (0) ,
        Rate (0) ,
        RangeMeters (0.0f)  {

    }

    FireEvent::FireEvent (const ::ClearanceRTI::WireHeader& Header_,uint16_t FiringEntity_,uint16_t TargetEntity_,uint16_t MunitionEntity_,uint16_t EventNumber_,double XMeters_,double YMeters_,double ZMeters_,float VxMps_,float VyMps_,float VzMps_,uint8_t MunitionKind_,uint16_t WarheadKind_,uint16_t FuseKind_,uint16_t Quantity_,uint16_t Rate_,float RangeMeters_) {
        Header = Header_;
        FiringEntity = FiringEntity_;
        TargetEntity = TargetEntity_;
        MunitionEntity = MunitionEntity_;
        EventNumber = EventNumber_;
        XMeters = XMeters_;
        YMeters = YMeters_;
        ZMeters = ZMeters_;
        VxMps = VxMps_;
        VyMps = VyMps_;
        VzMps = VzMps_;
        MunitionKind = MunitionKind_;
        WarheadKind = WarheadKind_;
        FuseKind = FuseKind_;
        Quantity = Quantity_;
        Rate = Rate_;
        RangeMeters = RangeMeters_;
    }

    bool operator == (const FireEvent& a, const FireEvent& b) {

        if (a.Header != b.Header) {
            return false;
        }
        if (a.FiringEntity != b.FiringEntity) {
            return false;
        }
        if (a.TargetEntity != b.TargetEntity) {
            return false;
        }
        if (a.MunitionEntity != b.MunitionEntity) {
            return false;
        }
        if (a.EventNumber != b.EventNumber) {
            return false;
        }
        if (std::fabs(a.XMeters - b.XMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.XMeters - b.XMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.YMeters - b.YMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.YMeters - b.YMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.ZMeters - b.ZMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.ZMeters - b.ZMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.VxMps - b.VxMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VxMps - b.VxMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.VyMps - b.VyMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VyMps - b.VyMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.VzMps - b.VzMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VzMps - b.VzMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (a.MunitionKind != b.MunitionKind) {
            return false;
        }
        if (a.WarheadKind != b.WarheadKind) {
            return false;
        }
        if (a.FuseKind != b.FuseKind) {
            return false;
        }
        if (a.Quantity != b.Quantity) {
            return false;
        }
        if (a.Rate != b.Rate) {
            return false;
        }
        if (std::fabs(a.RangeMeters - b.RangeMeters) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.RangeMeters - b.RangeMeters) < (std::numeric_limits< float>::min)())) {
            return false;
        }

        return true;
    }

    bool operator != (const FireEvent& a, const FireEvent& b) {
        return !operator ==(a, b);
    }

    void swap(FireEvent& a, FireEvent& b) noexcept
    {
        using std::swap;

        swap(a.Header, b.Header);
        swap(a.FiringEntity, b.FiringEntity);
        swap(a.TargetEntity, b.TargetEntity);
        swap(a.MunitionEntity, b.MunitionEntity);
        swap(a.EventNumber, b.EventNumber);
        swap(a.XMeters, b.XMeters);
        swap(a.YMeters, b.YMeters);
        swap(a.ZMeters, b.ZMeters);
        swap(a.VxMps, b.VxMps);
        swap(a.VyMps, b.VyMps);
        swap(a.VzMps, b.VzMps);
        swap(a.MunitionKind, b.MunitionKind);
        swap(a.WarheadKind, b.WarheadKind);
        swap(a.FuseKind, b.FuseKind);
        swap(a.Quantity, b.Quantity);
        swap(a.Rate, b.Rate);
        swap(a.RangeMeters, b.RangeMeters);

    }  
    std::ostream& operator << (std::ostream& o,const FireEvent& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "Header: " << sample.Header<<", ";
        o << "FiringEntity: " << sample.FiringEntity<<", ";
        o << "TargetEntity: " << sample.TargetEntity<<", ";
        o << "MunitionEntity: " << sample.MunitionEntity<<", ";
        o << "EventNumber: " << sample.EventNumber<<", ";
        o << "XMeters: " << std::setprecision(15) << sample.XMeters<<", ";
        o << "YMeters: " << std::setprecision(15) << sample.YMeters<<", ";
        o << "ZMeters: " << std::setprecision(15) << sample.ZMeters<<", ";
        o << "VxMps: " << std::setprecision(9) << sample.VxMps<<", ";
        o << "VyMps: " << std::setprecision(9) << sample.VyMps<<", ";
        o << "VzMps: " << std::setprecision(9) << sample.VzMps<<", ";
        o << "MunitionKind: " << std::hex<<(int)  sample.MunitionKind <<", ";
        o << "WarheadKind: " << sample.WarheadKind<<", ";
        o << "FuseKind: " << sample.FuseKind<<", ";
        o << "Quantity: " << sample.Quantity<<", ";
        o << "Rate: " << sample.Rate<<", ";
        o << "RangeMeters: " << std::setprecision(9) << sample.RangeMeters;
        o <<"]";
        return o;
    }

    // ---- DetonationEvent:

    DetonationEvent::DetonationEvent() :
        FiringEntity (0) ,
        TargetEntity (0) ,
        MunitionEntity (0) ,
        EventNumber (0) ,
        XMeters (0.0) ,
        YMeters (0.0) ,
        ZMeters (0.0) ,
        VxMps (0.0f) ,
        VyMps (0.0f) ,
        VzMps (0.0f) ,
        MunitionKind (0) ,
        WarheadKind (0) ,
        FuseKind (0) ,
        Quantity (0) ,
        Rate (0) ,
        DetonationResult (0)  {

    }

    DetonationEvent::DetonationEvent (const ::ClearanceRTI::WireHeader& Header_,uint16_t FiringEntity_,uint16_t TargetEntity_,uint16_t MunitionEntity_,uint16_t EventNumber_,double XMeters_,double YMeters_,double ZMeters_,float VxMps_,float VyMps_,float VzMps_,uint8_t MunitionKind_,uint16_t WarheadKind_,uint16_t FuseKind_,uint16_t Quantity_,uint16_t Rate_,uint8_t DetonationResult_) {
        Header = Header_;
        FiringEntity = FiringEntity_;
        TargetEntity = TargetEntity_;
        MunitionEntity = MunitionEntity_;
        EventNumber = EventNumber_;
        XMeters = XMeters_;
        YMeters = YMeters_;
        ZMeters = ZMeters_;
        VxMps = VxMps_;
        VyMps = VyMps_;
        VzMps = VzMps_;
        MunitionKind = MunitionKind_;
        WarheadKind = WarheadKind_;
        FuseKind = FuseKind_;
        Quantity = Quantity_;
        Rate = Rate_;
        DetonationResult = DetonationResult_;
    }

    bool operator == (const DetonationEvent& a, const DetonationEvent& b) {

        if (a.Header != b.Header) {
            return false;
        }
        if (a.FiringEntity != b.FiringEntity) {
            return false;
        }
        if (a.TargetEntity != b.TargetEntity) {
            return false;
        }
        if (a.MunitionEntity != b.MunitionEntity) {
            return false;
        }
        if (a.EventNumber != b.EventNumber) {
            return false;
        }
        if (std::fabs(a.XMeters - b.XMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.XMeters - b.XMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.YMeters - b.YMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.YMeters - b.YMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.ZMeters - b.ZMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.ZMeters - b.ZMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.VxMps - b.VxMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VxMps - b.VxMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.VyMps - b.VyMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VyMps - b.VyMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.VzMps - b.VzMps) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.VzMps - b.VzMps) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (a.MunitionKind != b.MunitionKind) {
            return false;
        }
        if (a.WarheadKind != b.WarheadKind) {
            return false;
        }
        if (a.FuseKind != b.FuseKind) {
            return false;
        }
        if (a.Quantity != b.Quantity) {
            return false;
        }
        if (a.Rate != b.Rate) {
            return false;
        }
        if (a.DetonationResult != b.DetonationResult) {
            return false;
        }

        return true;
    }

    bool operator != (const DetonationEvent& a, const DetonationEvent& b) {
        return !operator ==(a, b);
    }

    void swap(DetonationEvent& a, DetonationEvent& b) noexcept
    {
        using std::swap;

        swap(a.Header, b.Header);
        swap(a.FiringEntity, b.FiringEntity);
        swap(a.TargetEntity, b.TargetEntity);
        swap(a.MunitionEntity, b.MunitionEntity);
        swap(a.EventNumber, b.EventNumber);
        swap(a.XMeters, b.XMeters);
        swap(a.YMeters, b.YMeters);
        swap(a.ZMeters, b.ZMeters);
        swap(a.VxMps, b.VxMps);
        swap(a.VyMps, b.VyMps);
        swap(a.VzMps, b.VzMps);
        swap(a.MunitionKind, b.MunitionKind);
        swap(a.WarheadKind, b.WarheadKind);
        swap(a.FuseKind, b.FuseKind);
        swap(a.Quantity, b.Quantity);
        swap(a.Rate, b.Rate);
        swap(a.DetonationResult, b.DetonationResult);

    }  
    std::ostream& operator << (std::ostream& o,const DetonationEvent& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "Header: " << sample.Header<<", ";
        o << "FiringEntity: " << sample.FiringEntity<<", ";
        o << "TargetEntity: " << sample.TargetEntity<<", ";
        o << "MunitionEntity: " << sample.MunitionEntity<<", ";
        o << "EventNumber: " << sample.EventNumber<<", ";
        o << "XMeters: " << std::setprecision(15) << sample.XMeters<<", ";
        o << "YMeters: " << std::setprecision(15) << sample.YMeters<<", ";
        o << "ZMeters: " << std::setprecision(15) << sample.ZMeters<<", ";
        o << "VxMps: " << std::setprecision(9) << sample.VxMps<<", ";
        o << "VyMps: " << std::setprecision(9) << sample.VyMps<<", ";
        o << "VzMps: " << std::setprecision(9) << sample.VzMps<<", ";
        o << "MunitionKind: " << std::hex<<(int)  sample.MunitionKind <<", ";
        o << "WarheadKind: " << sample.WarheadKind<<", ";
        o << "FuseKind: " << sample.FuseKind<<", ";
        o << "Quantity: " << sample.Quantity<<", ";
        o << "Rate: " << sample.Rate<<", ";
        o << "DetonationResult: " << std::hex<<(int)  sample.DetonationResult ;
        o <<"]";
        return o;
    }

    // ---- EmissionSnapshot:

    EmissionSnapshot::EmissionSnapshot() :
        EmittingEntity (0) ,
        PositionMetersX (0.0) ,
        PositionMetersY (0.0) ,
        PositionMetersZ (0.0) ,
        EmitterName (0) ,
        EmitterFunction (0) ,
        FrequencyLowHz (0.0f) ,
        FrequencyHighHz (0.0f) ,
        EffectiveRadiatedPowerDbm (0.0f) ,
        PulseRepetitionFreqHz (0.0f) ,
        PulseWidthMicrosec (0.0f) ,
        BeamAzimuthRad (0.0f) ,
        BeamFunction (0)  {

    }

    EmissionSnapshot::EmissionSnapshot (const ::ClearanceRTI::WireHeader& Header_,uint16_t EmittingEntity_,double PositionMetersX_,double PositionMetersY_,double PositionMetersZ_,uint16_t EmitterName_,uint8_t EmitterFunction_,float FrequencyLowHz_,float FrequencyHighHz_,float EffectiveRadiatedPowerDbm_,float PulseRepetitionFreqHz_,float PulseWidthMicrosec_,float BeamAzimuthRad_,uint8_t BeamFunction_,const ::omg::types::bounded_sequence< uint16_t, 100L >& PaintedEntityNumbers_) {
        Header = Header_;
        EmittingEntity = EmittingEntity_;
        PositionMetersX = PositionMetersX_;
        PositionMetersY = PositionMetersY_;
        PositionMetersZ = PositionMetersZ_;
        EmitterName = EmitterName_;
        EmitterFunction = EmitterFunction_;
        FrequencyLowHz = FrequencyLowHz_;
        FrequencyHighHz = FrequencyHighHz_;
        EffectiveRadiatedPowerDbm = EffectiveRadiatedPowerDbm_;
        PulseRepetitionFreqHz = PulseRepetitionFreqHz_;
        PulseWidthMicrosec = PulseWidthMicrosec_;
        BeamAzimuthRad = BeamAzimuthRad_;
        BeamFunction = BeamFunction_;
        PaintedEntityNumbers = PaintedEntityNumbers_;
    }

    bool operator == (const EmissionSnapshot& a, const EmissionSnapshot& b) {

        if (a.Header != b.Header) {
            return false;
        }
        if (a.EmittingEntity != b.EmittingEntity) {
            return false;
        }
        if (std::fabs(a.PositionMetersX - b.PositionMetersX) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.PositionMetersX - b.PositionMetersX) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.PositionMetersY - b.PositionMetersY) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.PositionMetersY - b.PositionMetersY) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.PositionMetersZ - b.PositionMetersZ) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.PositionMetersZ - b.PositionMetersZ) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (a.EmitterName != b.EmitterName) {
            return false;
        }
        if (a.EmitterFunction != b.EmitterFunction) {
            return false;
        }
        if (std::fabs(a.FrequencyLowHz - b.FrequencyLowHz) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.FrequencyLowHz - b.FrequencyLowHz) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.FrequencyHighHz - b.FrequencyHighHz) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.FrequencyHighHz - b.FrequencyHighHz) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.EffectiveRadiatedPowerDbm - b.EffectiveRadiatedPowerDbm) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.EffectiveRadiatedPowerDbm - b.EffectiveRadiatedPowerDbm) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.PulseRepetitionFreqHz - b.PulseRepetitionFreqHz) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.PulseRepetitionFreqHz - b.PulseRepetitionFreqHz) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.PulseWidthMicrosec - b.PulseWidthMicrosec) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.PulseWidthMicrosec - b.PulseWidthMicrosec) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.BeamAzimuthRad - b.BeamAzimuthRad) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.BeamAzimuthRad - b.BeamAzimuthRad) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (a.BeamFunction != b.BeamFunction) {
            return false;
        }
        if (a.PaintedEntityNumbers != b.PaintedEntityNumbers) {
            return false;
        }

        return true;
    }

    bool operator != (const EmissionSnapshot& a, const EmissionSnapshot& b) {
        return !operator ==(a, b);
    }

    void swap(EmissionSnapshot& a, EmissionSnapshot& b) noexcept
    {
        using std::swap;

        swap(a.Header, b.Header);
        swap(a.EmittingEntity, b.EmittingEntity);
        swap(a.PositionMetersX, b.PositionMetersX);
        swap(a.PositionMetersY, b.PositionMetersY);
        swap(a.PositionMetersZ, b.PositionMetersZ);
        swap(a.EmitterName, b.EmitterName);
        swap(a.EmitterFunction, b.EmitterFunction);
        swap(a.FrequencyLowHz, b.FrequencyLowHz);
        swap(a.FrequencyHighHz, b.FrequencyHighHz);
        swap(a.EffectiveRadiatedPowerDbm, b.EffectiveRadiatedPowerDbm);
        swap(a.PulseRepetitionFreqHz, b.PulseRepetitionFreqHz);
        swap(a.PulseWidthMicrosec, b.PulseWidthMicrosec);
        swap(a.BeamAzimuthRad, b.BeamAzimuthRad);
        swap(a.BeamFunction, b.BeamFunction);
        swap(a.PaintedEntityNumbers, b.PaintedEntityNumbers);

    }  
    std::ostream& operator << (std::ostream& o,const EmissionSnapshot& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "Header: " << sample.Header<<", ";
        o << "EmittingEntity: " << sample.EmittingEntity<<", ";
        o << "PositionMetersX: " << std::setprecision(15) << sample.PositionMetersX<<", ";
        o << "PositionMetersY: " << std::setprecision(15) << sample.PositionMetersY<<", ";
        o << "PositionMetersZ: " << std::setprecision(15) << sample.PositionMetersZ<<", ";
        o << "EmitterName: " << sample.EmitterName<<", ";
        o << "EmitterFunction: " << std::hex<<(int)  sample.EmitterFunction <<", ";
        o << "FrequencyLowHz: " << std::setprecision(9) << sample.FrequencyLowHz<<", ";
        o << "FrequencyHighHz: " << std::setprecision(9) << sample.FrequencyHighHz<<", ";
        o << "EffectiveRadiatedPowerDbm: " << std::setprecision(9) << sample.EffectiveRadiatedPowerDbm<<", ";
        o << "PulseRepetitionFreqHz: " << std::setprecision(9) << sample.PulseRepetitionFreqHz<<", ";
        o << "PulseWidthMicrosec: " << std::setprecision(9) << sample.PulseWidthMicrosec<<", ";
        o << "BeamAzimuthRad: " << std::setprecision(9) << sample.BeamAzimuthRad<<", ";
        o << "BeamFunction: " << std::hex<<(int)  sample.BeamFunction <<", ";
        o << "PaintedEntityNumbers: " << sample.PaintedEntityNumbers;
        o <<"]";
        return o;
    }

    // ---- TransmitterState:

    TransmitterState::TransmitterState() :
        OwnerEntity (0) ,
        RadioId (0) ,
        FrequencyHz (0ull) ,
        BandwidthHz (0.0f) ,
        PowerDbm (0.0f) ,
        TransmitState (0) ,
        AntennaXMeters (0.0) ,
        AntennaYMeters (0.0) ,
        AntennaZMeters (0.0)  {

    }

    TransmitterState::TransmitterState (const ::ClearanceRTI::WireHeader& Header_,uint16_t OwnerEntity_,uint16_t RadioId_,uint64_t FrequencyHz_,float BandwidthHz_,float PowerDbm_,uint8_t TransmitState_,double AntennaXMeters_,double AntennaYMeters_,double AntennaZMeters_) {
        Header = Header_;
        OwnerEntity = OwnerEntity_;
        RadioId = RadioId_;
        FrequencyHz = FrequencyHz_;
        BandwidthHz = BandwidthHz_;
        PowerDbm = PowerDbm_;
        TransmitState = TransmitState_;
        AntennaXMeters = AntennaXMeters_;
        AntennaYMeters = AntennaYMeters_;
        AntennaZMeters = AntennaZMeters_;
    }

    bool operator == (const TransmitterState& a, const TransmitterState& b) {

        if (a.Header != b.Header) {
            return false;
        }
        if (a.OwnerEntity != b.OwnerEntity) {
            return false;
        }
        if (a.RadioId != b.RadioId) {
            return false;
        }
        if (a.FrequencyHz != b.FrequencyHz) {
            return false;
        }
        if (std::fabs(a.BandwidthHz - b.BandwidthHz) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.BandwidthHz - b.BandwidthHz) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (std::fabs(a.PowerDbm - b.PowerDbm) > std::numeric_limits< float>::epsilon()
        && !(std::fabs(a.PowerDbm - b.PowerDbm) < (std::numeric_limits< float>::min)())) {
            return false;
        }
        if (a.TransmitState != b.TransmitState) {
            return false;
        }
        if (std::fabs(a.AntennaXMeters - b.AntennaXMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.AntennaXMeters - b.AntennaXMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.AntennaYMeters - b.AntennaYMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.AntennaYMeters - b.AntennaYMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }
        if (std::fabs(a.AntennaZMeters - b.AntennaZMeters) > std::numeric_limits< double>::epsilon()
        && !(std::fabs(a.AntennaZMeters - b.AntennaZMeters) < (std::numeric_limits< double>::min)())) {
            return false;
        }

        return true;
    }

    bool operator != (const TransmitterState& a, const TransmitterState& b) {
        return !operator ==(a, b);
    }

    void swap(TransmitterState& a, TransmitterState& b) noexcept
    {
        using std::swap;

        swap(a.Header, b.Header);
        swap(a.OwnerEntity, b.OwnerEntity);
        swap(a.RadioId, b.RadioId);
        swap(a.FrequencyHz, b.FrequencyHz);
        swap(a.BandwidthHz, b.BandwidthHz);
        swap(a.PowerDbm, b.PowerDbm);
        swap(a.TransmitState, b.TransmitState);
        swap(a.AntennaXMeters, b.AntennaXMeters);
        swap(a.AntennaYMeters, b.AntennaYMeters);
        swap(a.AntennaZMeters, b.AntennaZMeters);

    }  
    std::ostream& operator << (std::ostream& o,const TransmitterState& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "Header: " << sample.Header<<", ";
        o << "OwnerEntity: " << sample.OwnerEntity<<", ";
        o << "RadioId: " << sample.RadioId<<", ";
        o << "FrequencyHz: " << sample.FrequencyHz<<", ";
        o << "BandwidthHz: " << std::setprecision(9) << sample.BandwidthHz<<", ";
        o << "PowerDbm: " << std::setprecision(9) << sample.PowerDbm<<", ";
        o << "TransmitState: " << std::hex<<(int)  sample.TransmitState <<", ";
        o << "AntennaXMeters: " << std::setprecision(15) << sample.AntennaXMeters<<", ";
        o << "AntennaYMeters: " << std::setprecision(15) << sample.AntennaYMeters<<", ";
        o << "AntennaZMeters: " << std::setprecision(15) << sample.AntennaZMeters;
        o <<"]";
        return o;
    }

    // ---- SignalEvent:

    SignalEvent::SignalEvent() :
        OwnerEntity (0) ,
        RadioId (0)  {

    }

    SignalEvent::SignalEvent (const ::ClearanceRTI::WireHeader& Header_,uint16_t OwnerEntity_,uint16_t RadioId_,const ::omg::types::bounded_sequence< uint8_t, 100L >& Data_) {
        Header = Header_;
        OwnerEntity = OwnerEntity_;
        RadioId = RadioId_;
        Data = Data_;
    }

    bool operator == (const SignalEvent& a, const SignalEvent& b) {

        if (a.Header != b.Header) {
            return false;
        }
        if (a.OwnerEntity != b.OwnerEntity) {
            return false;
        }
        if (a.RadioId != b.RadioId) {
            return false;
        }
        if (a.Data != b.Data) {
            return false;
        }

        return true;
    }

    bool operator != (const SignalEvent& a, const SignalEvent& b) {
        return !operator ==(a, b);
    }

    void swap(SignalEvent& a, SignalEvent& b) noexcept
    {
        using std::swap;

        swap(a.Header, b.Header);
        swap(a.OwnerEntity, b.OwnerEntity);
        swap(a.RadioId, b.RadioId);
        swap(a.Data, b.Data);

    }  
    std::ostream& operator << (std::ostream& o,const SignalEvent& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "Header: " << sample.Header<<", ";
        o << "OwnerEntity: " << sample.OwnerEntity<<", ";
        o << "RadioId: " << sample.RadioId<<", ";
        o << "Data: " << sample.Data;
        o <<"]";
        return o;
    }

} // namespace ClearanceRTI  

#ifdef NDDS_STANDALONE_TYPE
namespace rti {
    namespace topic {
    }
}

#else
// --- Type traits: -------------------------------------------------

namespace rti { 
    namespace topic {

        template<>
        struct native_type_code< ::ClearanceRTI::WireHeader > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member WireHeader_g_tc_members[4]=
                {

                    {
                        (char *)"ExerciseId",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"SiteId",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"ApplicationId",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"SimTimeSeconds",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode WireHeader_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ClearanceRTI::WireHeader", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        4, /* Number of members */
                        WireHeader_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for WireHeader*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &WireHeader_g_tc;
                }

                WireHeader_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                WireHeader_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                WireHeader_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                WireHeader_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                WireHeader_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;

                /* Initialize the values for member annotations. */
                WireHeader_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                WireHeader_g_tc_members[0]._annotations._defaultValue._u.octet_value = 0;
                WireHeader_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                WireHeader_g_tc_members[0]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                WireHeader_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                WireHeader_g_tc_members[0]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                WireHeader_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                WireHeader_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                WireHeader_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                WireHeader_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                WireHeader_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                WireHeader_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                WireHeader_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                WireHeader_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
                WireHeader_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                WireHeader_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                WireHeader_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                WireHeader_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                WireHeader_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                WireHeader_g_tc_members[3]._annotations._defaultValue._u.double_value = 0.0;
                WireHeader_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                WireHeader_g_tc_members[3]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                WireHeader_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                WireHeader_g_tc_members[3]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

                WireHeader_g_tc._data._sampleAccessInfo = sample_access_info();
                WireHeader_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &WireHeader_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::ClearanceRTI::WireHeader *sample;

                static RTIXCdrMemberAccessInfo WireHeader_g_memberAccessInfos[4] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo WireHeader_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &WireHeader_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::ClearanceRTI::WireHeader);
                if (sample == NULL) {
                    return NULL;
                }

                WireHeader_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ExerciseId - (char *)sample);

                WireHeader_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->SiteId - (char *)sample);

                WireHeader_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ApplicationId - (char *)sample);

                WireHeader_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->SimTimeSeconds - (char *)sample);

                WireHeader_g_sampleAccessInfo.memberAccessInfos =
                WireHeader_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::ClearanceRTI::WireHeader);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        WireHeader_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        WireHeader_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                WireHeader_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                WireHeader_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::ClearanceRTI::WireHeader >;

                WireHeader_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &WireHeader_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin WireHeader_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &WireHeader_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::ClearanceRTI::WireHeader >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::ClearanceRTI::WireHeader >::get())));
        }

        template<>
        struct native_type_code< ::ClearanceRTI::AircraftState > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode AircraftState_g_tc_Marking_string;

                static DDS_TypeCode_Member AircraftState_g_tc_members[24]=
                {

                    {
                        (char *)"Header",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntityNumber",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"Marking",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"ForceId",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntityKind",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntityDomain",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntityCountry",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntityCategory",/* Member name */
                        {
                            7,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntitySubcategory",/* Member name */
                        {
                            8,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntitySpecific",/* Member name */
                        {
                            9,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EntityExtra",/* Member name */
                        {
                            10,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"XMeters",/* Member name */
                        {
                            11,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"YMeters",/* Member name */
                        {
                            12,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"ZMeters",/* Member name */
                        {
                            13,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VxMps",/* Member name */
                        {
                            14,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VyMps",/* Member name */
                        {
                            15,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VzMps",/* Member name */
                        {
                            16,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PsiRad",/* Member name */
                        {
                            17,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"ThetaRad",/* Member name */
                        {
                            18,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PhiRad",/* Member name */
                        {
                            19,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"TrueAffiliation",/* Member name */
                        {
                            20,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"SquawkCode",/* Member name */
                        {
                            21,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"ActiveEmergency",/* Member name */
                        {
                            22,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FlightPhase",/* Member name */
                        {
                            23,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode AircraftState_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ClearanceRTI::AircraftState", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        24, /* Number of members */
                        AircraftState_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for AircraftState*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &AircraftState_g_tc;
                }

                AircraftState_g_tc_Marking_string = initialize_string_typecode((255L));

                AircraftState_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                AircraftState_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::ClearanceRTI::WireHeader>::get().native();
                AircraftState_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                AircraftState_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&AircraftState_g_tc_Marking_string;
                AircraftState_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[4]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[5]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[6]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                AircraftState_g_tc_members[7]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[8]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[9]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[10]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[11]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                AircraftState_g_tc_members[12]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                AircraftState_g_tc_members[13]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                AircraftState_g_tc_members[14]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                AircraftState_g_tc_members[15]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                AircraftState_g_tc_members[16]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                AircraftState_g_tc_members[17]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                AircraftState_g_tc_members[18]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                AircraftState_g_tc_members[19]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                AircraftState_g_tc_members[20]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[21]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                AircraftState_g_tc_members[22]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                AircraftState_g_tc_members[23]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;

                /* Initialize the values for member annotations. */
                AircraftState_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                AircraftState_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                AircraftState_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                AircraftState_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                AircraftState_g_tc_members[2]._annotations._defaultValue._u.string_value = (DDS_Char *) "";
                AircraftState_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[3]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[3]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[3]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[4]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[4]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[4]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[5]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[5]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[5]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[6]._annotations._defaultValue._u.ushort_value = 0;
                AircraftState_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[6]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                AircraftState_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[6]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                AircraftState_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[7]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[7]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[7]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[8]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[8]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[8]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[9]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[9]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[9]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[10]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[10]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[10]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[11]._annotations._defaultValue._u.double_value = 0.0;
                AircraftState_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[11]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                AircraftState_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[11]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                AircraftState_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[12]._annotations._defaultValue._u.double_value = 0.0;
                AircraftState_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[12]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                AircraftState_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[12]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                AircraftState_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[13]._annotations._defaultValue._u.double_value = 0.0;
                AircraftState_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[13]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                AircraftState_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                AircraftState_g_tc_members[13]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                AircraftState_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[14]._annotations._defaultValue._u.float_value = 0.0f;
                AircraftState_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[14]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                AircraftState_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[14]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                AircraftState_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[15]._annotations._defaultValue._u.float_value = 0.0f;
                AircraftState_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[15]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                AircraftState_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[15]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                AircraftState_g_tc_members[16]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[16]._annotations._defaultValue._u.float_value = 0.0f;
                AircraftState_g_tc_members[16]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[16]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                AircraftState_g_tc_members[16]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[16]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                AircraftState_g_tc_members[17]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[17]._annotations._defaultValue._u.float_value = 0.0f;
                AircraftState_g_tc_members[17]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[17]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                AircraftState_g_tc_members[17]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[17]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                AircraftState_g_tc_members[18]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[18]._annotations._defaultValue._u.float_value = 0.0f;
                AircraftState_g_tc_members[18]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[18]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                AircraftState_g_tc_members[18]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[18]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                AircraftState_g_tc_members[19]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[19]._annotations._defaultValue._u.float_value = 0.0f;
                AircraftState_g_tc_members[19]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[19]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                AircraftState_g_tc_members[19]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                AircraftState_g_tc_members[19]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                AircraftState_g_tc_members[20]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[20]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[20]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[20]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[20]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[20]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[21]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[21]._annotations._defaultValue._u.ushort_value = 0;
                AircraftState_g_tc_members[21]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[21]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                AircraftState_g_tc_members[21]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                AircraftState_g_tc_members[21]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                AircraftState_g_tc_members[22]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[22]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[22]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[22]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[22]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[22]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                AircraftState_g_tc_members[23]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[23]._annotations._defaultValue._u.octet_value = 0;
                AircraftState_g_tc_members[23]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[23]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                AircraftState_g_tc_members[23]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                AircraftState_g_tc_members[23]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

                AircraftState_g_tc._data._sampleAccessInfo = sample_access_info();
                AircraftState_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &AircraftState_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::ClearanceRTI::AircraftState *sample;

                static RTIXCdrMemberAccessInfo AircraftState_g_memberAccessInfos[24] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo AircraftState_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &AircraftState_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::ClearanceRTI::AircraftState);
                if (sample == NULL) {
                    return NULL;
                }

                AircraftState_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

                AircraftState_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntityNumber - (char *)sample);

                AircraftState_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Marking - (char *)sample);

                AircraftState_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ForceId - (char *)sample);

                AircraftState_g_memberAccessInfos[4].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntityKind - (char *)sample);

                AircraftState_g_memberAccessInfos[5].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntityDomain - (char *)sample);

                AircraftState_g_memberAccessInfos[6].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntityCountry - (char *)sample);

                AircraftState_g_memberAccessInfos[7].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntityCategory - (char *)sample);

                AircraftState_g_memberAccessInfos[8].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntitySubcategory - (char *)sample);

                AircraftState_g_memberAccessInfos[9].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntitySpecific - (char *)sample);

                AircraftState_g_memberAccessInfos[10].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EntityExtra - (char *)sample);

                AircraftState_g_memberAccessInfos[11].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->XMeters - (char *)sample);

                AircraftState_g_memberAccessInfos[12].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->YMeters - (char *)sample);

                AircraftState_g_memberAccessInfos[13].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ZMeters - (char *)sample);

                AircraftState_g_memberAccessInfos[14].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VxMps - (char *)sample);

                AircraftState_g_memberAccessInfos[15].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VyMps - (char *)sample);

                AircraftState_g_memberAccessInfos[16].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VzMps - (char *)sample);

                AircraftState_g_memberAccessInfos[17].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PsiRad - (char *)sample);

                AircraftState_g_memberAccessInfos[18].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ThetaRad - (char *)sample);

                AircraftState_g_memberAccessInfos[19].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PhiRad - (char *)sample);

                AircraftState_g_memberAccessInfos[20].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->TrueAffiliation - (char *)sample);

                AircraftState_g_memberAccessInfos[21].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->SquawkCode - (char *)sample);

                AircraftState_g_memberAccessInfos[22].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ActiveEmergency - (char *)sample);

                AircraftState_g_memberAccessInfos[23].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FlightPhase - (char *)sample);

                AircraftState_g_sampleAccessInfo.memberAccessInfos =
                AircraftState_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::ClearanceRTI::AircraftState);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        AircraftState_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        AircraftState_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                AircraftState_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                AircraftState_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::ClearanceRTI::AircraftState >;

                AircraftState_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &AircraftState_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin AircraftState_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &AircraftState_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::ClearanceRTI::AircraftState >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::ClearanceRTI::AircraftState >::get())));
        }

        template<>
        struct native_type_code< ::ClearanceRTI::FireEvent > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member FireEvent_g_tc_members[17]=
                {

                    {
                        (char *)"Header",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FiringEntity",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"TargetEntity",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"MunitionEntity",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EventNumber",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"XMeters",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"YMeters",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"ZMeters",/* Member name */
                        {
                            7,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VxMps",/* Member name */
                        {
                            8,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VyMps",/* Member name */
                        {
                            9,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VzMps",/* Member name */
                        {
                            10,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"MunitionKind",/* Member name */
                        {
                            11,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"WarheadKind",/* Member name */
                        {
                            12,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FuseKind",/* Member name */
                        {
                            13,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"Quantity",/* Member name */
                        {
                            14,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"Rate",/* Member name */
                        {
                            15,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"RangeMeters",/* Member name */
                        {
                            16,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode FireEvent_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ClearanceRTI::FireEvent", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        17, /* Number of members */
                        FireEvent_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for FireEvent*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &FireEvent_g_tc;
                }

                FireEvent_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                FireEvent_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::ClearanceRTI::WireHeader>::get().native();
                FireEvent_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[4]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[5]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                FireEvent_g_tc_members[6]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                FireEvent_g_tc_members[7]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                FireEvent_g_tc_members[8]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                FireEvent_g_tc_members[9]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                FireEvent_g_tc_members[10]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                FireEvent_g_tc_members[11]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                FireEvent_g_tc_members[12]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[13]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[14]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[15]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                FireEvent_g_tc_members[16]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;

                /* Initialize the values for member annotations. */
                FireEvent_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[3]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[3]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[3]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[4]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[4]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[4]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[5]._annotations._defaultValue._u.double_value = 0.0;
                FireEvent_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[5]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                FireEvent_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[5]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                FireEvent_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[6]._annotations._defaultValue._u.double_value = 0.0;
                FireEvent_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[6]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                FireEvent_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[6]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                FireEvent_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[7]._annotations._defaultValue._u.double_value = 0.0;
                FireEvent_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[7]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                FireEvent_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                FireEvent_g_tc_members[7]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                FireEvent_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
                FireEvent_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                FireEvent_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                FireEvent_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[9]._annotations._defaultValue._u.float_value = 0.0f;
                FireEvent_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[9]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                FireEvent_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[9]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                FireEvent_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[10]._annotations._defaultValue._u.float_value = 0.0f;
                FireEvent_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[10]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                FireEvent_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[10]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                FireEvent_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                FireEvent_g_tc_members[11]._annotations._defaultValue._u.octet_value = 0;
                FireEvent_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                FireEvent_g_tc_members[11]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                FireEvent_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                FireEvent_g_tc_members[11]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                FireEvent_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[12]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[12]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[12]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[13]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[13]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[13]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[14]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[14]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[14]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[15]._annotations._defaultValue._u.ushort_value = 0;
                FireEvent_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[15]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                FireEvent_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                FireEvent_g_tc_members[15]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                FireEvent_g_tc_members[16]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[16]._annotations._defaultValue._u.float_value = 0.0f;
                FireEvent_g_tc_members[16]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[16]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                FireEvent_g_tc_members[16]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                FireEvent_g_tc_members[16]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

                FireEvent_g_tc._data._sampleAccessInfo = sample_access_info();
                FireEvent_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &FireEvent_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::ClearanceRTI::FireEvent *sample;

                static RTIXCdrMemberAccessInfo FireEvent_g_memberAccessInfos[17] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo FireEvent_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &FireEvent_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::ClearanceRTI::FireEvent);
                if (sample == NULL) {
                    return NULL;
                }

                FireEvent_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

                FireEvent_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FiringEntity - (char *)sample);

                FireEvent_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->TargetEntity - (char *)sample);

                FireEvent_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->MunitionEntity - (char *)sample);

                FireEvent_g_memberAccessInfos[4].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EventNumber - (char *)sample);

                FireEvent_g_memberAccessInfos[5].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->XMeters - (char *)sample);

                FireEvent_g_memberAccessInfos[6].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->YMeters - (char *)sample);

                FireEvent_g_memberAccessInfos[7].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ZMeters - (char *)sample);

                FireEvent_g_memberAccessInfos[8].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VxMps - (char *)sample);

                FireEvent_g_memberAccessInfos[9].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VyMps - (char *)sample);

                FireEvent_g_memberAccessInfos[10].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VzMps - (char *)sample);

                FireEvent_g_memberAccessInfos[11].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->MunitionKind - (char *)sample);

                FireEvent_g_memberAccessInfos[12].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->WarheadKind - (char *)sample);

                FireEvent_g_memberAccessInfos[13].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FuseKind - (char *)sample);

                FireEvent_g_memberAccessInfos[14].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Quantity - (char *)sample);

                FireEvent_g_memberAccessInfos[15].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Rate - (char *)sample);

                FireEvent_g_memberAccessInfos[16].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->RangeMeters - (char *)sample);

                FireEvent_g_sampleAccessInfo.memberAccessInfos =
                FireEvent_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::ClearanceRTI::FireEvent);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        FireEvent_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        FireEvent_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                FireEvent_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                FireEvent_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::ClearanceRTI::FireEvent >;

                FireEvent_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &FireEvent_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin FireEvent_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &FireEvent_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::ClearanceRTI::FireEvent >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::ClearanceRTI::FireEvent >::get())));
        }

        template<>
        struct native_type_code< ::ClearanceRTI::DetonationEvent > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member DetonationEvent_g_tc_members[17]=
                {

                    {
                        (char *)"Header",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FiringEntity",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"TargetEntity",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"MunitionEntity",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EventNumber",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"XMeters",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"YMeters",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"ZMeters",/* Member name */
                        {
                            7,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VxMps",/* Member name */
                        {
                            8,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VyMps",/* Member name */
                        {
                            9,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"VzMps",/* Member name */
                        {
                            10,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"MunitionKind",/* Member name */
                        {
                            11,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"WarheadKind",/* Member name */
                        {
                            12,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FuseKind",/* Member name */
                        {
                            13,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"Quantity",/* Member name */
                        {
                            14,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"Rate",/* Member name */
                        {
                            15,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"DetonationResult",/* Member name */
                        {
                            16,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode DetonationEvent_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ClearanceRTI::DetonationEvent", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        17, /* Number of members */
                        DetonationEvent_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for DetonationEvent*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &DetonationEvent_g_tc;
                }

                DetonationEvent_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                DetonationEvent_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::ClearanceRTI::WireHeader>::get().native();
                DetonationEvent_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[4]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[5]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                DetonationEvent_g_tc_members[6]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                DetonationEvent_g_tc_members[7]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                DetonationEvent_g_tc_members[8]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                DetonationEvent_g_tc_members[9]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                DetonationEvent_g_tc_members[10]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                DetonationEvent_g_tc_members[11]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                DetonationEvent_g_tc_members[12]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[13]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[14]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[15]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                DetonationEvent_g_tc_members[16]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;

                /* Initialize the values for member annotations. */
                DetonationEvent_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[3]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[3]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[3]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[4]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[4]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[4]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[5]._annotations._defaultValue._u.double_value = 0.0;
                DetonationEvent_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[5]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                DetonationEvent_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[5]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                DetonationEvent_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[6]._annotations._defaultValue._u.double_value = 0.0;
                DetonationEvent_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[6]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                DetonationEvent_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[6]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                DetonationEvent_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[7]._annotations._defaultValue._u.double_value = 0.0;
                DetonationEvent_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[7]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                DetonationEvent_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                DetonationEvent_g_tc_members[7]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                DetonationEvent_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
                DetonationEvent_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                DetonationEvent_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                DetonationEvent_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[9]._annotations._defaultValue._u.float_value = 0.0f;
                DetonationEvent_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[9]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                DetonationEvent_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[9]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                DetonationEvent_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[10]._annotations._defaultValue._u.float_value = 0.0f;
                DetonationEvent_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[10]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                DetonationEvent_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                DetonationEvent_g_tc_members[10]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                DetonationEvent_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                DetonationEvent_g_tc_members[11]._annotations._defaultValue._u.octet_value = 0;
                DetonationEvent_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                DetonationEvent_g_tc_members[11]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                DetonationEvent_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                DetonationEvent_g_tc_members[11]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                DetonationEvent_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[12]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[12]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[12]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[13]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[13]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[13]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[14]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[14]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[14]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[15]._annotations._defaultValue._u.ushort_value = 0;
                DetonationEvent_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[15]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                DetonationEvent_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                DetonationEvent_g_tc_members[15]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                DetonationEvent_g_tc_members[16]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                DetonationEvent_g_tc_members[16]._annotations._defaultValue._u.octet_value = 0;
                DetonationEvent_g_tc_members[16]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                DetonationEvent_g_tc_members[16]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                DetonationEvent_g_tc_members[16]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                DetonationEvent_g_tc_members[16]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

                DetonationEvent_g_tc._data._sampleAccessInfo = sample_access_info();
                DetonationEvent_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &DetonationEvent_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::ClearanceRTI::DetonationEvent *sample;

                static RTIXCdrMemberAccessInfo DetonationEvent_g_memberAccessInfos[17] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo DetonationEvent_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &DetonationEvent_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::ClearanceRTI::DetonationEvent);
                if (sample == NULL) {
                    return NULL;
                }

                DetonationEvent_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

                DetonationEvent_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FiringEntity - (char *)sample);

                DetonationEvent_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->TargetEntity - (char *)sample);

                DetonationEvent_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->MunitionEntity - (char *)sample);

                DetonationEvent_g_memberAccessInfos[4].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EventNumber - (char *)sample);

                DetonationEvent_g_memberAccessInfos[5].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->XMeters - (char *)sample);

                DetonationEvent_g_memberAccessInfos[6].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->YMeters - (char *)sample);

                DetonationEvent_g_memberAccessInfos[7].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->ZMeters - (char *)sample);

                DetonationEvent_g_memberAccessInfos[8].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VxMps - (char *)sample);

                DetonationEvent_g_memberAccessInfos[9].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VyMps - (char *)sample);

                DetonationEvent_g_memberAccessInfos[10].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->VzMps - (char *)sample);

                DetonationEvent_g_memberAccessInfos[11].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->MunitionKind - (char *)sample);

                DetonationEvent_g_memberAccessInfos[12].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->WarheadKind - (char *)sample);

                DetonationEvent_g_memberAccessInfos[13].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FuseKind - (char *)sample);

                DetonationEvent_g_memberAccessInfos[14].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Quantity - (char *)sample);

                DetonationEvent_g_memberAccessInfos[15].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Rate - (char *)sample);

                DetonationEvent_g_memberAccessInfos[16].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->DetonationResult - (char *)sample);

                DetonationEvent_g_sampleAccessInfo.memberAccessInfos =
                DetonationEvent_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::ClearanceRTI::DetonationEvent);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        DetonationEvent_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        DetonationEvent_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                DetonationEvent_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                DetonationEvent_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::ClearanceRTI::DetonationEvent >;

                DetonationEvent_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &DetonationEvent_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin DetonationEvent_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &DetonationEvent_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::ClearanceRTI::DetonationEvent >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::ClearanceRTI::DetonationEvent >::get())));
        }

        template<>
        struct native_type_code< ::ClearanceRTI::EmissionSnapshot > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode EmissionSnapshot_g_tc_PaintedEntityNumbers_sequence;

                static DDS_TypeCode_Member EmissionSnapshot_g_tc_members[15]=
                {

                    {
                        (char *)"Header",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EmittingEntity",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PositionMetersX",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PositionMetersY",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PositionMetersZ",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EmitterName",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EmitterFunction",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FrequencyLowHz",/* Member name */
                        {
                            7,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FrequencyHighHz",/* Member name */
                        {
                            8,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"EffectiveRadiatedPowerDbm",/* Member name */
                        {
                            9,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PulseRepetitionFreqHz",/* Member name */
                        {
                            10,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PulseWidthMicrosec",/* Member name */
                        {
                            11,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"BeamAzimuthRad",/* Member name */
                        {
                            12,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"BeamFunction",/* Member name */
                        {
                            13,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PaintedEntityNumbers",/* Member name */
                        {
                            14,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode EmissionSnapshot_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ClearanceRTI::EmissionSnapshot", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        15, /* Number of members */
                        EmissionSnapshot_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for EmissionSnapshot*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &EmissionSnapshot_g_tc;
                }

                EmissionSnapshot_g_tc_PaintedEntityNumbers_sequence = initialize_sequence_typecode< ::omg::types::bounded_sequence< uint16_t, 100L > >((100L));

                EmissionSnapshot_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                EmissionSnapshot_g_tc_PaintedEntityNumbers_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ushort;
                EmissionSnapshot_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::ClearanceRTI::WireHeader>::get().native();
                EmissionSnapshot_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                EmissionSnapshot_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                EmissionSnapshot_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                EmissionSnapshot_g_tc_members[4]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                EmissionSnapshot_g_tc_members[5]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                EmissionSnapshot_g_tc_members[6]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                EmissionSnapshot_g_tc_members[7]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                EmissionSnapshot_g_tc_members[8]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                EmissionSnapshot_g_tc_members[9]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                EmissionSnapshot_g_tc_members[10]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                EmissionSnapshot_g_tc_members[11]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                EmissionSnapshot_g_tc_members[12]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                EmissionSnapshot_g_tc_members[13]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                EmissionSnapshot_g_tc_members[14]._representation._typeCode =  (RTICdrTypeCode *)& EmissionSnapshot_g_tc_PaintedEntityNumbers_sequence;

                /* Initialize the values for member annotations. */
                EmissionSnapshot_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                EmissionSnapshot_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                EmissionSnapshot_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                EmissionSnapshot_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                EmissionSnapshot_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                EmissionSnapshot_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                EmissionSnapshot_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[2]._annotations._defaultValue._u.double_value = 0.0;
                EmissionSnapshot_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[2]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                EmissionSnapshot_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[2]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                EmissionSnapshot_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[3]._annotations._defaultValue._u.double_value = 0.0;
                EmissionSnapshot_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[3]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                EmissionSnapshot_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[3]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                EmissionSnapshot_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[4]._annotations._defaultValue._u.double_value = 0.0;
                EmissionSnapshot_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[4]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                EmissionSnapshot_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                EmissionSnapshot_g_tc_members[4]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                EmissionSnapshot_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                EmissionSnapshot_g_tc_members[5]._annotations._defaultValue._u.ushort_value = 0;
                EmissionSnapshot_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                EmissionSnapshot_g_tc_members[5]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                EmissionSnapshot_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                EmissionSnapshot_g_tc_members[5]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                EmissionSnapshot_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                EmissionSnapshot_g_tc_members[6]._annotations._defaultValue._u.octet_value = 0;
                EmissionSnapshot_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                EmissionSnapshot_g_tc_members[6]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                EmissionSnapshot_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                EmissionSnapshot_g_tc_members[6]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                EmissionSnapshot_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[7]._annotations._defaultValue._u.float_value = 0.0f;
                EmissionSnapshot_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[7]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                EmissionSnapshot_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[7]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                EmissionSnapshot_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
                EmissionSnapshot_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                EmissionSnapshot_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                EmissionSnapshot_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[9]._annotations._defaultValue._u.float_value = 0.0f;
                EmissionSnapshot_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[9]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                EmissionSnapshot_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[9]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                EmissionSnapshot_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[10]._annotations._defaultValue._u.float_value = 0.0f;
                EmissionSnapshot_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[10]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                EmissionSnapshot_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[10]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                EmissionSnapshot_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[11]._annotations._defaultValue._u.float_value = 0.0f;
                EmissionSnapshot_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[11]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                EmissionSnapshot_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[11]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                EmissionSnapshot_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[12]._annotations._defaultValue._u.float_value = 0.0f;
                EmissionSnapshot_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[12]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                EmissionSnapshot_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                EmissionSnapshot_g_tc_members[12]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                EmissionSnapshot_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                EmissionSnapshot_g_tc_members[13]._annotations._defaultValue._u.octet_value = 0;
                EmissionSnapshot_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                EmissionSnapshot_g_tc_members[13]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                EmissionSnapshot_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                EmissionSnapshot_g_tc_members[13]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

                EmissionSnapshot_g_tc._data._sampleAccessInfo = sample_access_info();
                EmissionSnapshot_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &EmissionSnapshot_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::ClearanceRTI::EmissionSnapshot *sample;

                static RTIXCdrMemberAccessInfo EmissionSnapshot_g_memberAccessInfos[15] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo EmissionSnapshot_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &EmissionSnapshot_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::ClearanceRTI::EmissionSnapshot);
                if (sample == NULL) {
                    return NULL;
                }

                EmissionSnapshot_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EmittingEntity - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PositionMetersX - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PositionMetersY - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[4].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PositionMetersZ - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[5].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EmitterName - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[6].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EmitterFunction - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[7].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FrequencyLowHz - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[8].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FrequencyHighHz - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[9].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->EffectiveRadiatedPowerDbm - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[10].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PulseRepetitionFreqHz - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[11].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PulseWidthMicrosec - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[12].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->BeamAzimuthRad - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[13].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->BeamFunction - (char *)sample);

                EmissionSnapshot_g_memberAccessInfos[14].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PaintedEntityNumbers - (char *)sample);

                EmissionSnapshot_g_sampleAccessInfo.memberAccessInfos =
                EmissionSnapshot_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::ClearanceRTI::EmissionSnapshot);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        EmissionSnapshot_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        EmissionSnapshot_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                EmissionSnapshot_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                EmissionSnapshot_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::ClearanceRTI::EmissionSnapshot >;

                EmissionSnapshot_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &EmissionSnapshot_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin EmissionSnapshot_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &EmissionSnapshot_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::ClearanceRTI::EmissionSnapshot >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::ClearanceRTI::EmissionSnapshot >::get())));
        }

        template<>
        struct native_type_code< ::ClearanceRTI::TransmitterState > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member TransmitterState_g_tc_members[10]=
                {

                    {
                        (char *)"Header",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"OwnerEntity",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"RadioId",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"FrequencyHz",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"BandwidthHz",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"PowerDbm",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"TransmitState",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"AntennaXMeters",/* Member name */
                        {
                            7,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"AntennaYMeters",/* Member name */
                        {
                            8,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"AntennaZMeters",/* Member name */
                        {
                            9,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode TransmitterState_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ClearanceRTI::TransmitterState", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        10, /* Number of members */
                        TransmitterState_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for TransmitterState*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &TransmitterState_g_tc;
                }

                TransmitterState_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                TransmitterState_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::ClearanceRTI::WireHeader>::get().native();
                TransmitterState_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                TransmitterState_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                TransmitterState_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulonglong;
                TransmitterState_g_tc_members[4]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                TransmitterState_g_tc_members[5]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float;
                TransmitterState_g_tc_members[6]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet;
                TransmitterState_g_tc_members[7]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                TransmitterState_g_tc_members[8]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;
                TransmitterState_g_tc_members[9]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_double;

                /* Initialize the values for member annotations. */
                TransmitterState_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                TransmitterState_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                TransmitterState_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                TransmitterState_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                TransmitterState_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                TransmitterState_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                TransmitterState_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                TransmitterState_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
                TransmitterState_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                TransmitterState_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                TransmitterState_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                TransmitterState_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                TransmitterState_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
                TransmitterState_g_tc_members[3]._annotations._defaultValue._u.ulong_long_value = 0ull;
                TransmitterState_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
                TransmitterState_g_tc_members[3]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
                TransmitterState_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
                TransmitterState_g_tc_members[3]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;
                TransmitterState_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                TransmitterState_g_tc_members[4]._annotations._defaultValue._u.float_value = 0.0f;
                TransmitterState_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                TransmitterState_g_tc_members[4]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                TransmitterState_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                TransmitterState_g_tc_members[4]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                TransmitterState_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
                TransmitterState_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
                TransmitterState_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
                TransmitterState_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
                TransmitterState_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
                TransmitterState_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
                TransmitterState_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
                TransmitterState_g_tc_members[6]._annotations._defaultValue._u.octet_value = 0;
                TransmitterState_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
                TransmitterState_g_tc_members[6]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
                TransmitterState_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
                TransmitterState_g_tc_members[6]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;
                TransmitterState_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[7]._annotations._defaultValue._u.double_value = 0.0;
                TransmitterState_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[7]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                TransmitterState_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[7]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                TransmitterState_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[8]._annotations._defaultValue._u.double_value = 0.0;
                TransmitterState_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[8]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                TransmitterState_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[8]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;
                TransmitterState_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[9]._annotations._defaultValue._u.double_value = 0.0;
                TransmitterState_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[9]._annotations._minValue._u.double_value = RTIXCdrDouble_MIN;
                TransmitterState_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_DOUBLE;
                TransmitterState_g_tc_members[9]._annotations._maxValue._u.double_value = RTIXCdrDouble_MAX;

                TransmitterState_g_tc._data._sampleAccessInfo = sample_access_info();
                TransmitterState_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &TransmitterState_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::ClearanceRTI::TransmitterState *sample;

                static RTIXCdrMemberAccessInfo TransmitterState_g_memberAccessInfos[10] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo TransmitterState_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &TransmitterState_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::ClearanceRTI::TransmitterState);
                if (sample == NULL) {
                    return NULL;
                }

                TransmitterState_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

                TransmitterState_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->OwnerEntity - (char *)sample);

                TransmitterState_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->RadioId - (char *)sample);

                TransmitterState_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->FrequencyHz - (char *)sample);

                TransmitterState_g_memberAccessInfos[4].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->BandwidthHz - (char *)sample);

                TransmitterState_g_memberAccessInfos[5].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->PowerDbm - (char *)sample);

                TransmitterState_g_memberAccessInfos[6].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->TransmitState - (char *)sample);

                TransmitterState_g_memberAccessInfos[7].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->AntennaXMeters - (char *)sample);

                TransmitterState_g_memberAccessInfos[8].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->AntennaYMeters - (char *)sample);

                TransmitterState_g_memberAccessInfos[9].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->AntennaZMeters - (char *)sample);

                TransmitterState_g_sampleAccessInfo.memberAccessInfos =
                TransmitterState_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::ClearanceRTI::TransmitterState);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        TransmitterState_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        TransmitterState_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                TransmitterState_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                TransmitterState_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::ClearanceRTI::TransmitterState >;

                TransmitterState_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &TransmitterState_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin TransmitterState_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &TransmitterState_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::ClearanceRTI::TransmitterState >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::ClearanceRTI::TransmitterState >::get())));
        }

        template<>
        struct native_type_code< ::ClearanceRTI::SignalEvent > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode SignalEvent_g_tc_Data_sequence;

                static DDS_TypeCode_Member SignalEvent_g_tc_members[4]=
                {

                    {
                        (char *)"Header",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"OwnerEntity",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_KEY_MEMBER , /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"RadioId",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"Data",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode SignalEvent_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ClearanceRTI::SignalEvent", /* Name */
                        NULL, /* Ignored */ 
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        4, /* Number of members */
                        SignalEvent_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for SignalEvent*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &SignalEvent_g_tc;
                }

                SignalEvent_g_tc_Data_sequence = initialize_sequence_typecode< ::omg::types::bounded_sequence< uint8_t, 100L > >((100L));

                SignalEvent_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                SignalEvent_g_tc_Data_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;
                SignalEvent_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::ClearanceRTI::WireHeader>::get().native();
                SignalEvent_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                SignalEvent_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ushort;
                SignalEvent_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)& SignalEvent_g_tc_Data_sequence;

                /* Initialize the values for member annotations. */
                SignalEvent_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                SignalEvent_g_tc_members[1]._annotations._defaultValue._u.ushort_value = 0;
                SignalEvent_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                SignalEvent_g_tc_members[1]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                SignalEvent_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                SignalEvent_g_tc_members[1]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;
                SignalEvent_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_USHORT;
                SignalEvent_g_tc_members[2]._annotations._defaultValue._u.ushort_value = 0;
                SignalEvent_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_USHORT;
                SignalEvent_g_tc_members[2]._annotations._minValue._u.ushort_value = RTIXCdrUnsignedShort_MIN;
                SignalEvent_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_USHORT;
                SignalEvent_g_tc_members[2]._annotations._maxValue._u.ushort_value = RTIXCdrUnsignedShort_MAX;

                SignalEvent_g_tc._data._sampleAccessInfo = sample_access_info();
                SignalEvent_g_tc._data._typePlugin = type_plugin_info();

                is_initialized.store(true, std::memory_order_release);

                return &SignalEvent_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::ClearanceRTI::SignalEvent *sample;

                static RTIXCdrMemberAccessInfo SignalEvent_g_memberAccessInfos[4] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo SignalEvent_g_sampleAccessInfo =
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &SignalEvent_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample,
                    ::ClearanceRTI::SignalEvent);
                if (sample == NULL) {
                    return NULL;
                }

                SignalEvent_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Header - (char *)sample);

                SignalEvent_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->OwnerEntity - (char *)sample);

                SignalEvent_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->RadioId - (char *)sample);

                SignalEvent_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
                (RTIXCdrUnsignedLong) ((char *)&sample->Data - (char *)sample);

                SignalEvent_g_sampleAccessInfo.memberAccessInfos =
                SignalEvent_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::ClearanceRTI::SignalEvent);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        SignalEvent_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        SignalEvent_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                SignalEvent_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                SignalEvent_g_sampleAccessInfo.getMemberValuePointerFcn =
                interpreter::get_aggregation_value_pointer< ::ClearanceRTI::SignalEvent >;

                SignalEvent_g_sampleAccessInfo.languageBinding =
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &SignalEvent_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin SignalEvent_g_typePlugin =
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &SignalEvent_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::ClearanceRTI::SignalEvent >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::ClearanceRTI::SignalEvent >::get())));
        }
    }
}

namespace dds { 
    namespace topic {
        void topic_type_support< ::ClearanceRTI::WireHeader >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::ClearanceRTI::WireHeaderPlugin_new,
                ::ClearanceRTI::WireHeaderPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::ClearanceRTI::WireHeader >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::ClearanceRTI::WireHeader& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = WireHeaderPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = WireHeaderPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::ClearanceRTI::WireHeader >::from_cdr_buffer(::ClearanceRTI::WireHeader& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = WireHeaderPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::ClearanceRTI::WireHeader from cdr buffer");
        }

        void topic_type_support< ::ClearanceRTI::WireHeader >::reset_sample(::ClearanceRTI::WireHeader& sample) 
        {
            sample.ExerciseId = 0;
            sample.SiteId = 0;
            sample.ApplicationId = 0;
            sample.SimTimeSeconds = 0.0;
        }

        void topic_type_support< ::ClearanceRTI::WireHeader >::allocate_sample(::ClearanceRTI::WireHeader& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample);
        }
        void topic_type_support< ::ClearanceRTI::AircraftState >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::ClearanceRTI::AircraftStatePlugin_new,
                ::ClearanceRTI::AircraftStatePlugin_delete);
        }

        std::vector<char>& topic_type_support< ::ClearanceRTI::AircraftState >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::ClearanceRTI::AircraftState& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = AircraftStatePlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = AircraftStatePlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::ClearanceRTI::AircraftState >::from_cdr_buffer(::ClearanceRTI::AircraftState& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = AircraftStatePlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::ClearanceRTI::AircraftState from cdr buffer");
        }

        void topic_type_support< ::ClearanceRTI::AircraftState >::reset_sample(::ClearanceRTI::AircraftState& sample) 
        {
            ::rti::topic::reset_sample(sample.Header);
            sample.EntityNumber = 0;
            sample.Marking = "";
            sample.ForceId = 0;
            sample.EntityKind = 0;
            sample.EntityDomain = 0;
            sample.EntityCountry = 0;
            sample.EntityCategory = 0;
            sample.EntitySubcategory = 0;
            sample.EntitySpecific = 0;
            sample.EntityExtra = 0;
            sample.XMeters = 0.0;
            sample.YMeters = 0.0;
            sample.ZMeters = 0.0;
            sample.VxMps = 0.0f;
            sample.VyMps = 0.0f;
            sample.VzMps = 0.0f;
            sample.PsiRad = 0.0f;
            sample.ThetaRad = 0.0f;
            sample.PhiRad = 0.0f;
            sample.TrueAffiliation = 0;
            sample.SquawkCode = 0;
            sample.ActiveEmergency = 0;
            sample.FlightPhase = 0;
        }

        void topic_type_support< ::ClearanceRTI::AircraftState >::allocate_sample(::ClearanceRTI::AircraftState& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.Header,  -1, -1);
            ::rti::topic::allocate_sample(sample.Marking,  -1, 255L);
        }
        void topic_type_support< ::ClearanceRTI::FireEvent >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::ClearanceRTI::FireEventPlugin_new,
                ::ClearanceRTI::FireEventPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::ClearanceRTI::FireEvent >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::ClearanceRTI::FireEvent& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = FireEventPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = FireEventPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::ClearanceRTI::FireEvent >::from_cdr_buffer(::ClearanceRTI::FireEvent& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = FireEventPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::ClearanceRTI::FireEvent from cdr buffer");
        }

        void topic_type_support< ::ClearanceRTI::FireEvent >::reset_sample(::ClearanceRTI::FireEvent& sample) 
        {
            ::rti::topic::reset_sample(sample.Header);
            sample.FiringEntity = 0;
            sample.TargetEntity = 0;
            sample.MunitionEntity = 0;
            sample.EventNumber = 0;
            sample.XMeters = 0.0;
            sample.YMeters = 0.0;
            sample.ZMeters = 0.0;
            sample.VxMps = 0.0f;
            sample.VyMps = 0.0f;
            sample.VzMps = 0.0f;
            sample.MunitionKind = 0;
            sample.WarheadKind = 0;
            sample.FuseKind = 0;
            sample.Quantity = 0;
            sample.Rate = 0;
            sample.RangeMeters = 0.0f;
        }

        void topic_type_support< ::ClearanceRTI::FireEvent >::allocate_sample(::ClearanceRTI::FireEvent& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.Header,  -1, -1);
        }
        void topic_type_support< ::ClearanceRTI::DetonationEvent >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::ClearanceRTI::DetonationEventPlugin_new,
                ::ClearanceRTI::DetonationEventPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::ClearanceRTI::DetonationEvent >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::ClearanceRTI::DetonationEvent& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = DetonationEventPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = DetonationEventPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::ClearanceRTI::DetonationEvent >::from_cdr_buffer(::ClearanceRTI::DetonationEvent& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = DetonationEventPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::ClearanceRTI::DetonationEvent from cdr buffer");
        }

        void topic_type_support< ::ClearanceRTI::DetonationEvent >::reset_sample(::ClearanceRTI::DetonationEvent& sample) 
        {
            ::rti::topic::reset_sample(sample.Header);
            sample.FiringEntity = 0;
            sample.TargetEntity = 0;
            sample.MunitionEntity = 0;
            sample.EventNumber = 0;
            sample.XMeters = 0.0;
            sample.YMeters = 0.0;
            sample.ZMeters = 0.0;
            sample.VxMps = 0.0f;
            sample.VyMps = 0.0f;
            sample.VzMps = 0.0f;
            sample.MunitionKind = 0;
            sample.WarheadKind = 0;
            sample.FuseKind = 0;
            sample.Quantity = 0;
            sample.Rate = 0;
            sample.DetonationResult = 0;
        }

        void topic_type_support< ::ClearanceRTI::DetonationEvent >::allocate_sample(::ClearanceRTI::DetonationEvent& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.Header,  -1, -1);
        }
        void topic_type_support< ::ClearanceRTI::EmissionSnapshot >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::ClearanceRTI::EmissionSnapshotPlugin_new,
                ::ClearanceRTI::EmissionSnapshotPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::ClearanceRTI::EmissionSnapshot >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::ClearanceRTI::EmissionSnapshot& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = EmissionSnapshotPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = EmissionSnapshotPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::ClearanceRTI::EmissionSnapshot >::from_cdr_buffer(::ClearanceRTI::EmissionSnapshot& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = EmissionSnapshotPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::ClearanceRTI::EmissionSnapshot from cdr buffer");
        }

        void topic_type_support< ::ClearanceRTI::EmissionSnapshot >::reset_sample(::ClearanceRTI::EmissionSnapshot& sample) 
        {
            ::rti::topic::reset_sample(sample.Header);
            sample.EmittingEntity = 0;
            sample.PositionMetersX = 0.0;
            sample.PositionMetersY = 0.0;
            sample.PositionMetersZ = 0.0;
            sample.EmitterName = 0;
            sample.EmitterFunction = 0;
            sample.FrequencyLowHz = 0.0f;
            sample.FrequencyHighHz = 0.0f;
            sample.EffectiveRadiatedPowerDbm = 0.0f;
            sample.PulseRepetitionFreqHz = 0.0f;
            sample.PulseWidthMicrosec = 0.0f;
            sample.BeamAzimuthRad = 0.0f;
            sample.BeamFunction = 0;
            ::rti::topic::reset_sample(sample.PaintedEntityNumbers);
        }

        void topic_type_support< ::ClearanceRTI::EmissionSnapshot >::allocate_sample(::ClearanceRTI::EmissionSnapshot& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.Header,  -1, -1);
            ::rti::topic::allocate_sample(sample.PaintedEntityNumbers,  100L, -1);
        }
        void topic_type_support< ::ClearanceRTI::TransmitterState >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::ClearanceRTI::TransmitterStatePlugin_new,
                ::ClearanceRTI::TransmitterStatePlugin_delete);
        }

        std::vector<char>& topic_type_support< ::ClearanceRTI::TransmitterState >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::ClearanceRTI::TransmitterState& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = TransmitterStatePlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = TransmitterStatePlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::ClearanceRTI::TransmitterState >::from_cdr_buffer(::ClearanceRTI::TransmitterState& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = TransmitterStatePlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::ClearanceRTI::TransmitterState from cdr buffer");
        }

        void topic_type_support< ::ClearanceRTI::TransmitterState >::reset_sample(::ClearanceRTI::TransmitterState& sample) 
        {
            ::rti::topic::reset_sample(sample.Header);
            sample.OwnerEntity = 0;
            sample.RadioId = 0;
            sample.FrequencyHz = 0ull;
            sample.BandwidthHz = 0.0f;
            sample.PowerDbm = 0.0f;
            sample.TransmitState = 0;
            sample.AntennaXMeters = 0.0;
            sample.AntennaYMeters = 0.0;
            sample.AntennaZMeters = 0.0;
        }

        void topic_type_support< ::ClearanceRTI::TransmitterState >::allocate_sample(::ClearanceRTI::TransmitterState& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.Header,  -1, -1);
        }
        void topic_type_support< ::ClearanceRTI::SignalEvent >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::ClearanceRTI::SignalEventPlugin_new,
                ::ClearanceRTI::SignalEventPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::ClearanceRTI::SignalEvent >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::ClearanceRTI::SignalEvent& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = SignalEventPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = SignalEventPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::ClearanceRTI::SignalEvent >::from_cdr_buffer(::ClearanceRTI::SignalEvent& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = SignalEventPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::ClearanceRTI::SignalEvent from cdr buffer");
        }

        void topic_type_support< ::ClearanceRTI::SignalEvent >::reset_sample(::ClearanceRTI::SignalEvent& sample) 
        {
            ::rti::topic::reset_sample(sample.Header);
            sample.OwnerEntity = 0;
            sample.RadioId = 0;
            ::rti::topic::reset_sample(sample.Data);
        }

        void topic_type_support< ::ClearanceRTI::SignalEvent >::allocate_sample(::ClearanceRTI::SignalEvent& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.Header,  -1, -1);
            ::rti::topic::allocate_sample(sample.Data,  100L, -1);
        }
    }
}  

#endif // NDDS_STANDALONE_TYPE
