#pragma once

#include <stdint.h>

#include "cpu/Ram.h"
#include "rom/Rom.h"
#include "rom/SRam.h"

class Bus
{
private:
    Ram *m_Ram;
    Rom *m_Rom;
    SRam *m_SRam;

    uint8_t m_RomBnk, m_RomMirrorBnk, m_SramBnk, m_SramMirrorBnk;

    std::pair<uint32_t, uint8_t> GetRealAddr(uint32_t addr);
public:
    Bus(Ram* ram, Rom *rom, SRam *sram);
    ~Bus();

    void SetMapMode(RomType mapMode);

    uint8_t ReadByte(uint32_t addr);
    uint16_t ReadWord(uint32_t addr);
    void WriteByte(uint32_t addr, uint8_t byte);
    void WriteWord(uint32_t addr, uint16_t word);
};