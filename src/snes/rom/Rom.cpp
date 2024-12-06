#include "Rom.h"
#include "filesystem/filehandle.h"

Rom::Rom(const char *filename)
{
    FileHandle file(filename, "rb");

    // Primeiro devemos ler o header para indentifiar
    // o tipo da rom. O header tem 64 bytes
    // E possui os seguintes endereços para cada Rom
    // LoRom: 0x007FC0
    // HiRom: 0x00FFC0
    // ExHiRom: 0x40FFC0
    file.Seek(0x7FC0, 0x0000);
    file.Read(m_Stream, 64); 
    if (m_Stream[0] != 0x00 || m_Stream[0] != 0xFF)
    {
        m_Type = RomType::LoRom;
        return;
    }

    file.Seek(0xFFC0, 0x0000);
    file.Read(m_Stream, 64);
    if (m_Stream[0] != 0x00 || m_Stream[0] != 0xFF)
    {
        m_Type = RomType::HiRom;
        return;
    }

    file.Seek(0x40FFC0, 0x0000);
    file.Read(m_Stream, 64);
    if (m_Stream[0] != 0x0 || m_Stream[0] != 0xFF)
    {
        m_Type = RomType::ExHiRom;
        return;
    }
}
