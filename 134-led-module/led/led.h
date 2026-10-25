#ifndef LED_H
#define LED_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void led_init(void);
void led_set(bool on);
void led_toggle(void);
bool led_is_on(void);

#ifdef __cplusplus
}
#endif

#endif