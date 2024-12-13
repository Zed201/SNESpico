#pragma once
#include <stdint.h>
#include "utils.h"

class SRam
{
private:
public:
    SRam();
    ~SRam();

    uint8_t ReadByte(uint24_t addr);
    uint16_t ReadWord(uint24_t addr);

    void WriteByte(uint24_t addr, uint8_t byte);
    void WriteWord(uint24_t addr, uint16_t word);
};