#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include <string.h>

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

#define COMMAND 1
#define CHARACTER (1 << 1)
#define STRING (1 << 2)

mutex_t mtx;

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

void lcd_interrupt_handler()
{
    mutex_enter_blocking(&mtx);
    uint8_t type = multicore_fifo_pop_blocking();

    if (type == STRING)
    {
        while (multicore_fifo_rvalid())
        {
            uint8_t data = multicore_fifo_pop_blocking();

            gpio_put(EN_PIN, true);
            gpio_put(RS_PIN, true);

            gpio_put(D0, data & 1);
            gpio_put(D1, data & 2);
            gpio_put(D2, data & 4);
            gpio_put(D3, data & 8);
            gpio_put(D4, data & 0x10);
            gpio_put(D5, data & 0x20);
            gpio_put(D6, data & 0x40);
            gpio_put(D7, data & 0x80);

            gpio_put(EN_PIN, false);
            gpio_put(RS_PIN, true);
            busy_wait_ms(5);
        }
    }
    else if (type == COMMAND)
    {
        uint8_t data = multicore_fifo_pop_blocking();

        gpio_put(EN_PIN, true);
        gpio_put(RS_PIN, false);

        gpio_put(D0, data & 1);
        gpio_put(D1, data & 2);
        gpio_put(D2, data & 4);
        gpio_put(D3, data & 8);
        gpio_put(D4, data & 0x10);
        gpio_put(D5, data & 0x20);
        gpio_put(D6, data & 0x40);
        gpio_put(D7, data & 0x80);

        gpio_put(EN_PIN, false);
        busy_wait_ms(5);
    }
    else if (type == CHARACTER)
    {
        uint8_t data = multicore_fifo_pop_blocking();

        gpio_put(EN_PIN, true);
        gpio_put(RS_PIN, true);

        gpio_put(D0, data & 1);
        gpio_put(D1, data & 2);
        gpio_put(D2, data & 4);
        gpio_put(D3, data & 8);
        gpio_put(D4, data & 0x10);
        gpio_put(D5, data & 0x20);
        gpio_put(D6, data & 0x40);
        gpio_put(D7, data & 0x80);

        gpio_put(EN_PIN, false);
        gpio_put(RS_PIN, true);
        busy_wait_ms(5);
    }
    
    mutex_exit(&mtx);
    multicore_fifo_clear_irq();
}

void lcd_core1()
{
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_IRQ_PROC1, lcd_interrupt_handler);
    irq_set_enabled(SIO_IRQ_PROC1, true);

    while (true)
    {
        tight_loop_contents();
    }
}

void send_command(uint8_t command)
{
    mutex_enter_blocking(&mtx);

    multicore_fifo_push_blocking(COMMAND);
    multicore_fifo_push_blocking(command);

    mutex_exit(&mtx);
}

void send_character(uint8_t character)
{
    mutex_enter_blocking(&mtx);

    multicore_fifo_push_blocking(CHARACTER);
    multicore_fifo_push_blocking(character);

    mutex_exit(&mtx);
}

void send_string(const char *str)
{
    uint32_t size = strlen(str);

    uint32_t i = 0;
    while (i < size)
    {
        mutex_enter_blocking(&mtx);
    
        multicore_fifo_push_blocking(STRING);

        for (uint32_t j = 0; j < 4 && i < size; j++, i++)
            multicore_fifo_push_blocking(str[i]);
    
        mutex_exit(&mtx);
    }
}

int main() 
{
    stdio_init_all();

    init();

    mutex_init(&mtx);

    multicore_launch_core1(lcd_core1);

    const uint32_t size = 12;
    char str[size] = "Hello World";

    sleep_ms(10000);

    send_command(0x0f);
    send_command(0x01);
    send_string(str);

    while(true)
    {
    }

    return 0;
}