#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include <string.h>

#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define RS_PIN 10
#define EN_PIN 11
#define BTN 0

#define TX 1
#define BPS 5

uint32_t millis()
{
    return to_ms_since_boot(get_absolute_time());
}

void init()
{
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

    gpio_put(D4, command & 0x10);
    gpio_put(D5, command & 0x20);
    gpio_put(D6, command & 0x40);
    gpio_put(D7, command & 0x80);

    gpio_put(EN_PIN, false);
    gpio_put(RS_PIN, false);

    sleep_ms(5);

    gpio_put(EN_PIN, true);
    gpio_put(RS_PIN, false);

    gpio_put(D4, command & 0x01);
    gpio_put(D5, command & 0x02);
    gpio_put(D6, command & 0x04);
    gpio_put(D7, command & 0x08);

    gpio_put(EN_PIN, false);
    gpio_put(RS_PIN, false);

    sleep_ms(5);
}

void send_character(uint8_t character)
{
    gpio_put(EN_PIN, true);
    gpio_put(RS_PIN, true);

    gpio_put(D4, character & 0x10);
    gpio_put(D5, character & 0x20);
    gpio_put(D6, character & 0x40);
    gpio_put(D7, character & 0x80);

    gpio_put(EN_PIN, false);
    gpio_put(RS_PIN, true);

    sleep_ms(5);

    gpio_put(EN_PIN, true);
    gpio_put(RS_PIN, true);

    gpio_put(D4, character & 0x01);
    gpio_put(D5, character & 0x02);
    gpio_put(D6, character & 0x04);
    gpio_put(D7, character & 0x08);

    gpio_put(EN_PIN, false);
    gpio_put(RS_PIN, true);

    sleep_ms(5);
}

void send_string(const char *str)
{
    uint32_t size = strlen(str);

    for (uint32_t i = 0; i < size; i++)
        send_character(str[i]);
}

bool btnStateOld = false, pressed = false;
uint32_t tDown, tUp;

void btnIrq(uint gpio, uint32_t eventMask)
{
    bool state = gpio_get(BTN);

    if (!state) tDown = millis();
    else tUp = millis();

    if (btnStateOld && !state && int(tDown - tUp) > 25)
        pressed = true;

    btnStateOld = state;
}

int main() 
{
    stdio_init_all();

    init();

    uint32_t currentChar = 0;

    gpio_put(EN_PIN, true);
    gpio_put(RS_PIN, false);

    gpio_put(D4, false);
    gpio_put(D5, true);
    gpio_put(D6, false);
    gpio_put(D7, false);

    gpio_put(EN_PIN, false);
    gpio_put(RS_PIN, false);

    sleep_ms(10);

    send_command(0x0E);
    send_command(0x01);

    const char str[] = "Lab. Hardware";
    send_string(str);

    send_command(0xC0);

    for (uint8_t i = 0; i < 8; i++)
        send_character((currentChar >> (7 - i)) & 1 ? '1' : '0');

    send_command(0x02);

    gpio_init(BTN);
    gpio_set_dir(BTN, GPIO_IN);
    gpio_pull_up(BTN);
    gpio_set_irq_enabled_with_callback(BTN, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, btnIrq);

    gpio_init(TX);
    gpio_set_dir(TX, GPIO_OUT);

    while(true)
    {
        if (pressed)
        {
            // Bit start
            gpio_put(TX, true);
            sleep_ms(1000 / BPS);

            currentChar = (currentChar + 1) % strlen(str);

            send_command(0xC0);

            bool bit = false;
            for (uint8_t i = 0; i < 8; i++)
            {
                bit = (str[currentChar] >> (7 - i)) & 1;
                send_character(bit ? '1' : '0');
                gpio_put(TX, bit);
                sleep_ms(1000 / BPS);
            }

            send_command(0x02);

            for (uint8_t i = 0; i < currentChar; i++)
                send_command(0x14);

            pressed = false;

            gpio_put(TX, false);
        }

    }

    return 0;
}