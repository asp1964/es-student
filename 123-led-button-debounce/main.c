
#include "pico/stdlib.h"
// добавляем заголовочный файл функций ввода-вывода

#include "hardware/gpio.h"
// добавляем заголовочный файл функций работы с GPIO

const uint DEBOUNCE_MS = 20;
const uint BUTTON_PIN = 15;
const uint LED_PIN = 18;
// объявляем константу вывода светодиода

bool get_button_debounce(uint pin)
{
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE_MS);
    return state && gpio_get(pin);
}
int main()
{
     
    gpio_init(LED_PIN);
    
    // инициализируем пин светодиода

    gpio_set_dir(LED_PIN, GPIO_OUT);
    // настраиваем пин светодиода на выход

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    bool led = false;
    bool previous = false;

    while (1)
    {
       
       bool current = get_button_debounce(BUTTON_PIN);
       // bool current = gpio_get(BUTTON_PIN);

        if (previous == true && current == false)
        {
            led = !led;
            gpio_put(LED_PIN, led);
        }

        previous = current;
    }
}