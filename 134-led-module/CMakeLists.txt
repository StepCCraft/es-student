cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(134_led_module)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.c
    led/led.c
    logging/log.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/led
    ${CMAKE_CURRENT_SOURCE_DIR}/logging
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_gpio
)

# Удалите или закомментируйте следующую строку
# pico_set_linker_script(${PROJECT_NAME} ${PICO_LINKER_SCRIPT})

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})