# Project Includes
set(include_dirs 
    "."
    "drivers"
    "$ENV{IDF_PATH}/components/freertos/include/freertos"
)

# Core Library Includes
set(core_include_dirs 
    "core/apps"
    "core/classes"
    "core/interfaces"
    "core/libraries"
)

# Project Source Files
set(srcs 
    "main.c"
    "drivers/gpio/drv_gpio.c"
    "drivers/nvs/drv_nvs.c"
    "drivers/wifi/drv_wifi.c"
)

# Core Library Files
set(core_srcs 

# Applications
    "core/apps/system/app_system.c"
    "core/apps/calibration/app_calibration.c"

# Libraries
    "core/libraries/rtos/lib_rtos.c"
    "core/libraries/rtos/classes/rtos_task/cls_rtos_task.c"
    "core/libraries/status_led/lib_status_led.c"
    "core/libraries/wifi/lib_wifi.c"
     "core/libraries/mqtt/esp_mqtt/lib_esp_mqtt.c"

# classes
    "core/classes/sensor/cls_sensor.c"
    "core/classes/sensor_demo/cls_sensor_demo.c"
    "core/classes/sensor_demo/cls_sensor_demo_override.c"

)

# Requirements
set(dependencies 
    nvs_flash
    mqtt
)

set(COMPONENT_REQUIRES "${dependencies}")

idf_component_register(SRCS "${srcs}" "${core_srcs}"
                    INCLUDE_DIRS "${include_dirs}" "${core_include_dirs}"
                    REQUIRES "${dependencies}"
                    )





