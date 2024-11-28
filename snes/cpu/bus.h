#pragma once

#include <stdint.h>

#define KB (1 << 10)
#define RAM_MAX_MEMORY 128 * KB
#define ROM_MAX_MEMORY 600 * KB // por enquanto temporario o tamanho, so para teste

#define BYTES_TO_WORD(byteH, byteL) (byteH << 8) | byteL

// mascara para os 8 bits menos e menos significativos de 16 bits
#define LOW_BYTES_MASK 0x00FF
#define HIGH_BYTES_MASK 0xFF00

class Bus
{
private:
    uint8_t m_Memory[RAM_MAX_MEMORY];
    uint8_t rom_Memory[ROM_MAX_MEMORY];


    // fazer genericos pois o codigo da ram e do rom para deslocamente vai ser basicamente o mesmo
    uint8_t __Read_Byte(uint32_t addr, uint8_t* mem);
    uint16_t __Read_Word(uint32_t addr, uint8_t* mem);
    void __Set_Byte(uint32_t addr, uint8_t byte, uint8_t* mem);
    void __Set_Word(uint32_t addr, uint16_t word, uint8_t* mem);

    /* 
        TODO: Fazer lógica de paginas e dos bancos de memória,
        pois a memória do rasberry pi pico é de 264kB e tem 2MB de flash
     */

public:
    // so para teste
    uint64_t rom_Size = 0;
    Bus();
    ~Bus();

    uint8_t Ram_ReadByte(uint32_t addr);
    uint16_t Ram_ReadWord(uint32_t addr);

    void Ram_SetByte(uint32_t addr, uint8_t byte);
    void Ram_SetWord(uint32_t addr, uint16_t word);

    void Ram_Reset();

    // TODO: identificar os tipos de rom, com base nos endereços
    bool ReadRom(char * file_name);

    uint8_t Rom_ReadByte(uint32_t addr);
    uint16_t Rom_ReadWord(uint32_t addr);

    void Rom_SetByte(uint32_t addr, uint8_t byte);
    void Rom_SetWord(uint32_t addr, uint16_t word);

};