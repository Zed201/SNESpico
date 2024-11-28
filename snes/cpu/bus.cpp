#include "bus.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

Bus::Bus()
{
    memset(m_Memory, 0, RAM_MAX_MEMORY);
    memset(rom_Memory, 0, ROM_MAX_MEMORY);
}

Bus::~Bus()
{
}

uint8_t Bus::__Read_Byte(uint32_t addr, uint8_t* mem)
{
    return mem[addr];
}

uint16_t Bus::__Read_Word(uint32_t addr, uint8_t* mem)
{
                        // byteH      byteL
    return BYTES_TO_WORD(mem[addr + 1], mem[addr]);
}

void Bus::__Set_Byte(uint32_t addr, uint8_t byte, uint8_t* mem)
{
    mem[addr] = byte;
}

void Bus::__Set_Word(uint32_t addr, uint16_t word, uint8_t* mem)
{
    mem[addr] = word & LOW_BYTES_MASK; // pode fazer com um static_cast também
    mem[addr + 1] = word >> 8;
}

uint8_t Bus::Ram_ReadByte(uint32_t addr)
{
    return __Read_Byte(addr, m_Memory);
}

uint16_t Bus::Ram_ReadWord(uint32_t addr)
{
    return __Read_Word(addr, m_Memory);
}

void Bus::Ram_SetByte(uint32_t addr, uint8_t byte)
{
    __Set_Byte(addr, byte, m_Memory);
}

void Bus::Ram_SetWord(uint32_t addr, uint16_t word)
{
    __Set_Word(addr, word, m_Memory);
}

void Bus::Ram_Reset()
{
    memset(m_Memory, 0, RAM_MAX_MEMORY);
}

// TODO: refazer depois para adicionar a logica dos bancos de memória ou dar um jeito de transformar em stream
bool Bus::ReadRom(char* file_name)
{
    FILE *f = fopen(file_name, "rb");
    if (!f){
        printf("Erro ao abrir o arquivo\n");
        return false;
    }
    fseek(f, 0, SEEK_END);
    int64_t f_Size = ftell(f);
    rewind(f);
    
    if (f_Size < 0) {
        printf("Erro ao obter tamanho do arquivo\n");
        fclose(f);
        return false;
    }

    // Ler o conteúdo do arquivo
    rom_Size = fread(rom_Memory, 1, f_Size, f);
    if (rom_Size != f_Size) {
        perror("Erro ao ler o arquivo");
        memset(rom_Memory, 0, ROM_MAX_MEMORY);
        rom_Size = 0;
        fclose(f);
        return false;
    }
    return true;
}

uint8_t Bus::Rom_ReadByte(uint32_t addr)
{
    return __Read_Byte(addr, rom_Memory);
}
uint16_t Bus::Rom_ReadWord(uint32_t addr)
{
    return __Read_Word(addr, rom_Memory);
}

void Bus::Rom_SetByte(uint32_t addr, uint8_t byte)
{
    __Set_Byte(addr, byte, rom_Memory);
}
void Bus::Rom_SetWord(uint32_t addr, uint16_t word)
{
    __Set_Word(addr, word, rom_Memory);
}