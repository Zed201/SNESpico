#include "sd_card.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include "hardware/spi.h"
//#include <string.h>

#define SPI_PORT spi0
#define SPI_BAUD 1000000

#define SCK 2
#define TX 3
#define RX 4
#define CSn 5 // Seletor do chip se 1 não comunica com o SD Card

#define BLOCK_LEN 512

uint64_t SDCard::s_CurrentAddr = 0;

///////////////////////////////////
//      - RESPONSE FORMATS -
//
//      - R1: 8 bits
//          bit[0] = in idle state
//          bit[1] = erase reset
//          bit[2] = illegal command
//          bit[3] = com crc error
//          bit[4] = erase sequence error
//          bit[5] = address error
//          bit[6] = parameter error
//          bit[7] = always zero
//
///////////////////////////////////
uint8_t SDCard::SendCommand(uint8_t cmd, uint32_t arg)
{
    uint8_t response = 0xFF; // Resposta inicial (invalida)

    gpio_put(CSn, 0); // Ativa o cartão (CS = 0)

    // Envia o comando e argumento
    uint8_t src = (0x4F & cmd);
    spi_write_blocking(SPI_PORT, &src, 1);
    spi_write_blocking(SPI_PORT, (uint8_t *)&arg, 4);
    
    uint8_t crc = 0x00;
    spi_write_blocking(SPI_PORT, &crc, 1);
    
    // Recebe a resposta do cartão
    spi_read_blocking(SPI_PORT, 0xFF, &response, 1);

    gpio_put(CSn, 1); // Desativa o Chip Select (CS = 1)

    return response;
}

void SDCard::Init()
{
    spi_init(SPI_PORT, SPI_BAUD);

    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(TX, GPIO_FUNC_SPI);
    gpio_set_function(RX, GPIO_FUNC_SPI);
    
    gpio_init(CSn);
    gpio_set_dir(CSn, GPIO_OUT);
    gpio_put(CSn, true);

    // Resetando SD Card e entrando em modo SPI
    uint8_t response = 0xFF; // Resposta inicial (invalida)

    gpio_put(CSn, 0); // Ativa o cartão (CS = 0)

    // Envia o comando e argumento
    uint8_t cmd0 = (0x4F & 0x00);
    uint32_t arg = 0x00;
    uint8_t crc7 = 0x95;
    spi_write_blocking(SPI_PORT, &cmd0, 1);
    spi_write_blocking(SPI_PORT, reinterpret_cast<uint8_t*>(&arg), 4);
    spi_write_blocking(SPI_PORT, &crc7, 1);
    
    // Recebe a resposta do cartão
    spi_read_blocking(SPI_PORT, 0xFF, &response, 1);

    gpio_put(CSn, 1); // Desativa o Chip Select (CS = 1)

    if (response != 0x01)
    {
        // Erro ao tentar resetar e entrar no modo SPI do SD card
        return;
    }
}

void SDCard::Shutdown()
{
    gpio_deinit(CSn);

    spi_deinit(SPI_PORT);
}

uint64_t SDCard::Read(uint8_t *dst, uint64_t len)
{
    uint64_t bytesReaded = 0;
    // Envia CMD18 (Ler múltiplos blocos)
    uint8_t response = SendCommand(0x12, s_CurrentAddr); // CMD18
    if (response != 0x00) 
    { 
        // Erro ao tentar ler do endereço atual
        return bytesReaded;
    }

    uint16_t CRC16 = 0x0000;
    while (len != 0)
    {
        spi_read_blocking(SPI_PORT, 0xFF, dst, len >= BLOCK_LEN ? BLOCK_LEN : len);
        spi_read_blocking(SPI_PORT, 0xFF, reinterpret_cast<uint8_t*>(&CRC16), 2);

        if (len >= BLOCK_LEN)
        {
            dst += BLOCK_LEN;
            bytesReaded += BLOCK_LEN;
            len -= BLOCK_LEN;
        }
        else
        {
            dst += len;
            bytesReaded += len;
            len = 0;
        }
    }

    response = SendCommand(0x0C, 0); // CMD12 (Stop transmission)
    if (response != 0x00)
    {
        // Erro ao tentar parar transmissão de dados
    }

    return bytesReaded;
}

uint64_t SDCard::Write(const uint8_t *src, uint64_t len)
{
    uint64_t bytesWritten = 0;
    
    // Envia CMD25 (Escrever múltiplos blocos)
    uint8_t response = SendCommand(0x19, s_CurrentAddr); // CMD18
    if (response != 0x00) 
    { 
        // Erro ao tentar escrever no endereço atual
        return bytesWritten;
    }

    uint8_t startToken = 0xFC, stopToken = 0xFD;
    while (len != 0)
    {
        spi_write_blocking(SPI_PORT, &startToken, 1);

        if (len >= BLOCK_LEN)
        {
            spi_write_blocking(SPI_PORT, src, BLOCK_LEN);
            src += BLOCK_LEN;
            bytesWritten += BLOCK_LEN;
            len -= BLOCK_LEN;
        }
        else
        {
            uint8_t padding[BLOCK_LEN] = {0};
            memcpy(padding, src, len);
            spi_write_blocking(SPI_PORT, padding, BLOCK_LEN);
            src += len;
            bytesWritten += len;
            len = 0;
        }

        while(spi_is_busy(SPI_PORT))
            sleep_us(100); // Espera 100 microsegundos
    }

    spi_write_blocking(SPI_PORT, &stopToken, 1);

    return bytesWritten;
}
