#include "device.h"

#include <stdio.h>
#include "pico/unique_id.h"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/sysinfo.h"

void device_info(void)
{
    /* 1. Серийный номер платы — готовой функцией SDK.
     * Размер: два hex-символа на байт + завершающий ноль. */
    char board_id[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];
    pico_get_unique_board_id_string(board_id, sizeof(board_id));

    /* 2. Регистр CHIP_ID в блоке SYSINFO — чтение по адресу.
     * volatile обязателен: за адресом не переменная, а регистр устройства,
     * и компилятор не вправе выбросить чтение. */
    volatile uint32_t *chip_id_reg =
        (volatile uint32_t *)(SYSINFO_BASE + SYSINFO_CHIP_ID_OFFSET);
    uint32_t id = *chip_id_reg;

    /* 3. Разбор трёх полей по маскам и сдвигам из sysinfo.h.
     * Маска оставляет нужные разряды, сдвиг переносит их в младшие. */
    uint32_t manufacturer =
        (id & SYSINFO_CHIP_ID_MANUFACTURER_BITS) >> SYSINFO_CHIP_ID_MANUFACTURER_LSB;
    uint32_t part =
        (id & SYSINFO_CHIP_ID_PART_BITS) >> SYSINFO_CHIP_ID_PART_LSB;
    uint32_t revision =
        (id & SYSINFO_CHIP_ID_REVISION_BITS) >> SYSINFO_CHIP_ID_REVISION_LSB;

    /* 4. Пять строк паспорта, формат «ключ: значение».
     * Печатаем напрямую, не через журнал — паспорт не должен
     * исчезать при пониженном пороге вывода.
     * Строки о прошивке здесь нет: о ней отвечает команда v. */
    printf("project: %s\n", DEVICE_PROJECT);
    printf("repo: %s\n",    DEVICE_REPO);
    printf("board: %s\n",   PICO_BOARD);
    printf("serial: %s\n",  board_id);
    printf("chip: manufacturer 0x%03x, part 0x%04x, revision %u\n",
           (unsigned)manufacturer, (unsigned)part, (unsigned)revision);
}