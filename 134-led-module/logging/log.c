#include "log.h"

/* Имя и версия прибора — можно переопределить при сборке */
#ifndef APP_NAME
#  define APP_NAME "es-led-module"
#endif
#ifndef APP_VERSION
#  define APP_VERSION "1.0.0"
#endif

/* Префикс строки журнала: "[УРОВЕНЬ] функция:строка: " */
void log_prefix(const char *level, const char *func, int line)
{
    printf("[%s] %s:%d: ", level, func, line);
}

/* Строка версии. Печатается самим модулем журнала,
 * без подписи уровня — это разрешённое исключение. */
void log_version(void)
{
    printf("device: %s %s, built %s %s, log level %d\n",
           APP_NAME, APP_VERSION, __DATE__, __TIME__, LOG_LEVEL);
}