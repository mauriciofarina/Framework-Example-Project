/**
 * @file main.c
 * @author Mauricio Dall Oglio Farina
 * @brief Project Main
 */
#include <stdio.h>

#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gpio/drv_gpio.h"
#include "nvs/drv_nvs.h"
#include "wifi/drv_wifi.h"

#include "system/app_system.h"

void app_main(void) {

    drv_nvs_init();
    drv_gpio_init();
    drv_wifi_init();

    app_system_start();

    while (1) {
        vTaskSuspend(NULL);
    }
}
