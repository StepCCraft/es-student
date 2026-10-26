#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "led.h"
#include "log.h"          /* буквально "log.h" — этого ждёт автотест */

const uint BUTTON_PIN = 15;
const uint DEBOUNCE_MS = 20;

static bool get_button_debounce(uint pin)
{
    bool first = gpio_get(pin);
    sleep_ms(DEBOUNCE_MS);
    bool second = gpio_get(pin);

    if (first != second)
    {
        return false;
    }
    return !second;
}

static void handle_command(int command)
{
    if (command == 'e')
    {
        led_set(true);
        LOG_INF("led %s", led_is_on() ? "on" : "off");
    }
    else if (command == 'd')
    {
        led_set(false);
        LOG_INF("led %s", led_is_on() ? "on" : "off");
    }
    else if (command == 'v')
    {
        log_version();
    }
    else
    {
        LOG_ERR("unknown command: %c", command);
    }
}

int main(void)
{
    stdio_init_all();

    led_init();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    bool previous_pressed = false;

    while (true)
    {
        bool current_pressed = get_button_debounce(BUTTON_PIN);

        if (!previous_pressed && current_pressed)
        {
            led_toggle();
            LOG_INF("led %s", led_is_on() ? "on" : "off");
        }

        previous_pressed = current_pressed;

        int command = getchar_timeout_us(0);

        if (command == PICO_ERROR_TIMEOUT)
        {
            continue;
        }

        LOG_DBG("got %c", command);
        handle_command(command);
    }
}