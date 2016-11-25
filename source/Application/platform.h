/**
  ****************************************************************************************
  * @file    platform.h
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-25
  * @brief   platform define 
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_H_
#define __PLATFORM_H_

/* Includes ------------------------------------------------------------------*/


/* debug switch --------------------------------------------------------------*/
#define HARDFAULT_HANDLER_ENABLED	1


/* task stack and priority define */
#define BLE_TOP_IMPLEMENTATION_STACK					256
#define BLE_TOP_IMPLEMENTATION_PRIORITY					2				








/* gpio and buffer define for uart */
#define APP_UART_ENABLED	1
#define RETARGET_ENABLED	1
#ifndef UART_TX_BUF_SIZE
    #define UART_TX_BUF_SIZE 1024         /**< UART TX buffer size. */
#endif
#ifndef UART_RX_BUF_SIZE
    #define UART_RX_BUF_SIZE 1            /**< UART RX buffer size. */
#endif

#define RX_PIN_NUMBER  				11    // UART RX pin number.
#define TX_PIN_NUMBER  				9     // UART TX pin number.
#define CTS_PIN_NUMBER 				10    // UART Clear To Send pin number. Not used if HWFC is set to false
#define RTS_PIN_NUMBER 				8     // Not used if HWFC is set to false




#endif /* __PLATFORM_H_ */


/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/


