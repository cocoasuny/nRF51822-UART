/**
  ****************************************************************************************
  * @file    bsp.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-25
  * @brief   main program for nRF51822
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
#include "main.h"


/**@brief A function which is hooked to idle task.
 * @note Idle hook must be enabled in FreeRTOS configuration (configUSE_IDLE_HOOK).
 */
void vApplicationIdleHook( void )
{
//     vTaskResume(m_logger_thread);
}
/**@brief Function for application main entry.
 */
int main(void)
{
	/* clock config */
	nrf_drv_clock_init();
	
	/* bsp init */
	bsp_init();
	
	printf("Test\r\n");
	
	while(1)
	{
	
	}
}

/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/




