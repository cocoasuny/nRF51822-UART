/**
  ****************************************************************************************
  * @file    ble_central_manage.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-29
  * @brief   ble central manage
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 Chengdu CloudCare Healthcare Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ble_central_manage.h"


/* private variables declare -------------------------------------------------*/
static ble_db_discovery_t m_ble_db_discovery[CENTRAL_LINK_COUNT + PERIPHERAL_LINK_COUNT]; /**< list of DB structures used by the database discovery module. */



/* private function decalre --------------------------------------------------*/
static void scan_advertise_data_report(const ble_gap_evt_adv_report_t *adv_report);


/**
 * @brief Parameters used when scanning.
 */
static const ble_gap_scan_params_t m_scan_params =
{
    .active   = 1,
    .interval = SCAN_INTERVAL,
    .window   = SCAN_WINDOW,
    .timeout  = SCAN_TIMEOUT,
    #if (NRF_SD_BLE_API_VERSION == 2)
        .selective   = 0,
        .p_whitelist = NULL,
    #endif
    #if (NRF_SD_BLE_API_VERSION == 3)
        .use_whitelist = 0,
    #endif
};


/**
  * @brief  Function for initiating scanning.
  * @note   Function for initiating scanning.
  * @param  None
  * @retval None
  */
void scan_start(void)
{
    ret_code_t err_code;

    (void) sd_ble_gap_scan_stop();

    err_code = sd_ble_gap_scan_start(&m_scan_params);
    // It is okay to ignore this error since we are stopping the scan anyway.
    if (err_code != NRF_ERROR_INVALID_STATE)
    {
        APP_ERROR_CHECK(err_code);
    }       
}

/**
  * @brief  Function for initiating stop scanning.
  * @note   Function for initiating stop scanning.
  * @param  None
  * @retval None
  */
void scan_stop(void)
{
	sd_ble_gap_scan_stop();
}

/**
  * @brief  Function for handling BLE Stack events concerning central applications.
  * @note   This function keeps the connection handles of central applications up-to-date. It
  *         parses scanning reports, initiating a connection attempt to peripherals when a target UUID
  *         is found, and manages connection parameter update requests.
  *         Since this function updates connection handles, @ref BLE_GAP_EVT_DISCONNECTED events
  *         should be dispatched to the target application before invoking this function.
  * @param  p_ble_evt   Bluetooth stack event.
  * @retval None
  */
