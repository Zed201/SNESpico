#include <bus.h>

#include <memory.h>

Bus::Bus()
{
    memset(m_Memory, 0, MAX_MEMORY);
}

Bus::~Bus()
{
}

uint8_t Bus::ReadByte(uint32_t addr)
{
    return m_Memory[addr];
}

uint16_t Bus::ReadWord(uint32_t addr)
{
    uint8_t byteL = m_Memory[addr];
    uint8_t byteH = m_Memory[addr + 1];
    return BYTES_TO_WORD(byteH, byteL);
}

void Bus::SetByte(uint32_t addr, uint8_t byte)
{
    m_Memory[addr] = byte;
}

void Bus::SetWord(uint32_t addr, uint16_t word)
{
    m_Memory[addr] = word & 0x00FF;
    m_Memory[addr + 1] = word >> 8;
}

void Bus::Reset()
{
    memset(m_Memory, 0, MAX_MEMORY);
}
