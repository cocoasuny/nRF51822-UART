/**
  ****************************************************************************************
  * @file    ble_service_passkey.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-29
  * @brief   ble peripheral service of passkey confirm
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
#include "ble_service_passkey.h"

/* Includes ------------------------------------------------------------------*/


/* global variables declare */
ble_passkey_service_t	gBleServicePasskey;


/**
  * @brief  ble_passkey_service_init
  * @note   Init for passkey confirm service 
  * @param  None
  * @retval None
  */
uint32_t ble_passkey_service_init(ble_passkey_service_t *p_passkey_service,
								  ble_passkey_service_init_t *p_passkey_service_init)
{
    uint32_t   					err_code;
    ble_uuid_t 					ble_uuid;
	ble_uuid128_t 				ble_service_baseUUID = PASSKEY_UUID_BASE;
	
	/* Initialize service structure */
	p_passkey_service->conn_handle			= BLE_CONN_HANDLE_INVALID;
	p_passkey_service->evt_handler			= p_passkey_service_init->evt_handler;
	
	/* Add passkey service */
	err_code = sd_ble_uuid_vs_add(&ble_service_baseUUID,&p_passkey_service->uuid_type);
	if(err_code != NRF_SUCCESS)
	{
		APP_ERROR_CHECK(err_code);
		return err_code;
	}
	
	ble_uuid.type = p_passkey_service->uuid_type;
	ble_uuid.uuid = BLE_UUID_PASSKEY_AUTH_SERVICE;
	err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,&ble_uuid,&p_passkey_service->service_handler);
	if(err_code != NRF_SUCCESS)
	{
		APP_ERROR_CHECK(err_code);
		return err_code;
	}
	
	/* Add passkey write character */
	
	/* Add passkey confirm result character */
	
	return NRF_SUCCESS;
}



/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/