void on_ble_central_evt(const ble_evt_t * const p_ble_evt)
{
    const ble_gap_evt_t   		* const p_gap_evt = &p_ble_evt->evt.gap_evt;
    ret_code_t                    err_code;

    switch (p_ble_evt->header.evt_id)
    {
        /** Upon connection, check which peripheral has connected, initiate DB
         *  discovery,resume scanning if necessary. */
        case BLE_GAP_EVT_CONNECTED:
        {
			#ifdef DEBUG_BLE_CONNECT
				printf("CENTRAL: connected\r\n");
			#endif
  
			/* 开始查找当前连接中peripheral端所包含的服务 */
			#ifdef DEBUG_BLE_CONNECT
                printf("CENTRAL: start to find service on conn_handle 0x%x\r\n", p_gap_evt->conn_handle);
			#endif

			APP_ERROR_CHECK_BOOL(p_gap_evt->conn_handle < CENTRAL_LINK_COUNT + PERIPHERAL_LINK_COUNT);
			err_code = ble_db_discovery_start(&m_ble_db_discovery[p_gap_evt->conn_handle], p_gap_evt->conn_handle);
			APP_ERROR_CHECK(err_code);
            
            /** check if we should be looking for more peripherals to connect to. */
            if (ble_conn_state_n_centrals() <= CENTRAL_LINK_COUNT)
            {
                 // Resume scanning.
                scan_start();
            }
            else
            {
				// 已达到连接设备数量上限
            }
        } break; // BLE_GAP_EVT_CONNECTED

        /** Upon disconnection, reset the connection handle of the peer which disconnected, and start scanning again. */
        case BLE_GAP_EVT_DISCONNECTED:
        {
			#ifdef DEBUG_BLE_CONNECT
				printf("CENTRAL: disconnected (reason: %d)\r\n",p_gap_evt->params.disconnected.reason);
			#endif
            
			// Start scanning
			scan_start();
        } break; // BLE_GAP_EVT_DISCONNECTED

        case BLE_GAP_EVT_ADV_REPORT:
        {
			scan_advertise_data_report(&p_gap_evt->params.adv_report);
//            if (strlen(m_target_periph_name) != 0)
//            {
//                if (find_adv_name(&p_gap_evt->params.adv_report, m_target_periph_name))
//                {
//                    // Initiate connection.
//                    NRF_LOG_INFO("central connecting ...\r\n");
//                    err_code = sd_ble_gap_connect(&p_gap_evt->params.adv_report.peer_addr,
//                                                  &m_scan_params,
//                                                  &m_connection_param);
//                    if (err_code != NRF_SUCCESS)
//                    {
//                        printf("Connection Request Failed, reason %d\r\n", err_code);
//                    }
//                }
//            }
//            else
//            {
//               /** We do not want to connect to two peripherals offering the same service, so when
//                *  a UUID is matched, we check that we are not already connected to a peer which
//                *  offers the same service. */
//                if (find_adv_uuid(&p_gap_evt->params.adv_report, BLE_UUID_HEART_RATE_SERVICE)&&
//                     (m_conn_handle_hrs_c == BLE_CONN_HANDLE_INVALID))
//                {
//                    // Initiate connection.
//                    NRF_LOG_INFO("CENTRAL: connecting ...\r\n");
//                    err_code = sd_ble_gap_connect(&p_gap_evt->params.adv_report.peer_addr,
//                                                  &m_scan_params,
//                                                  &m_connection_param);
//                    if (err_code != NRF_SUCCESS)
//                    {
//                        printf("CENTRAL: Connection Request Failed, reason %d\r\n", err_code);
//                    }
//                }
//            }
        } break; // BLE_GAP_ADV_REPORT

        case BLE_GAP_EVT_TIMEOUT:
        {
            // We have not specified a timeout for scanning, so only connection attemps can timeout.
            if (p_gap_evt->params.timeout.src == BLE_GAP_TIMEOUT_SRC_CONN)
            {
				#ifdef DEBUG_BLE_CONNECT
					printf("CENTRAL: Connection Request timed out.\r\n");
				#endif
            }
        } break; // BLE_GAP_EVT_TIMEOUT

        case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST:
        {
            // Accept parameters requested by peer.
            err_code = sd_ble_gap_conn_param_update(p_gap_evt->conn_handle,
                                        &p_gap_evt->params.conn_param_update_request.conn_params);
            APP_ERROR_CHECK(err_code);
        } break; // BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST

        case BLE_GATTC_EVT_TIMEOUT:
            // Disconnect on GATT Client timeout event.
			#ifdef DEBUG_BLE_CONNECT
				printf("CENTRAL: GATT Client Timeout.\r\n");
			#endif
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTC_EVT_TIMEOUT

        case BLE_GATTS_EVT_TIMEOUT:
            // Disconnect on GATT Server timeout event.
			#ifdef DEBUG_BLE_CONNECT
				printf("CENTRAL: GATT Server Timeout.\r\n");
			#endif
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_TIMEOUT

#if (NRF_SD_BLE_API_VERSION == 3)
        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
            err_code = sd_ble_gatts_exchange_mtu_reply(p_ble_evt->evt.gatts_evt.conn_handle,
                                                       NRF_BLE_MAX_MTU_SIZE);
            APP_ERROR_CHECK(err_code);
            break; // BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST
#endif

        default:
            // No implementation needed.
            break;
    }
}
/**
  * @brief  Function for handling advertise data report
  * @note   Central端处理扫描到的广播数据报告
  * @param  ble_gap_evt_adv_report_t *adv_report
  * @retval None
  */
static void scan_advertise_data_report(const ble_gap_evt_adv_report_t *adv_report)
{
//	uint8_t				i = 0;
	#ifdef DEBUG_BLE_CONNECT
//		printf("peer addr:0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\r\n",adv_report->peer_addr.addr[0],\
//											adv_report->peer_addr.addr[1],adv_report->peer_addr.addr[2],\
//											adv_report->peer_addr.addr[3],adv_report->peer_addr.addr[4],\
//											adv_report->peer_addr.addr[5]);
//		printf("Adv Data:");
//		for(i=0;i<adv_report->dlen;i++)
//		{
//			printf("0x%x, ",adv_report->data[i]);
//		}
//		printf("\r\n");
	#endif
}



/************************ (C) COPYRIGHT Chengdu CloudCare Healthcare Co., Ltd. *****END OF FILE****/

