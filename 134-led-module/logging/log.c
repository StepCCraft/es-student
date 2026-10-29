#include "log.h"
#include "device.h"     /* имя и версия переехали в паспорт */

/* Префикс строки журнала: "[УРОВЕНЬ] функция:строка: " */
void log_prefix(const char *level, const char *func, int line)
{
    printf("[%s] %s:%d: ", level, func, line);
}

/* Строка о прошивке. Печатает сам модуль журнала, без подписи уровня. */
void log_version(void)
{
    printf("device: %s %s, built %s %s, log level %d\n",
           DEVICE_NAME, FIRMWARE_VERSION, __DATE__, __TIME__, LOG_LEVEL);
}