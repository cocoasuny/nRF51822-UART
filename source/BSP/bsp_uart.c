/**
  ****************************************************************************************
  * @file    bsp_uart.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-25
  * @brief   bsp uart
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
#include "bsp_uart.h"


/* Includes ------------------------------------------------------------------*/

void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}


/**
  * @brief  uart_init 
  * @note   This function is called  automatically at the beginning of program 
  * @param  None
  * @retval None
  */
void uart_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    const app_uart_comm_params_t comm_params =  
    {
        RX_PIN_NUMBER, 
        TX_PIN_NUMBER, 
        RTS_PIN_NUMBER, 
        CTS_PIN_NUMBER, 
        APP_UART_FLOW_CONTROL_DISABLED, 
        false, 
        UART_BAUDRATE_BAUDRATE_Baud115200
    }; 
        
    APP_UART_FIFO_INIT(&comm_params, 
                       UART_RX_BUF_SIZE, 
                       UART_TX_BUF_SIZE, 
                       uart_error_handle, 
                       APP_IRQ_PRIORITY_LOW,
                       err_code);
    UNUSED_VARIABLE(err_code);
}



/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/

