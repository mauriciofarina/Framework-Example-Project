/**
 * @file drv_wifi.c
 * @author Mauricio Dall Oglio Farina
 * @brief WiFi Implementation
 */
#include "drv_wifi.h"

#include "wifi/mid_wifi.h"

#include "esp_log.h"
#include "esp_wifi.h"

#define WIFI_STA_TAG "WIFI_STA" /** WiFi Station Log Tag */

/**
 * @brief WiFi Station Event Handler
 *
 * @param arg[in] Arguments (Not Used)
 * @param event_base[in] Event Base (Not Used)
 * @param event_id[in] Event ID
 * @param event_data[in] Event Data (Not Used)
 */
static void wifi_sta_event(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
static void ip_sta_event(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

static void wifi_sta_event(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {

    switch (event_id) {

        case WIFI_EVENT_STA_START:
            ESP_LOGI(WIFI_STA_TAG, "Connecting...");
            esp_wifi_connect();
            break;
        case WIFI_EVENT_STA_CONNECTED:
            ESP_LOGI(WIFI_STA_TAG, "Connected to Access Point");
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            ESP_LOGW(WIFI_STA_TAG, "WIFI Connection Lost");
            esp_wifi_connect();
            break;
        default:
            // Ignored
            break;
    }
}

/**
 * @brief WiFi Station IP Event Handler
 *
 * @param arg[in] Arguments (Not Used)
 * @param event_base[in] Event Base (Not Used)
 * @param event_id[in] Event ID
 * @param event_data[in] Event Data
 */
static void ip_sta_event(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {

    switch (event_id) {

        case IP_EVENT_STA_GOT_IP: {
            ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
            ESP_LOGI(WIFI_STA_TAG, "Receive IP:" IPSTR, IP2STR(&event->ip_info.ip));
        } break;
        default:
            // Ignored
            break;
    }
}

void drv_wifi_init(void) {

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, WIFI_EVENT_STA_START, &wifi_sta_event, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &wifi_sta_event, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &wifi_sta_event, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_sta_event, NULL, NULL));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void mid_wifi_start_station(mid_wifi_config_t *const config) {

    wifi_config_t wifi_config_sta = {0};
    memcpy(wifi_config_sta.sta.ssid, config->ssid, MID_WIFI_MAX_SSID_SIZE);
    memcpy(wifi_config_sta.sta.password, config->password, MID_WIFI_MAX_PASSWORD_SIZE);

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config_sta));
}

void mid_wifi_start_access_point(mid_wifi_config_t *const config) {

    wifi_config_t wifi_config_ap = {
        .ap = {
            .max_connection = 0,
        },
    };
    memcpy(wifi_config_ap.ap.ssid, config->ssid, MID_WIFI_MAX_SSID_SIZE);
    memcpy(wifi_config_ap.ap.password, config->password, MID_WIFI_MAX_PASSWORD_SIZE);

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config_ap));
}

void mid_wifi_scan(mid_wifi_scan_t *buffer, uint32_t *items) {

    wifi_ap_record_t ap_records[*items];
    uint16_t max_records = *items;
    wifi_scan_config_t scan_config = {0};

    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&max_records, ap_records));

    for (uint32_t i = 0; i < max_records; ++i) {
        strcpy(buffer[i].ssid, (char *)ap_records[i].ssid);
        buffer[i].rssi = ap_records[i].rssi;
    }

    *items = max_records;
}
