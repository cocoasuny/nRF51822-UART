/**
  ****************************************************************************************
  * @file    ble_service_passkey.h
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-29
  * @brief   header of ble_service_passkey.c 
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLE_SERVICE_PASSKEY_H__
#define __BLE_SERVICE_PASSKEY_H__

#include "main.h"

/* passkey service and characters uuid define */
#define  PASSKEY_UUID_BASE                  	{0x22,0x1A,0xAC,0xD7,0x5B,0xCA,0xA0,0x5A,0x23,0xD6,0xFA,0xAD,0x39,0x89,0x88,0xC3}
#define  BLE_UUID_PASSKEY_AUTH_SERVICE   		0x8939
#define  BLE_UUID_PASSKEY_FEATURE_CHAR   		0x8940
#define  BLE_UUID_PASSKEY_AUTH_RESULT_CHAR      0x8941

// Forward declaration of the ble_passkey_t type. 
typedef struct ble_passkey_s ble_passkey_service_t;

/**@brief Passkey  Authentication Service event handler type. */

typedef void (*ble_passkey_service_evt_handler_t) (ble_passkey_service_t * p_pas, ble_gatts_evt_write_t *p_evt);

/* type struct defines for passkey confirm service */
typedef struct ble_passkey_s
{
	ble_passkey_service_evt_handler_t	evt_handler; 	/**< Event handler to be called for handling events in the Check up Service. */
	uint16_t							service_handler;/**< Handle of Check Up Service (as provided by the BLE stack). */
    uint16_t                     		conn_handle;    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
	ble_gatts_char_handles_t            passkey_write_handles;/**< Handles related to the check up parameters characteristic. */
	ble_gatts_char_handles_t            passkey_result_handles;/**< Handles related to the check up parameters characteristic. */	
	uint8_t                       		uuid_type;
}ble_passkey_service_t;

/** @brief Check up service init structure. This contains all options and data needed for 
 *         initalization of the service */
typedef	struct
{
	ble_passkey_service_evt_handler_t	evt_handler; 	/**< Event handler to be called for handling events in the Check up Service. */	
}ble_passkey_service_init_t;


/* function declare */
uint32_t ble_passkey_service_init(ble_passkey_service_t *p_passkey_service,
								  ble_passkey_service_init_t *p_checkup_service_init);


/* variables declare */
extern ble_passkey_service_t	gBleServicePasskey;


#endif // __BLE_SERVICE_PASSKEY_H__

/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/




