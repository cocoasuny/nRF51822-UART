/**
  ****************************************************************************************
  * @file    ble_service_checkup.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-29
  * @brief   ble peripheral service of immediately measure(check up)
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "ble_service_checkup.h"

/* global variabled declare -------------------------------------------------*/
ble_checkup_service_t	gBleServiceCheckUp;


/* private function clare ----------------------------------------------------*/
static uint32_t immediately_measure_parameter_write_char_add(ble_checkup_service_t *p_checkup_service,
													ble_checkup_service_init_t *p_checkup_service_init);
static uint32_t	immediately_measure_result_upload_char_add(ble_checkup_service_t *p_checkup_service,
													ble_checkup_service_init_t *p_checkup_service_init);

/**
  * @brief  ble_checkup_service_init
  * @note   Init for check up service 
  * @param  None
  * @retval None
  */
uint32_t ble_checkup_service_init(ble_checkup_service_t *p_checkup_service,
								  ble_checkup_service_init_t *p_checkup_service_init)
{
	uint32_t   				err_code;
	ble_uuid_t 				ble_uuid;
	ble_uuid128_t 			ble_service_baseUUID = CHECK_UP_UUID_BASE;
	
	/* Initialize service structure */
	p_checkup_service->evt_handler = p_checkup_service_init->evt_handler;
	p_checkup_service->conn_handle = BLE_CONN_HANDLE_INVALID;
	
	/* Add check up service */
	err_code = sd_ble_uuid_vs_add(&ble_service_baseUUID,&p_checkup_service->uuid_type);
	if(err_code != NRF_SUCCESS)
	{
		APP_ERROR_CHECK(err_code);
		return err_code;
	}
	
	ble_uuid.type = p_checkup_service->uuid_type;
	ble_uuid.uuid = CHECK_UP_UUID_SERVICE;
	err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_checkup_service->service_handler);	
    if(err_code != NRF_SUCCESS)
	{
		APP_ERROR_CHECK(err_code);
		return err_code;
	}
	
	/* Add parameter write character for check up service */
	err_code = immediately_measure_parameter_write_char_add(p_checkup_service,p_checkup_service_init);
    if(err_code != NRF_SUCCESS)
	{
		APP_ERROR_CHECK(err_code);
		return err_code;
	}	
	
	/* Add immediately measure result upload character for check up service */
	immediately_measure_result_upload_char_add(p_checkup_service,p_checkup_service_init);
    if(err_code != NRF_SUCCESS)
	{
		APP_ERROR_CHECK(err_code);
		return err_code;
	}	
	
	return NRF_SUCCESS;
}
/**
  * @brief  immediately_measure_parameter_write_char_add
  * @note   add the sample parameter character for check up service
  * @param  *p_checkup_service,*p_checkup_service_init
  * @retval NRF_SUCCESS on success, otherwise an error code.
  */
static uint32_t immediately_measure_parameter_write_char_add(ble_checkup_service_t *p_checkup_service,
													ble_checkup_service_init_t *p_checkup_service_init)
{
    ble_gatts_char_md_t 				char_md;
    ble_gatts_attr_t    				attr_char_value;
    ble_uuid_t          				ble_uuid;
    ble_gatts_attr_md_t 				attr_md;
	uint8_t 							param_attr_value[20];

	memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.write  = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL;
    char_md.p_sccd_md         = NULL;

	BLE_UUID_BLE_ASSIGN(ble_uuid, CHECK_UP_UUID_PARAM_CHAR);
	
	memset(&attr_md, 0, sizeof(attr_md));
	
	BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
	attr_md.vloc       = BLE_GATTS_VLOC_USER;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 1;
	
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = 1;
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = 20;
    attr_char_value.p_value      = param_attr_value;	
	
	return sd_ble_gatts_characteristic_add(p_checkup_service->service_handler,
										    &char_md,
											&attr_char_value,
											&p_checkup_service->param_char_handle);
}
/**
  * @brief  immediately_measure_result_upload_char_add
  * @note   add the immediately measure result upload character for check up service
  * @param  *p_checkup_service,*p_checkup_service_init
  * @retval NRF_SUCCESS on success, otherwise an error code.
  */
static uint32_t	immediately_measure_result_upload_char_add(ble_checkup_service_t *p_checkup_service,
													ble_checkup_service_init_t *p_checkup_service_init)
{
	ble_gatts_char_md_t 				char_md;
	ble_gatts_attr_t    				attr_char_value;
    ble_uuid_t         	 				ble_uuid;
    ble_gatts_attr_md_t 				attr_md;
	uint8_t 							data_attr_value[20];
	
	memset(&char_md, 0, sizeof(char_md));
    char_md.char_props.notify = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
	char_md.p_cccd_md         = NULL;
    char_md.p_sccd_md         = NULL;	
	
	BLE_UUID_BLE_ASSIGN(ble_uuid, CHECK_UP_UUID_DATA_UPDATE_CHAR);
	
	memset(&attr_md, 0, sizeof(attr_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    attr_md.vloc       = BLE_GATTS_VLOC_USER;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 1;
	
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    attr_char_value.p_uuid      = &ble_uuid;
    attr_char_value.p_attr_md   = &attr_md;
    attr_char_value.init_len    = sizeof(uint8_t);
    attr_char_value.init_offs   = 0;
    attr_char_value.max_len     = 20;
    attr_char_value.p_value     = data_attr_value;

	return sd_ble_gatts_characteristic_add(p_checkup_service->service_handler,
											&char_md,
											&attr_char_value,
											&p_checkup_service->data_update_char_handles);
	
}

/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/

