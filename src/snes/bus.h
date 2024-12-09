#pragma once

#include <stdint.h>

#include "cpu/Ram.h"
#include "rom/Rom.h"

class Bus
{
private:
    Ram *m_Ram;
    Rom *m_Rom;
public:
    Bus(Ram* ram, Rom *rom);
    ~Bus();

    void SetMapMode(uint8_t mapMode);

    uint8_t ReadByte(uint32_t addr);
    uint16_t ReadWord(uint32_t addr);
    void WriteByte(uint32_t addr, uint8_t byte);
    void WriteWord(uint32_t addr, uint16_t word);
};