#pragma once

/* Сведения о приборе */
#define DEVICE_NAME       "es-led-module"
#define FIRMWARE_VERSION  "1.0.0"

/* Происхождение */
#define DEVICE_PROJECT    "134-led-module"
#define DEVICE_REPO       "https://github.com/sezha/es-student"

/* Тип платы: приходит из CMake как -DPICO_BOARD="pico".
 * Запасное значение — на случай сборки без определения компилятора. */
#ifndef PICO_BOARD
#  define PICO_BOARD      "unknown"
#endif

/* Паспорт устройства: пять строк «ключ: значение» */
void device_info(void);