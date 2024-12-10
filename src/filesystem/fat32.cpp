#include "fat32.h"
#include "sd_card/sd_card.h"

void FAT32::Init()
{
    SDCard::Init();
    if (!LoadBootSector())
        return;

    SDCard::Read(11, reinterpret_cast<uint8_t*>(&m_BytesPerSector), 2);    
    SDCard::Read(13, reinterpret_cast<uint8_t*>(&m_SectorsPerCluster), 1);
    SDCard::Read(14, reinterpret_cast<uint8_t*>(&m_ReservedSectorsCount), 2);
    SDCard::Read(16, reinterpret_cast<uint8_t*>(&m_NumFATs), 1);
    SDCard::Read(32, reinterpret_cast<uint8_t*>(&m_TotalClusters), 4);
    SDCard::Read(36, reinterpret_cast<uint8_t*>(&m_FatSize), 4);
    SDCard::Read(44, reinterpret_cast<uint8_t*>(&m_RootCluster), 4);

    m_RootDirSectors = (m_BytesPerSector - 1) / m_BytesPerSector;
    m_DataStartSector = m_ReservedSectorsCount + (m_NumFATs * m_FatSize) + m_RootDirSectors;
    m_DataSector = m_TotalClusters - (m_ReservedSectorsCount + (m_NumFATs * m_FatSize) + m_RootDirSectors);
    m_ClusterCount = m_DataSector / m_SectorsPerCluster;
}