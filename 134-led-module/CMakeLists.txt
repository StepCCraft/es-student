cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(134-led-module C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(134-led-module
    main.c
    led/led.c
    logging/log.c
)

target_include_directories(134-led-module PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/led
    ${CMAKE_CURRENT_SOURCE_DIR}/logging
)

target_link_libraries(134-led-module
    pico_stdlib
    hardware_gpio
)

pico_enable_stdio_usb(134-led-module 1)
pico_enable_stdio_uart(134-led-module 0)

pico_add_extra_outputs(134-led-module)