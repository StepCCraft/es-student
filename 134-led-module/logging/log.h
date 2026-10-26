#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/* 1. Сначала — числовые уровни */
#define LOG_LEVEL_ERR 1
#define LOG_LEVEL_INF 2
#define LOG_LEVEL_DBG 3

/* 2. Потом — порог (по умолчанию самый подробный) */
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DBG
#endif

/* Прототипы функций модуля журнала */
void log_prefix(const char *level, const char *func, int line);
void log_version(void);

/* Макросы логирования.
 * LOG_INF и LOG_DBG определены всегда — этого ждёт автотест;
 * тишина при пониженном пороге достигается пустым телом. */

#define LOG_ERR(fmt, ...) \
    do { \
        log_prefix("ERR", __func__, __LINE__); \
        printf(fmt "\n", ##__VA_ARGS__); \
    } while (0)

#if LOG_LEVEL >= LOG_LEVEL_INF
#  define LOG_INF(fmt, ...) \
    do { \
        log_prefix("INF", __func__, __LINE__); \
        printf(fmt "\n", ##__VA_ARGS__); \
    } while (0)
#else
#  define LOG_INF(fmt, ...) do { } while (0)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DBG
#  define LOG_DBG(fmt, ...) \
    do { \
        log_prefix("DBG", __func__, __LINE__); \
        printf(fmt "\n", ##__VA_ARGS__); \
    } while (0)
#else
#  define LOG_DBG(fmt, ...) do { } while (0)
#endif

#endif /* LOG_H */