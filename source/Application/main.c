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

/* gloable variables define */
SemaphoreHandle_t 			g_semaphore_ble_event_ready = NULL;				/**< Semaphore raised if there is a new event to be 
																				processed in the BLE thread. */

/* private variables define */
static TaskHandle_t 				m_logger_thread;					  	/**< Definition of Logger thread. */
static TaskHandle_t 				m_ble_top_implementation_thread;      	/**< Definition of BLE stack thread. */


/* private function declare*/
static void logger_thread(void * arg);

/**@brief Thread for handling the logger.
 *
 * @details This thread is responsible for processing log entries if logs are deferred.
 *          Thread flushes all log entries and suspends. It is resumed by idle task hook.
 *
 * @param[in]   arg   Pointer used for passing some arbitrary information (context) from the
 *                    osThreadCreate() call to the thread.
 */
static void logger_thread(void * arg)
{
    UNUSED_PARAMETER(arg);

    while(1)
    {
		printf("Test\r\n");
		vTaskDelay(1000);
    }
}
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
	
	
	/* Init a semaphore for the BLE thread. */
    g_semaphore_ble_event_ready = xSemaphoreCreateBinary();
    if (NULL == g_semaphore_ble_event_ready)
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }	
	
	/* creat a thread for ble top level implementation*/
	if(
		pdPASS != xTaskCreate(ble_top_implementation_thread,"ble",BLE_TOP_IMPLEMENTATION_STACK,NULL,
							  	BLE_TOP_IMPLEMENTATION_PRIORITY,&m_ble_top_implementation_thread)
	)
	{
		APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
	}
	
	/* creat a thread for logger */	
    if (pdPASS != xTaskCreate(logger_thread, "LOG", 256, NULL, 1, &m_logger_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }
	
	// Start FreeRTOS scheduler.
    vTaskStartScheduler();
	
	while(1)
	{
		APP_ERROR_HANDLER(NRF_ERROR_FORBIDDEN);
	}
}

/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/




