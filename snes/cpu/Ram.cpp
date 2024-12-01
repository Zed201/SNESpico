#include "Ram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ram::Ram()
{
    memset(m_Memory, 0, RAM_MAX_MEMORY);
}

Ram::~Ram()
{
}

uint8_t Ram::ReadByte(uint32_t addr)
{
    return m_Memory[addr];
}

uint16_t Ram::ReadWord(uint32_t addr)
{
                        // byteH      byteL
    return BYTES_TO_WORD(m_Memory[addr + 1], m_Memory[addr]);
}

void Ram::WriteByte(uint32_t addr, uint8_t byte)
{
    m_Memory[addr] = byte;
}

void Ram::WriteWord(uint32_t addr, uint16_t word)
{
    m_Memory[addr] = word & LOW_BYTES_MASK; // pode fazer com um static_cast também
    m_Memory[addr + 1] = word >> 8;
}
