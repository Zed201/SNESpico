#include <bus.h>

#include <memory.h>

Bus::Bus()
{
    memset(m_Memory, 0, RAM_MAX_MEMORY);
}

Bus::~Bus()
{
}

uint8_t Bus::Ram_ReadByte(uint32_t addr)
{
    return m_Memory[addr];
}

uint16_t Bus::Ram_ReadWord(uint32_t addr)
{
    uint8_t byteL = m_Memory[addr];
    uint8_t byteH = m_Memory[addr + 1];
    return BYTES_TO_WORD(byteH, byteL);
}

void Bus::Ram_SetByte(uint32_t addr, uint8_t byte)
{
    m_Memory[addr] = byte;
}

void Bus::Ram_SetWord(uint32_t addr, uint16_t word)
{
    m_Memory[addr] = word & 0x00FF;
    m_Memory[addr + 1] = word >> 8;
}

void Bus::Ram_Reset()
{
    memset(m_Memory, 0, RAM_MAX_MEMORY);
}

uint8_t Bus::__Read_Byte(uint32_t addr, uint8_t mem){}
uint16_t Bus::__Read_Word(uint32_t addr, uint8_t mem){}
void Bus::__Set_Byte(uint32_t addr, uint8_t byte, uint8_t mem){}
void Bus::__Set_Word(uint32_t addr, uint16_t word, uint8_t mem){}

void Bus::ReadRom(char * file_name){}

uint8_t Bus::Rom_ReadByte(uint32_t addr){}
uint16_t Bus::Rom_ReadWord(uint32_t addr){}

void Bus::Rom_SetByte(uint32_t addr, uint8_t byte){}
void Bus::Rom_SetWord(uint32_t addr, uint16_t word){}