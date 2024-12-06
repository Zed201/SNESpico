#pragma once
#include <stdint.h>

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
    unsigned char m_Stream[16 * 1024]; // 16KB de página
    RomType m_Type;
public:
    Rom(const char *filename);

    inline unsigned char* GetPage() { return m_Stream; }
    inline RomType GetType() { return m_Type; }
};