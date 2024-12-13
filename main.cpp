#include <stdio.h>
#include "pico/stdlib.h"

#define CLK 28
#define SHIFT_LOAD 0
#define RECEIVER 1

#define UPDATE_RATE 50.f

uint32_t millis()
{
    return to_ms_since_boot(get_absolute_time());
}

int main() 
{
    stdio_init_all();

    gpio_init(CLK);
    gpio_set_dir(CLK, GPIO_OUT);
    gpio_put(CLK, false);

    gpio_init(SHIFT_LOAD);
    gpio_set_dir(SHIFT_LOAD, GPIO_OUT);
    gpio_put(SHIFT_LOAD, true);  

    gpio_init(RECEIVER);
    gpio_set_dir(RECEIVER, GPIO_IN);

    while(true)
    {
        sleep_ms(1000 / UPDATE_RATE);

        gpio_put(SHIFT_LOAD, false);
        gpio_put(CLK, true);


        gpio_put(SHIFT_LOAD, true);
        gpio_put(CLK, false);

        uint16_t v = 0;
        char str[17] = {0};
        for(uint8_t i = 0; i < 16; i++)
        {
            gpio_put(CLK, true);
            bool getV = gpio_get(RECEIVER);
            v += getV << i;
            str[16 - i - 1] = getV + '0';
            gpio_put(CLK, false);
        }

        printf("%s\n", str);
    }

    return 0;
}