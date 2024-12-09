#include "Rom.h"
#include "filesystem/filehandle.h"

RomType Rom::Load(const char *filename)
{
    m_File.Open(filename, "rb");

    // Primeiro devemos ler o header para indentifiar
    // o tipo da rom. O header tem 64 bytes
    // E possui os seguintes endereços para cada Rom
    // LoRom: 0x007FC0
    // HiRom: 0x00FFC0
    // ExHiRom: 0x40FFC0
    m_File.Seek(0x7FC0, 0x0000);
    m_File.Read(m_Stream, 64); 
    if (m_Stream[0] != 0x00 || m_Stream[0] != 0xFF)
        return RomType::LoRom;

    m_File.Seek(0xFFC0, 0x0000);
    m_File.Read(m_Stream, 64);
    if (m_Stream[0] != 0x00 || m_Stream[0] != 0xFF)
        return RomType::HiRom;

    m_File.Seek(0x40FFC0, 0x0000);
    m_File.Read(m_Stream, 64);
    if (m_Stream[0] != 0x0 || m_Stream[0] != 0xFF)
        return RomType::ExHiRom;
}

uint8_t *Rom::LoadPage(uint64_t addr)
{
    uint64_t pageIndex = addr / ROM_PAGE_SIZE;
    m_File.Seek(pageIndex * ROM_PAGE_SIZE, 0x0000);
    m_File.Read(m_Stream, ROM_PAGE_SIZE);
    return m_Stream;
}
