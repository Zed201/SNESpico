#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"

#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define RS_PIN 10
#define EN_PIN 11

uint32_t millis()
{
    return to_ms_since_boot(get_absolute_time());
}

void init()
{
    gpio_init(D0);
    gpio_set_dir(D0, GPIO_OUT);

    gpio_init(D1);
    gpio_set_dir(D1, GPIO_OUT);

    gpio_init(D2);
    gpio_set_dir(D2, GPIO_OUT);

    gpio_init(D3);
    gpio_set_dir(D3, GPIO_OUT);

    gpio_init(D4);
    gpio_set_dir(D4, GPIO_OUT);

    gpio_init(D5);
    gpio_set_dir(D5, GPIO_OUT);

    gpio_init(D6);
    gpio_set_dir(D6, GPIO_OUT);

    gpio_init(D7);
    gpio_set_dir(D7, GPIO_OUT);

    gpio_init(RS_PIN);
    gpio_set_dir(RS_PIN, GPIO_OUT);

    gpio_init(EN_PIN);
    gpio_set_dir(EN_PIN, GPIO_OUT);
}

void send_command(uint8_t command)
{
    gpio_put(EN_PIN, true);
    gpio_put(RS_PIN, false);

    gpio_put(D0, command & 1);
    gpio_put(D1, command & 2);
    gpio_put(D2, command & 4);
    gpio_put(D3, command & 8);
    gpio_put(D4, command & 0x10);
    gpio_put(D5, command & 0x20);
    gpio_put(D6, command & 0x40);
    gpio_put(D7, command & 0x80);

    gpio_put(EN_PIN, false);
    sleep_ms(60);
}

void send_character(uint8_t character)
{
    gpio_put(EN_PIN, true);
    gpio_put(RS_PIN, true);

    gpio_put(D0, character & 1);
    gpio_put(D1, character & 2);
    gpio_put(D2, character & 4);
    gpio_put(D3, character & 8);
    gpio_put(D4, character & 0x10);
    gpio_put(D5, character & 0x20);
    gpio_put(D6, character & 0x40);
    gpio_put(D7, character & 0x80);

    gpio_put(EN_PIN, false);
    gpio_put(RS_PIN, true);
    sleep_ms(60);
}

int main() 
{
    stdio_init_all();

    init();

    /*
    gpio_init(LED_PIN);
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    pwm_set_gpio_level(LED_PIN, 0);
    uint32_t sliceNum = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_enabled(sliceNum, true);

    adc_init();
    adc_gpio_init(POT_PIN);
    adc_select_input(ADC_NUM);
    */

   const uint32_t size = 12;
   char str[size] = "Hello World";

    send_command(0x0f);
    send_command(0x01);

    for(uint32_t i = 0; i < size - 1; i++)
        send_character(str[i]);

    /*
    gpio_put(RS_PIN, true);

    sleep_ms(500);

    gpio_put(D0, false);
    gpio_put(D1, false);
    gpio_put(D2, false);
    gpio_put(D3, true);
    gpio_put(D4, false);
    gpio_put(D5, false);
    gpio_put(D6, true);
    gpio_put(D7, false);

    sleep_ms(500);

    gpio_put(EN_PIN, false);
    gpio_put(RS_PIN, true);
    */


    while(true)
    {
        // Do nothing
    }

    return 0;
}