/**
 * @file drv_nvs.c
 * @author Mauricio Dall Oglio Farina
 * @brief Non-Volatile Storage Implementation
 */
#include "drv_nvs.h"

#include "nvs_flash.h"

void drv_nvs_init(void) {

    esp_err_t result = nvs_flash_init();
    if (result == ESP_ERR_NVS_NO_FREE_PAGES || result == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        result = nvs_flash_init();
    }
    ESP_ERROR_CHECK(result);
}