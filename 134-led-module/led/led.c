#include "led.h"
#include "pico/stdlib.h"

#ifndef LED_PIN
#  define LED_PIN 25   /* встроенный светодиод на Pico */
#endif

static bool led_state = false;

void led_init(void)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);
    led_state = false;
}

void led_set(bool on)
{
    led_state = on;
    gpio_put(LED_PIN, on ? 1 : 0);
}

void led_toggle(void)
{
    led_set(!led_state);
}

bool led_is_on(void)
{
    return led_state;
}