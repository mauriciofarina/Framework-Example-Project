# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)



add_compile_definitions(USE_RTOS_KERNEL)
add_compile_definitions(USE_RTOS_FREERTOS)
add_compile_definitions(USE_ESP_MQTT)

add_compile_definitions(WIFI_STATION_SSID="FARINA")
add_compile_definitions(WIFI_STATION_PASSWORD="farina1501")
add_compile_definitions(WIFI_ACCESS_POINT_SSID="THE_AP")
add_compile_definitions(WIFI_ACCESS_POINT_PASSWORD="THE_PASS")

add_compile_definitions(MQTT_SERVER="mqtt://mqtt.eclipseprojects.io")




set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/components)


include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(sensor_node)


