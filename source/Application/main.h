/**
  ****************************************************************************************
  * @file    platform.h
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-25
  * @brief   header of main.c
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN__
#define __MAIN__

#include <stdint.h>
#include <string.h>
#include "platform.h"
#include "bsp.h"
#include "nrf_drv_clock.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "ble_top_implementation.h"
#include "ble_central_manage.h"
#include "ble_hci.h"
#include "ble_conn_state.h"
#include "ble_service_passkey.h"
#include "ble_service_checkup.h"



/* type struct define */
typedef struct
{
	uint8_t  DevSupportCap;
	uint8_t  DevREV[3];
	uint8_t  FWREV[3];
	uint8_t  SeriNum[4];
	uint8_t  Flag_ReceviedDevInfor;
    uint8_t  STMBootVersion[3];
    uint8_t  protocolVersion;
}DeviceInfomation_t;





/* gloable variables declare */
extern SemaphoreHandle_t 			g_semaphore_ble_event_ready;
extern DeviceInfomation_t  			g_DeviceInformation; //硬件设备信息


#endif // __MAIN__

/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/




