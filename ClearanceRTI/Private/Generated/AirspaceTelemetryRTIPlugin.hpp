

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from AirspaceTelemetryRTI.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef AirspaceTelemetryRTIPlugin_1287320769_h
#define AirspaceTelemetryRTIPlugin_1287320769_h

#include "AirspaceTelemetryRTI.hpp"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
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

    #define WireHeaderPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define WireHeaderPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define WireHeaderPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define WireHeaderPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define WireHeaderPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern WireHeader*
    WireHeaderPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern WireHeader*
    WireHeaderPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern WireHeader*
    WireHeaderPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    WireHeaderPluginSupport_copy_data(
        WireHeader *out,
        const WireHeader *in);

    NDDSUSERDllExport extern void
    WireHeaderPluginSupport_destroy_data_w_params(
        WireHeader *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    WireHeaderPluginSupport_destroy_data_ex(
        WireHeader *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    WireHeaderPluginSupport_destroy_data(
        WireHeader *sample);

    NDDSUSERDllExport extern void
    WireHeaderPluginSupport_print_data(
        const WireHeader *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    WireHeaderPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    WireHeaderPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    WireHeaderPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    WireHeaderPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    WireHeaderPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        WireHeader *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    WireHeaderPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        WireHeader *out,
        const WireHeader *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    WireHeaderPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const WireHeader *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    WireHeaderPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        WireHeader **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    WireHeaderPlugin_deserialize_from_cdr_buffer(
        WireHeader *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    WireHeaderPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    WireHeaderPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    WireHeaderPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    WireHeaderPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    WireHeaderPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        WireHeader ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    WireHeaderPlugin_new(void);

    NDDSUSERDllExport extern void
    WireHeaderPlugin_delete(struct PRESTypePlugin *);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct AircraftState
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct AircraftState)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * AircraftState must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct AircraftState.
    */
    typedef struct AircraftState AircraftStateKeyHolder;

    #define AircraftStatePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define AircraftStatePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define AircraftStatePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define AircraftStatePlugin_get_key PRESTypePluginDefaultEndpointData_getKey
    #define AircraftStatePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define AircraftStatePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define AircraftStatePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern AircraftState*
    AircraftStatePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern AircraftState*
    AircraftStatePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern AircraftState*
    AircraftStatePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    AircraftStatePluginSupport_copy_data(
        AircraftState *out,
        const AircraftState *in);

    NDDSUSERDllExport extern void
    AircraftStatePluginSupport_destroy_data_w_params(
        AircraftState *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    AircraftStatePluginSupport_destroy_data_ex(
        AircraftState *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    AircraftStatePluginSupport_destroy_data(
        AircraftState *sample);

    NDDSUSERDllExport extern void
    AircraftStatePluginSupport_print_data(
        const AircraftState *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern AircraftState*
    AircraftStatePluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern AircraftState*
    AircraftStatePluginSupport_create_key(void);

    NDDSUSERDllExport extern void
    AircraftStatePluginSupport_destroy_key_ex(
        AircraftStateKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    AircraftStatePluginSupport_destroy_key(
        AircraftStateKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    AircraftStatePlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    AircraftStatePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    AircraftStatePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    AircraftStatePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    AircraftStatePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        AircraftState *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        AircraftState *out,
        const AircraftState *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const AircraftState *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        AircraftState **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_deserialize_from_cdr_buffer(
        AircraftState *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    AircraftStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    AircraftStatePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    AircraftStatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    AircraftStatePlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        AircraftState ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        AircraftStateKeyHolder *key,
        const AircraftState *instance);

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        AircraftState *instance,
        const AircraftStateKeyHolder *key);

    NDDSUSERDllExport extern RTIBool
    AircraftStatePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream,
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    AircraftStatePlugin_new(void);

    NDDSUSERDllExport extern void
    AircraftStatePlugin_delete(struct PRESTypePlugin *);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct FireEvent
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct FireEvent)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * FireEvent must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct FireEvent.
    */
    typedef struct FireEvent FireEventKeyHolder;

    #define FireEventPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define FireEventPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define FireEventPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define FireEventPlugin_get_key PRESTypePluginDefaultEndpointData_getKey
    #define FireEventPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define FireEventPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define FireEventPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern FireEvent*
    FireEventPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern FireEvent*
    FireEventPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern FireEvent*
    FireEventPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    FireEventPluginSupport_copy_data(
        FireEvent *out,
        const FireEvent *in);

    NDDSUSERDllExport extern void
    FireEventPluginSupport_destroy_data_w_params(
        FireEvent *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    FireEventPluginSupport_destroy_data_ex(
        FireEvent *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    FireEventPluginSupport_destroy_data(
        FireEvent *sample);

    NDDSUSERDllExport extern void
    FireEventPluginSupport_print_data(
        const FireEvent *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern FireEvent*
    FireEventPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern FireEvent*
    FireEventPluginSupport_create_key(void);

    NDDSUSERDllExport extern void
    FireEventPluginSupport_destroy_key_ex(
        FireEventKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    FireEventPluginSupport_destroy_key(
        FireEventKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    FireEventPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    FireEventPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    FireEventPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    FireEventPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    FireEventPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        FireEvent *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        FireEvent *out,
        const FireEvent *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const FireEvent *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        FireEvent **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_deserialize_from_cdr_buffer(
        FireEvent *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    FireEventPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    FireEventPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    FireEventPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    FireEventPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        FireEvent ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        FireEventKeyHolder *key,
        const FireEvent *instance);

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        FireEvent *instance,
        const FireEventKeyHolder *key);

    NDDSUSERDllExport extern RTIBool
    FireEventPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream,
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    FireEventPlugin_new(void);

    NDDSUSERDllExport extern void
    FireEventPlugin_delete(struct PRESTypePlugin *);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct DetonationEvent
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct DetonationEvent)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * DetonationEvent must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct DetonationEvent.
    */
    typedef struct DetonationEvent DetonationEventKeyHolder;

    #define DetonationEventPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define DetonationEventPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define DetonationEventPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define DetonationEventPlugin_get_key PRESTypePluginDefaultEndpointData_getKey
    #define DetonationEventPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define DetonationEventPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define DetonationEventPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern DetonationEvent*
    DetonationEventPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern DetonationEvent*
    DetonationEventPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern DetonationEvent*
    DetonationEventPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    DetonationEventPluginSupport_copy_data(
        DetonationEvent *out,
        const DetonationEvent *in);

    NDDSUSERDllExport extern void
    DetonationEventPluginSupport_destroy_data_w_params(
        DetonationEvent *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    DetonationEventPluginSupport_destroy_data_ex(
        DetonationEvent *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    DetonationEventPluginSupport_destroy_data(
        DetonationEvent *sample);

    NDDSUSERDllExport extern void
    DetonationEventPluginSupport_print_data(
        const DetonationEvent *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern DetonationEvent*
    DetonationEventPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern DetonationEvent*
    DetonationEventPluginSupport_create_key(void);

    NDDSUSERDllExport extern void
    DetonationEventPluginSupport_destroy_key_ex(
        DetonationEventKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    DetonationEventPluginSupport_destroy_key(
        DetonationEventKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    DetonationEventPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    DetonationEventPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    DetonationEventPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    DetonationEventPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    DetonationEventPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        DetonationEvent *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        DetonationEvent *out,
        const DetonationEvent *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const DetonationEvent *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        DetonationEvent **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_deserialize_from_cdr_buffer(
        DetonationEvent *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    DetonationEventPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    DetonationEventPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    DetonationEventPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    DetonationEventPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        DetonationEvent ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        DetonationEventKeyHolder *key,
        const DetonationEvent *instance);

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        DetonationEvent *instance,
        const DetonationEventKeyHolder *key);

    NDDSUSERDllExport extern RTIBool
    DetonationEventPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream,
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    DetonationEventPlugin_new(void);

    NDDSUSERDllExport extern void
    DetonationEventPlugin_delete(struct PRESTypePlugin *);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct EmissionSnapshot
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct EmissionSnapshot)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * EmissionSnapshot must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct EmissionSnapshot.
    */
    typedef struct EmissionSnapshot EmissionSnapshotKeyHolder;

    #define EmissionSnapshotPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define EmissionSnapshotPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define EmissionSnapshotPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define EmissionSnapshotPlugin_get_key PRESTypePluginDefaultEndpointData_getKey
    #define EmissionSnapshotPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define EmissionSnapshotPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define EmissionSnapshotPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern EmissionSnapshot*
    EmissionSnapshotPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern EmissionSnapshot*
    EmissionSnapshotPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EmissionSnapshot*
    EmissionSnapshotPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPluginSupport_copy_data(
        EmissionSnapshot *out,
        const EmissionSnapshot *in);

    NDDSUSERDllExport extern void
    EmissionSnapshotPluginSupport_destroy_data_w_params(
        EmissionSnapshot *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    EmissionSnapshotPluginSupport_destroy_data_ex(
        EmissionSnapshot *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    EmissionSnapshotPluginSupport_destroy_data(
        EmissionSnapshot *sample);

    NDDSUSERDllExport extern void
    EmissionSnapshotPluginSupport_print_data(
        const EmissionSnapshot *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern EmissionSnapshot*
    EmissionSnapshotPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern EmissionSnapshot*
    EmissionSnapshotPluginSupport_create_key(void);

    NDDSUSERDllExport extern void
    EmissionSnapshotPluginSupport_destroy_key_ex(
        EmissionSnapshotKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    EmissionSnapshotPluginSupport_destroy_key(
        EmissionSnapshotKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    EmissionSnapshotPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    EmissionSnapshotPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    EmissionSnapshotPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    EmissionSnapshotPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    EmissionSnapshotPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        EmissionSnapshot *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        EmissionSnapshot *out,
        const EmissionSnapshot *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const EmissionSnapshot *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        EmissionSnapshot **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_deserialize_from_cdr_buffer(
        EmissionSnapshot *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    EmissionSnapshotPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    EmissionSnapshotPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    EmissionSnapshotPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EmissionSnapshotPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        EmissionSnapshot ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        EmissionSnapshotKeyHolder *key,
        const EmissionSnapshot *instance);

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        EmissionSnapshot *instance,
        const EmissionSnapshotKeyHolder *key);

    NDDSUSERDllExport extern RTIBool
    EmissionSnapshotPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream,
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    EmissionSnapshotPlugin_new(void);

    NDDSUSERDllExport extern void
    EmissionSnapshotPlugin_delete(struct PRESTypePlugin *);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct TransmitterState
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct TransmitterState)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * TransmitterState must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct TransmitterState.
    */
    typedef struct TransmitterState TransmitterStateKeyHolder;

    #define TransmitterStatePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define TransmitterStatePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define TransmitterStatePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define TransmitterStatePlugin_get_key PRESTypePluginDefaultEndpointData_getKey
    #define TransmitterStatePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define TransmitterStatePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define TransmitterStatePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern TransmitterState*
    TransmitterStatePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern TransmitterState*
    TransmitterStatePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TransmitterState*
    TransmitterStatePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePluginSupport_copy_data(
        TransmitterState *out,
        const TransmitterState *in);

    NDDSUSERDllExport extern void
    TransmitterStatePluginSupport_destroy_data_w_params(
        TransmitterState *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    TransmitterStatePluginSupport_destroy_data_ex(
        TransmitterState *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    TransmitterStatePluginSupport_destroy_data(
        TransmitterState *sample);

    NDDSUSERDllExport extern void
    TransmitterStatePluginSupport_print_data(
        const TransmitterState *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern TransmitterState*
    TransmitterStatePluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern TransmitterState*
    TransmitterStatePluginSupport_create_key(void);

    NDDSUSERDllExport extern void
    TransmitterStatePluginSupport_destroy_key_ex(
        TransmitterStateKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    TransmitterStatePluginSupport_destroy_key(
        TransmitterStateKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    TransmitterStatePlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    TransmitterStatePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    TransmitterStatePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    TransmitterStatePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    TransmitterStatePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        TransmitterState *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        TransmitterState *out,
        const TransmitterState *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const TransmitterState *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        TransmitterState **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_deserialize_from_cdr_buffer(
        TransmitterState *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    TransmitterStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    TransmitterStatePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    TransmitterStatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    TransmitterStatePlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        TransmitterState ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        TransmitterStateKeyHolder *key,
        const TransmitterState *instance);

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        TransmitterState *instance,
        const TransmitterStateKeyHolder *key);

    NDDSUSERDllExport extern RTIBool
    TransmitterStatePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream,
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    TransmitterStatePlugin_new(void);

    NDDSUSERDllExport extern void
    TransmitterStatePlugin_delete(struct PRESTypePlugin *);

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct SignalEvent
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct SignalEvent)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * SignalEvent must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct SignalEvent.
    */
    typedef struct SignalEvent SignalEventKeyHolder;

    #define SignalEventPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define SignalEventPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer
    #define SignalEventPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define SignalEventPlugin_get_key PRESTypePluginDefaultEndpointData_getKey
    #define SignalEventPlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define SignalEventPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample
    #define SignalEventPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern SignalEvent*
    SignalEventPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern SignalEvent*
    SignalEventPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern SignalEvent*
    SignalEventPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool
    SignalEventPluginSupport_copy_data(
        SignalEvent *out,
        const SignalEvent *in);

    NDDSUSERDllExport extern void
    SignalEventPluginSupport_destroy_data_w_params(
        SignalEvent *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void
    SignalEventPluginSupport_destroy_data_ex(
        SignalEvent *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    SignalEventPluginSupport_destroy_data(
        SignalEvent *sample);

    NDDSUSERDllExport extern void
    SignalEventPluginSupport_print_data(
        const SignalEvent *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern SignalEvent*
    SignalEventPluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern SignalEvent*
    SignalEventPluginSupport_create_key(void);

    NDDSUSERDllExport extern void
    SignalEventPluginSupport_destroy_key_ex(
        SignalEventKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void
    SignalEventPluginSupport_destroy_key(
        SignalEventKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData
    SignalEventPlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void
    SignalEventPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData
    SignalEventPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *container_plugin_context);

    NDDSUSERDllExport extern void
    SignalEventPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void
    SignalEventPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        SignalEvent *sample,
        void *handle);

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        SignalEvent *out,
        const SignalEvent *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const SignalEvent *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr());

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        SignalEvent **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_deserialize_from_cdr_buffer(
        SignalEvent *sample,
        const char * buffer,
        unsigned int length);

    NDDSUSERDllExport extern unsigned int
    SignalEventPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind
    SignalEventPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int
    SignalEventPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    SignalEventPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        SignalEvent ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        SignalEventKeyHolder *key,
        const SignalEvent *instance);

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        SignalEvent *instance,
        const SignalEventKeyHolder *key);

    NDDSUSERDllExport extern RTIBool
    SignalEventPlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream,
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    SignalEventPlugin_new(void);

    NDDSUSERDllExport extern void
    SignalEventPlugin_delete(struct PRESTypePlugin *);

} /* namespace ClearanceRTI  */

#if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* AirspaceTelemetryRTIPlugin_1287320769_h */
