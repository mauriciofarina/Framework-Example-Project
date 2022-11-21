/**
 * @file drv_gpio.c
 * @author Mauricio Dall Oglio Farina
 * @brief GPIO Driver
 */
#include "drv_gpio.h"

#include "driver/gpio.h"

#include "gpio/mid_gpio.h"

#define STATUS_LED_PIN 2 /** Status LED Pin Number */

void drv_gpio_init(void) {
    gpio_reset_pin(STATUS_LED_PIN);
    gpio_set_direction(STATUS_LED_PIN, GPIO_MODE_OUTPUT);
}

void mid_gpio_set_pin(mid_gpio_pin_t instance, bool enable) {

    switch (instance) {
        case MID_GPIO_STATUS_LED:
            gpio_set_level(STATUS_LED_PIN, enable);
            break;
        default:
            assert(0); // Not Implemented
            break;
    }
}
