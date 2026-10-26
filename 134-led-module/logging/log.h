#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/*
 * Уровни логирования.
 * Чем больше число — тем подробнее вывод.
 */
#define LOG_LEVEL_ERR 1
#define LOG_LEVEL_INF 2
#define LOG_LEVEL_DBG 3

/*
 * Порог логирования.
 * Можно переопределить при сборке: -DLOG_LEVEL=LOG_LEVEL_INF
 * По умолчанию — самый подробный режим.
 */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_DBG
#endif

/*
 * На основании порога решаем, какие макросы вообще компилируются.
 * Если уровень выключен — макрос раскрывается в пустой оператор,
 * и строковые литералы сообщений не попадают в бинарь.
 */
#if LOG_LEVEL == LOG_LEVEL_ERR
#  define LOG_ENABLE_INF 0
#  define LOG_ENABLE_DBG 0
#elif LOG_LEVEL == LOG_LEVEL_INF
#  define LOG_ENABLE_INF 1
#  define LOG_ENABLE_DBG 0
#elif LOG_LEVEL == LOG_LEVEL_DBG
#  define LOG_ENABLE_INF 1
#  define LOG_ENABLE_DBG 1
#else
#  error "LOG_LEVEL must be LOG_LEVEL_ERR, LOG_LEVEL_INF or LOG_LEVEL_DBG"
#endif

/*
 * Формат строки журнала:
 *   [УРОВЕНЬ] функция:строка: сообщение
 *
 * __func__ и __LINE__ подставляются автоматически в месте вызова,
 * поэтому сразу видно, откуда пришло сообщение.
 */

/* LOG_ERR включён всегда */
#define LOG_ERR(fmt, ...) \
    do { \
        fprintf(stderr, "[ERR] %s:%d: " fmt "\n", \
                __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#if LOG_ENABLE_INF
#  define LOG_INF(fmt, ...) \
    do { \
        fprintf(stdout, "[INF] %s:%d: " fmt "\n", \
                __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#  define LOG_INF(fmt, ...) do { } while (0)
#endif

#if LOG_ENABLE_DBG
#  define LOG_DBG(fmt, ...) \
    do { \
        fprintf(stdout, "[DBG] %s:%d: " fmt "\n", \
                __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#  define LOG_DBG(fmt, ...) do { } while (0)
#endif

#endif /* LOG_H */