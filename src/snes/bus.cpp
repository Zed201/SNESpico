#include "bus.h"

void Bus::SetMapMode(uint8_t mapMode)
{
}

uint8_t Bus::ReadByte(uint32_t addr)
{
    std::pair<uint32_t, uint8_t> result = GetRealAddr(addr);

    switch (result.second)
    {
    case 0: // Ram
        return m_Ram->ReadByte(result.first);
    case 1: // Rom
        return m_Rom->InRange(result.first) ? m_Rom->GetPage()[result.first] : m_Rom->LoadPage(result.first)[result.first];
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
        uint8_t* page = m_Rom->InRange(result.first) ? m_Rom->GetPage() : m_Rom->LoadPage(result.first);
        return (page[result.first + 1] << 8) | page[result.first];
    }
    default: // Endereço não corresponde a nada do modo de mapeamento
        return 0;
    }

    return 0;
}
