#pragma once
#include <stdint.h>

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
    uint64_t m_BaseAddr = 0;
    uint8_t m_PagesCount = 0;
public:
    RomType Load(const char* filename);

    uint8_t* LoadPage(uint64_t addr);
    inline uint8_t* GetPage() { return m_Stream; }
    inline bool InRange(uint64_t addr) { return addr >= m_BaseAddr && addr < (m_BaseAddr + ROM_PAGE_SIZE); }
};