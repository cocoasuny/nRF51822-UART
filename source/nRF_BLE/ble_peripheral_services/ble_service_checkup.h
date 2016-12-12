/**
  ****************************************************************************************
  * @file    ble_service_checkup.h
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-29
  * @brief   header of ble_service_checkup.c 
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLE_SERVICE_CHECKUP_H__
#define __BLE_SERVICE_CHECKUP_H__

#include "main.h"


/* check up service and characters uuid define */
#define CHECK_UP_UUID_BASE                   {0x30,0x4F,0x43,0xFB,0x4A,0xBA,0x8B,0x15,0xE0,0x76,0xD9,0x02,0x11,0x23,0x97,0x08} 
#define CHECK_UP_UUID_SERVICE                0x2311
#define CHECK_UP_UUID_PARAM_CHAR             0x2312
#define CHECK_UP_UUID_DATA_UPDATE_CHAR       0x2313


// Forward declaration of the ble_checkup_service_t type.
typedef struct ble_checkup_s ble_checkup_service_t;

/** @brief check up service event handler type */
typedef void (*ble_checkup_service_evt_handler_t) (ble_checkup_service_t *p_checkup_service,ble_gatts_evt_write_t *p_evt);


/* type struct defines for check up service */
typedef struct ble_checkup_s
{
	ble_checkup_service_evt_handler_t	evt_handler; 	/**< Event handler to be called for handling events in the Check up Service. */
	uint16_t							service_handler;/**< Handle of Check Up Service (as provided by the BLE stack). */
    uint16_t                     		conn_handle;    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
	ble_gatts_char_handles_t            param_char_handle;/**< Handles related to the check up parameters characteristic. */
	ble_gatts_char_handles_t            data_update_char_handles;/**< Handles related to the check up parameters characteristic. */	
	uint8_t                       		uuid_type;
}ble_checkup_service_t;

/** @brief Check up service init structure. This contains all options and data needed for 
 *         initalization of the service */
typedef	struct
{
	ble_checkup_service_evt_handler_t	evt_handler; 	/**< Event handler to be called for handling events in the Check up Service. */	
}ble_checkup_service_init_t;



/* extern variables declare */
extern ble_checkup_service_t	gBleServiceCheckUp;


/* extern function declare */
uint32_t ble_checkup_service_init(ble_checkup_service_t *p_checkup_service,
								  ble_checkup_service_init_t *p_checkup_service_init);


#endif // __BLE_SERVICE_CHECKUP_H__

/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/




