#pragma once
#include <stdint.h>
#include "utils.h"
#include "filesystem/filehandle.h"

#define ROM_PAGE_SIZE 16 * 1024 // 16KB de página

enum class RomType: uint8_t 
{
    LoRom,
    HiRom,
    ExHiRom,
    Unknow
};

class Rom
{
private:
    FileHandle m_File;
    uint8_t m_Stream[ROM_PAGE_SIZE];
    uint24_t m_BaseAddr = 0;
    uint8_t m_PagesCount = 0;
public:
    RomType Load(const char* filename);

    uint8_t* LoadPage(uint24_t addr);
    inline uint8_t* GetPage(uint24_t addr) 
    {
        if (addr < m_BaseAddr || addr >= (m_BaseAddr + ROM_PAGE_SIZE))
            LoadPage(addr);

        return m_Stream;
    }
};