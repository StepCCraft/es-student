#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN    15   // замените на свой
#define BUTTON_PIN 14   // замените на свой
#define DEBOUNCE_MS 50

bool get_button_debounce(uint pin)
{
    if (gpio_get(pin) == 0)          // кнопка нажата (подтяжка к VCC)
    {
        sleep_ms(DEBOUNCE_MS);
        return gpio_get(pin) == 0;
    }
    return false;
}

void set_led(bool on)
{
    gpio_put(LED_PIN, on);
    printf("led: %s\n", on ? "on" : "off");
}

bool handle_command(int command, bool led)
{
    if (command == 'e')
    {
        led = true;
        set_led(led);
    }
    else if (command == 'd')
    {
        led = false;
        set_led(led);
    }
    else
    {
        printf("unknown command: %c\n", command);
    }
    return led;
}

int main()
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    bool led = false;
    bool last_button = false;

    while (1)
    {
        // 1. кнопка
        bool button = get_button_debounce(BUTTON_PIN);
        if (button && !last_button)
        {
            led = !led;
            set_led(led);
        }
        last_button = button;

        // 2. команда из порта (последней — приоритет у неё)
        int command = getchar_timeout_us(0);
        if (command == PICO_ERROR_TIMEOUT)
        {
            continue;               // ранний выход
        }

        led = handle_command(command, led);
    }
}