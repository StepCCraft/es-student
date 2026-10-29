#include "device.h"

#include <stdio.h>
#include "pico/unique_id.h"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/sysinfo.h"

void device_info(void)
{
    /* 1. Серийный номер платы — готовой функцией SDK. */
    char board_id[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];
    pico_get_unique_board_id_string(board_id, sizeof(board_id));

    /* 2. Регистр CHIP_ID в блоке SYSINFO — чтение по адресу через volatile. */
    volatile uint32_t *chip_id_reg =
        (volatile uint32_t *)(SYSINFO_BASE + SYSINFO_CHIP_ID_OFFSET);
    uint32_t id = *chip_id_reg;

    /* 3. Разбор трёх полей по маскам и сдвигам из sysinfo.h. */
    uint32_t manufacturer =
        (id & SYSINFO_CHIP_ID_MANUFACTURER_BITS) >> SYSINFO_CHIP_ID_MANUFACTURER_LSB;
    uint32_t part =
        (id & SYSINFO_CHIP_ID_PART_BITS) >> SYSINFO_CHIP_ID_PART_LSB;
    uint32_t revision =
        (id & SYSINFO_CHIP_ID_REVISION_BITS) >> SYSINFO_CHIP_ID_REVISION_LSB;

    /* 4. Пять строк паспорта, формат «ключ: значение». */
    printf("project: %s\n", DEVICE_PROJECT);
    printf("repo: %s\n",    DEVICE_REPO);
    printf("board: %s\n",   DEVICE_BOARD);
    printf("serial: %s\n",  board_id);
    printf("chip: manufacturer 0x%03x, part 0x%04x, revision %u\n",
           (unsigned)manufacturer, (unsigned)part, (unsigned)revision);
}