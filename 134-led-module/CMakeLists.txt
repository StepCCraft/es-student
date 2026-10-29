cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(134_led_module C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.c
    led/led.c
    logging/log.c
    device/device.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/led
    ${CMAKE_CURRENT_SOURCE_DIR}/logging
    ${CMAKE_CURRENT_SOURCE_DIR}/device
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_gpio
    pico_unique_id
)

# Тип платы передаём из настроек сборки в код определением компилятора.
# Имя должно быть PICO_BOARD — этого ждёт автотест.
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PICO_BOARD="${PICO_BOARD}"
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})