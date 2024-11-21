#pragma once

#include <stdint.h>

#define KB (1 << 10)
#define MAX_MEMORY 128 * KB

#define BYTES_TO_WORD(byteH, byteL) (byteH << 8) | byteL

class Bus
{
private:
    uint8_t m_Memory[MAX_MEMORY];
public:
    Bus();
    ~Bus();

    uint8_t ReadByte(uint32_t addr);
    uint16_t ReadWord(uint32_t addr);

    void SetByte(uint32_t addr, uint8_t byte);
    void SetWord(uint32_t addr, uint16_t word);

    void Reset();
};