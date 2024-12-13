#include "bus.h"
#include <bits/stl_pair.h>

std::pair<uint32_t, uint8_t> Bus::GetRealAddr(uint32_t addr)
{
    uint8_t bank = (addr >> 16);

    // RAM 0x7E0000 - 0x7FFFFF
    // Mirrored 0x7E0000 - 0X7E1FFF to banks 00-3F, 80-BF
    if (bank == 0x7E || bank == 0x7F)
        return std::pair(addr - 0x7E0000, 0);
    else if (bank >= 0x00 && bank <= 0x3F)
        return std::pair(addr - (bank << 16), 0);
}

Bus::Bus(Ram *ram, Rom *rom, SRam* sram) : m_Ram(ram), m_Rom(rom), m_SRam(sram)
{
}

Bus::~Bus()
{
}

void Bus::SetMapMode(RomType mapMode)
{
    switch (mapMode)
    {
    case RomType::LoRom:
        m_RomBnk = 0x80;
        m_RomMirrorBnk = 0x00;
        m_SramBnk = 0xF0;
        m_SramMirrorBnk = 0x70;
        break;
    case RomType::HiRom:
        break;
    default:
        break;
    }
}

uint8_t Bus::ReadByte(uint32_t addr)
{
    std::pair<uint32_t, uint8_t> result = GetRealAddr(addr);

    switch (result.second)
    {
    case 0: // Ram
        return m_Ram->ReadByte(result.first);
    case 1: // Rom
        return m_Rom->GetPage(result.first)[result.first];
    case 2: // SRAM
        return m_SRam->ReadByte(result.first);
    default: // Endereço não corresponde a nada do modo de mapeamento
        return 0;
    }
    
}

uint16_t Bus::ReadWord(uint32_t addr)
{
    std::pair<uint32_t, uint8_t> result = GetRealAddr(addr);

    switch (result.second)
    {
    case 0: // Ram
        return m_Ram->ReadWord(result.first);
    case 1: // Rom
    {
        uint8_t* page = m_Rom->GetPage(result.first);
        return (page[result.first + 1] << 8) | page[result.first];
    }
    case 2: // SRAM
        return m_SRam->ReadWord(result.first);
    default: // Endereço não corresponde a nada do modo de mapeamento
        return 0;
    }

    return 0;
}

void Bus::WriteByte(uint32_t addr, uint8_t byte)
{
    std::pair<uint32_t, uint8_t> result = GetRealAddr(addr);

    switch (result.second)
    {
    case 0: // Ram
        m_Ram->WriteByte(result.first, byte);
        break;
    case 1: // Rom
        // Erro, pois nao eh possivel escrever na memoria rom
        // ROM (Read-Only Memory)
        break;
    case 2: // SRAM
        m_SRam->WriteByte(result.first, byte);
        break;    
    default:
        break;
    }
}

void Bus::WriteWord(uint32_t addr, uint16_t word)
{
    std::pair<uint32_t, uint8_t> result = GetRealAddr(addr);

    switch (result.second)
    {
    case 0: // Ram
        m_Ram->WriteWord(result.first, word);
        break;
    case 1: // Rom
        // Erro, pois nao eh possivel escrever na memoria rom
        // ROM (Read-Only Memory)
        break;
    case 2: // SRAM
        m_SRam->WriteWord(result.first, word);
        break;    
    default:
        break;
    }
}
