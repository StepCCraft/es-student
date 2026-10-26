#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"   // добавлено: gpio_init, gpio_set_dir, gpio_get, gpio_pull_up
#include "led.h"

const uint BUTTON_PIN = 15;
const uint DEBOUNCE_MS = 20;

// Возвращает true, если кнопка стабильно нажата (pin == 0 при pull-up)
static bool get_button_debounce(uint pin)
{
    bool first = gpio_get(pin);
    sleep_ms(DEBOUNCE_MS);
    bool second = gpio_get(pin);

    // состояние считаем валидным только если оба чтения совпали
    if (first != second)
    {
        return false; // дребезг — считаем, что нажатия не было
    }

    // при pull-up нажатие = 0, поэтому инвертируем
    return !second;
}

static void handle_command(int command)
{
    if (command == 'e')
    {
        led_set(true);
        printf("led %s\n", led_is_on() ? "on" : "off");
    }
    else if (command == 'd')
    {
        led_set(false);
        printf("led %s\n", led_is_on() ? "on" : "off");
    }
    else
    {
        printf("unknown command: %c\n", command);
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

        // фронт: было не нажато -> стало нажато
        if (!previous_pressed && current_pressed)
        {
            led_toggle();
            printf("led %s\n", led_is_on() ? "on" : "off");
        }

        previous_pressed = current_pressed;

        int command = getchar_timeout_us(0);

        if (command == PICO_ERROR_TIMEOUT)
        {
            continue;
        }

        handle_command(command);
    }
}