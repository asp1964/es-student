// заголовочные файлы и константы — без изменений
// добавляем заголовочный файл функций ввода-вывода
#include "pico/stdlib.h"


// добавляем заголовочный файл функций работы с GPIO
#include <stdio.h>
#include "hardware/gpio.h"


const uint DEBOUNCE_MS = 20;
const uint BUTTON_PIN = 15;

// объявляем константу вывода светодиода
const uint LED_PIN = 18;


bool get_button_debounce(uint pin)
{
    // читаем вывод устойчиво к дребезгу
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE_MS);
    return state && gpio_get(pin);
}

void set_led(bool on)
{
    // выставляем уровень на выводе и сообщаем о состоянии в порт
    gpio_put(LED_PIN, on);
    printf("led %s\n", on ? "on" : "off");
}

// разбираем команду и возвращаем новое состояние светодиода
bool handle_command(int command, bool led)
{
    
    
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
}

int main()
{
    // включаем стандартный ввод-вывод
    // инициализируем и настраиваем выводы

    
    stdio_init_all();
     
    gpio_init(LED_PIN);
     
    gpio_set_dir(LED_PIN, GPIO_OUT);
   
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // объявляем переменные
    bool led = false;
    bool previous = false;

    while (1)
    {
        // читаем состояние пина кнопки с задержкой
        bool current = get_button_debounce(BUTTON_PIN);

        // если состояние сменилось — переключаем светодиод

        // запоминаем текущее состояние пина кнопки, как предыдущее

        if (previous == true && current == false)
        {
            led = !led;
            set_led(led);
            
        }

        previous = current;
        sleep_ms(10);

        int command = getchar_timeout_us(0);

        if (command == PICO_ERROR_TIMEOUT)
        {
            continue;
        }

        led = handle_command(command, led);
    }
}
