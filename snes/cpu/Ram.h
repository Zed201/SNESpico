#pragma once

#include <stdint.h>

#define KB (1 << 10)
#define RAM_MAX_MEMORY 128 * KB

#define BYTES_TO_WORD(byteH, byteL) (byteH << 8) | byteL

// mascara para os 8 bits menos e menos significativos de 16 bits
#define LOW_BYTES_MASK 0x00FF
#define HIGH_BYTES_MASK 0xFF00

class Ram
{
private:
    uint8_t m_Memory[RAM_MAX_MEMORY];
public:
    Ram();
    ~Ram();

    uint8_t ReadByte(uint32_t addr);
    uint16_t ReadWord(uint32_t addr);
    void WriteByte(uint32_t addr, uint8_t byte);
    void WriteWord(uint32_t addr, uint16_t word);
};