#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG_LEVEL_ERR 1
#define LOG_LEVEL_INF 2
#define LOG_LEVEL_DBG 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DBG
#endif

void log_prefix(const char *level, const char *func, int line);
void log_version(void);

#define LOG_ERR(fmt, ...) \
    do { log_prefix("ERR", __func__, __LINE__); printf(fmt "\n", ##__VA_ARGS__); } while (0)

#define LOG_INF(fmt, ...) \
    do { if (LOG_LEVEL >= LOG_LEVEL_INF) { log_prefix("INF", __func__, __LINE__); printf(fmt "\n", ##__VA_ARGS__); } } while (0)

#define LOG_DBG(fmt, ...) \
    do { if (LOG_LEVEL >= LOG_LEVEL_DBG) { log_prefix("DBG", __func__, __LINE__); printf(fmt "\n", ##__VA_ARGS__); } } while (0)

#endif /* LOG_H */