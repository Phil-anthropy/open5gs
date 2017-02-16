#define TRACE_MODULE _nasies

#include "core_debug.h"
#include "core_lib.h"
#include "nas_ies.h"

/* 9.9.2.0A Device properties
 * See subclause 10.5.7.8 in 3GPP TS 24.008 [13].
 * O TV 1 */
status_t nas_decode_device_properties(
    nas_device_properties_t *device_properties, pkbuf_t *pkbuf)
{
    c_uint16_t size = 1;

    memcpy(device_properties, pkbuf->payload - size, size);
    return CORE_OK;
}

/* 9.9.2.2 Location area identification
 * See subclause 10.5.1.3 in 3GPP TS 24.008 [13]
 * O TV 6 */
status_t nas_decode_location_area_identification(
    nas_location_area_identification_t *old_location_area_identification, 
    pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;

    size = sizeof(nas_location_area_identification_t);
    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(old_location_area_identification, pkbuf->payload - size, size);
    
    old_location_area_identification->lac = 
        ntohs(old_location_area_identification->lac);

    return CORE_OK;
}

/* 9.9.2.4 Mobile station classmark 2
 * See subclause 10.5.1.6 in 3GPP TS 24.008
 * O TLV 5 */
status_t nas_decode_mobile_station_classmark_2(
    nas_mobile_station_classmark_2_t *mobile_station_classmark_2, 
    pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_mobile_station_classmark_2_t *source = pkbuf->payload;

    mobile_station_classmark_2->length = source->length;
    size = mobile_station_classmark_2->length + 
        sizeof(mobile_station_classmark_2->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(mobile_station_classmark_2, pkbuf->payload - size, size);
    
    return CORE_OK;
}

/*9.9.2.5 Mobile station classmark 3
 * See subclause 10.5.1.7 in 3GPP TS 24.008 [13].
 * O TLV 2-34 */
status_t nas_decode_mobile_station_classmark_3(
    nas_mobile_station_classmark_3_t *mobile_station_classmark_3, 
    pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_mobile_station_classmark_3_t *source = pkbuf->payload;

    mobile_station_classmark_3->length = source->length;
    size = mobile_station_classmark_3->length + 
        sizeof(mobile_station_classmark_3->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    /* TODO 
    memcpy(mobile_station_classmark_3, pkbuf->payload - size, size);
    */
    
    return CORE_OK;
}

/* 9.9.2.10 Supported codec list
 * See subclause 10.5.4.32 in 3GPP TS 24.008 [13].
 * O TLV 5-n */
status_t nas_decode_supported_codec_list(
    nas_supported_codec_list_t *supported_codecs, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_supported_codec_list_t *source = pkbuf->payload;

    supported_codecs->length = source->length;
    size = supported_codecs->length + 
        sizeof(supported_codecs->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");

    memcpy(supported_codecs, pkbuf->payload - size, 
           c_min(size, sizeof(nas_supported_codec_list_t)));

    return CORE_OK;
}

status_t nas_decode_additional_update_type(
    nas_additional_update_type_t *additional_update_type, pkbuf_t *pkbuf)
{
    c_uint16_t size = 1;

    memcpy(additional_update_type, pkbuf->payload - size, size);
    return CORE_OK;
}

/* 9.9.3.8 DRX parameter
 * See subclause 10.5.5.6 in 3GPP TS 24.008
 * O TV 3 */
status_t nas_decode_drx_parameter(
    nas_drx_parameter_t *drx_parameter, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;

    size = sizeof(nas_drx_parameter_t);
    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(drx_parameter, pkbuf->payload - size, size);

    return CORE_OK;
}

/* 9.9.3.11 EPS attach type
 * M V 1/2
 * 9.9.3.21 NAS key set identifier 
 * M V 1/2 */
status_t nas_decode_attach_info(
    nas_attach_info_t *attach_info, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;

    size = sizeof(nas_attach_info_t);
    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(attach_info, pkbuf->payload - size, size);

    return CORE_OK;
}

/* 9.9.3.12 EPS mobile identity
 * M LV 5-12 */
status_t nas_decode_eps_mobile_identity(
    nas_eps_mobile_identity_t *eps_mobile_identity, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_eps_mobile_identity_t *source = pkbuf->payload;

    eps_mobile_identity->length = source->length;
    size = eps_mobile_identity->length + sizeof(eps_mobile_identity->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(eps_mobile_identity, pkbuf->payload - size, size);
    if (eps_mobile_identity->type_of_identity == NAS_EPS_MOBILE_IDENTITY_GUTI)
    {
        eps_mobile_identity->u.guti.mme_group_id = 
            ntohs(eps_mobile_identity->u.guti.mme_group_id);
        eps_mobile_identity->u.guti.m_tmsi = 
            ntohl(eps_mobile_identity->u.guti.m_tmsi);
    }
    
    return CORE_OK;
}

/* 9.9.3.15 ESM message container
 * M LV-E 5-n */
status_t nas_decode_esm_message_container(
    nas_esm_message_container_t *esm_message_container, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_esm_message_container_t *source = pkbuf->payload;

    esm_message_container->length = ntohs(source->length);
    size = esm_message_container->length + 
            sizeof(esm_message_container->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    esm_message_container->buffer = pkbuf->payload - size + 
        sizeof(esm_message_container->length);

    return CORE_OK;
}

/* 9.9.3.16A GPRS timer 2
 * See subclause 10.5.7.4 in 3GPP TS 24.008 [13].
 * O TLV 3 */
status_t nas_decode_gprs_timer_2(
    nas_gprs_timer_2_t *t3324_value, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_gprs_timer_2_t *source = pkbuf->payload;

    t3324_value->length = source->length;
    size = t3324_value->length + sizeof(t3324_value->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(t3324_value, pkbuf->payload - size, size);

    return CORE_OK;
}

/* 9.9.3.16B GPRS timer 3
 * See subclause 10.5.7.4a in 3GPP TS 24.008 [13].
 * O TLV 3 */
CORE_DECLARE(status_t) nas_decode_gprs_timer_3(
    nas_gprs_timer_3_t *t3412_extended_value, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_gprs_timer_3_t *source = pkbuf->payload;

    t3412_extended_value->length = source->length;
    size = t3412_extended_value->length + sizeof(t3412_extended_value->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(t3412_extended_value, pkbuf->payload - size, size);

    return CORE_OK;
}

/* 9.9.3.20 MS network capability
 * See subclause 10.5.5.12 in 3GPP TS 24.008
 * O TLV 4-10 */
status_t nas_decode_ms_network_capability(
    nas_ms_network_capability_t *ms_network_capability, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_ms_network_capability_t *source = pkbuf->payload;

    ms_network_capability->length = source->length;
    size = ms_network_capability->length + sizeof(ms_network_capability->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(ms_network_capability, pkbuf->payload - size, size);

    return CORE_OK;
}

/* 9.9.3.20A MS network feature support 
 * See subclause 10.5.1.15 in 3GPP TS 24.008 [13].
 * O TV 1 */

status_t nas_decode_ms_network_feature_support(
    nas_ms_network_feature_support_t *ms_network_feature_support, 
    pkbuf_t *pkbuf)
{
    c_uint16_t size = 1;

    memcpy(ms_network_feature_support, pkbuf->payload - size, size);
    return CORE_OK;
}

/* 9.9.3.24A Network resource identifier container
 * See subclause 10.5.5.31 in 3GPP TS 24.008 [13].
 * O TLV 4 */
status_t nas_decode_network_resource_identifier_container(
    nas_network_resource_identifier_container_t *tmsi_based_nri_container, 
    pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_network_resource_identifier_container_t *source = pkbuf->payload;

    tmsi_based_nri_container->length = source->length;
    size = tmsi_based_nri_container->length + 
        sizeof(tmsi_based_nri_container->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(tmsi_based_nri_container, pkbuf->payload - size, size);
    
    return CORE_OK;
}

/* 9.9.3.26 P-TMSI signature 
 * See subclause 10.5.5.8 in 3GPP TS 24.008
 * O TV 4 */
status_t nas_decode_p_tmsi_signature(
    nas_p_tmsi_signature_t *old_p_tmsi_signature, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;

    size = 3;
    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(old_p_tmsi_signature, pkbuf->payload - size, size);

    *old_p_tmsi_signature = ntohl(*old_p_tmsi_signature);

    return CORE_OK;
}

/* 9.9.3.31 TMSI status
 * See subclause 10.5.5.4 in 3GPP TS 24.008 [13]
 * O TV 1 */
status_t nas_decode_tmsi_status(
    nas_tmsi_status_t *tmsi_status, pkbuf_t *pkbuf)
{
    c_uint16_t size = 1;

    memcpy(tmsi_status, pkbuf->payload - size, size);
    return CORE_OK;
}

/* 9.9.3.32 Tracking area identity
 * O TV 6 */
status_t nas_decode_tracking_area_identity(
    nas_tracking_area_identity_t *last_visited_registered_tai, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;

    size = sizeof(nas_tracking_area_identity_t);
    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(last_visited_registered_tai, pkbuf->payload - size, size);
    
    last_visited_registered_tai->tac = ntohs(last_visited_registered_tai->tac);

    return CORE_OK;
}

/* 9.9.3.34 UE network capability
 * M LV 3-14 */
status_t nas_decode_ue_network_capability(
    nas_ue_network_capability_t *ue_network_capability, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_ue_network_capability_t *source = pkbuf->payload;

    ue_network_capability->length = source->length;
    size = ue_network_capability->length + 
            sizeof(ue_network_capability->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(ue_network_capability, pkbuf->payload - size, size);

    return CORE_OK;
}

/* 9.9.3.44 Voice domain preference and UE's usage setting
 * See subclause 10.5.5.28 in 3GPP TS 24.008 [13].
 * O TLV 3 */
status_t nas_decode_voice_domain_preference_and_ue_usage_setting(
    nas_voice_domain_preference_and_ue_usage_setting_t *
        voice_domain_preference_and_ue_usage_setting, 
    pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_voice_domain_preference_and_ue_usage_setting_t *source = pkbuf->payload;

    voice_domain_preference_and_ue_usage_setting->length = source->length;
    size = voice_domain_preference_and_ue_usage_setting->length + 
        sizeof(voice_domain_preference_and_ue_usage_setting->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(voice_domain_preference_and_ue_usage_setting, 
            pkbuf->payload - size, size);
    
    return CORE_OK;
}

/* 9.9.3.45 GUTI type 
 * O TV 1 */
status_t nas_decode_guti_type(nas_guti_type_t *old_guti_type, pkbuf_t *pkbuf)
{
    c_uint16_t size = 1;

    memcpy(old_guti_type, pkbuf->payload - size, size);
    return CORE_OK;
}

/* 9.9.3.46 Extended DRX parameters
 * See subclause 10.5.5.32 in 3GPP TS 24.008 [13].
 * O TLV 3 */
status_t nas_decode_extended_drx_parameters(
    nas_extended_drx_parameters_t *extended_drx_parameters, pkbuf_t *pkbuf)
{
    c_uint16_t size = 0;
    nas_extended_drx_parameters_t *source = pkbuf->payload;

    extended_drx_parameters->length = source->length;
    size = extended_drx_parameters->length + 
        sizeof(extended_drx_parameters->length);

    d_assert(pkbuf_header(pkbuf, -size) == CORE_OK, 
            return CORE_ERROR, "pkbuf_header error");
    memcpy(extended_drx_parameters, pkbuf->payload - size, size);
    
    return CORE_OK;
}
