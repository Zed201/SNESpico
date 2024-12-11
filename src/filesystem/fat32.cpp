#include "fat32.h"
#include "sd_card/sd_card.h"
#include "string.h"

// Load boot sector and populate FAT32 metadata
bool FAT32::LoadBootSector()
{
    uint8_t buffer[512]; // Buffer for the boot sector
    if (!SDCard::Read(0, buffer, 512))
        return false; // Failed to read boot sector

    memcpy(&m_BytesPerSector, buffer + 11, 2);
    memcpy(&m_SectorsPerCluster, buffer + 13, 1);
    memcpy(&m_ReservedSectorsCount, buffer + 14, 2);
    memcpy(&m_NumFATs, buffer + 16, 1);
    memcpy(&m_FatSize, buffer + 36, 4);
    memcpy(&m_RootCluster, buffer + 44, 4);

    m_DataStartSector = m_ReservedSectorsCount + (m_NumFATs * m_FatSize);
    m_ClusterCount = (m_TotalClusters - m_DataStartSector) / m_SectorsPerCluster;

    return true;
}

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

void FAT32::ShutDown()
{
    if (m_BlockBuffer)
    {
        delete[] m_BlockBuffer;
        m_BlockBuffer = nullptr;
    }

    SDCard::Shutdown();
}

// Allocate a new cluster and update the FAT
uint32_t FAT32::AllocateCluster()
{
    uint32_t cluster = 2; // Start from the first data cluster
    uint8_t buffer[4]; // Buffer to hold FAT32 entries (4 bytes)

    for (; cluster < m_TotalClusters + 2; cluster++)
    {
        uint32_t fatSector = ClusterToSector(cluster) / (m_BytesPerSector / 4);
        uint32_t fatOffset = (cluster % (m_BytesPerSector / 4)) * 4;

        // Read the FAT sector
        if (!SDCard::Read(m_ReservedSectorsCount + fatSector, buffer, 4))
            return 0; // Failed to read FAT

        uint32_t value = *(uint32_t*) buffer & 0x0FFFFFFF;
        if (value == 0) // Free cluster
        {
            value = 0x0FFFFFFF; // Mark as end of chain
            memcpy(buffer, &value, 4);

            if (!SDCard::Write(m_ReservedSectorsCount + fatSector, buffer, 4))
                return 0; // Failed to write FAT

            return cluster;
        }
    }

    return 0; // No free cluster found
}

// Get the next cluster in a chain
uint32_t FAT32::GetNextCluster(uint32_t currentCluster)
{
    uint8_t buffer[4]; // Buffer to hold FAT32 entries (4 bytes)

    uint32_t fatSector = ClusterToSector(currentCluster) / (m_BytesPerSector / 4);
    uint32_t fatOffset = (currentCluster % (m_BytesPerSector / 4)) * 4;

    if (!SDCard::Read(m_ReservedSectorsCount + fatSector, buffer, 4))
        return 0xFFFFFFFF; // Error reading FAT

    return *(uint32_t*) buffer & 0x0FFFFFFF; // Return the next cluster
}

// Free a chain of clusters starting from a given cluster
void FAT32::FreeClusterChain(uint32_t startCluster)
{
    uint32_t currentCluster = startCluster;
    uint8_t buffer[4];

    while (currentCluster >= 2 && currentCluster < m_TotalClusters + 2)
    {
        uint32_t nextCluster = GetNextCluster(currentCluster);

        uint32_t fatSector = ClusterToSector(currentCluster) / (m_BytesPerSector / 4);
        uint32_t fatOffset = (currentCluster % (m_BytesPerSector / 4)) * 4;

        uint32_t value = 0; // Mark as free
        memcpy(buffer, &value, 4);
        SDCard::Write(m_ReservedSectorsCount + fatSector, buffer, 4);

        currentCluster = nextCluster;
    }
}

// Convert a cluster number to the starting sector
uint32_t FAT32::ClusterToSector(uint32_t cluster) const
{
    return m_DataStartSector + ((cluster - 2) * m_SectorsPerCluster);
}

// Read an entire cluster
bool FAT32::ReadCluster(uint32_t cluster, uint8_t *buffer)
{
    uint32_t startSector = ClusterToSector(cluster);
    for (uint8_t i = 0; i < m_SectorsPerCluster; ++i)
    {
        if (!SDCard::Read(startSector + i, buffer + (i * m_BytesPerSector), m_BytesPerSector))
            return false; // Read error
    }

    return true;
}

// Write an entire cluster
bool FAT32::WriteCluster(uint32_t cluster, const uint8_t *buffer)
{
    uint32_t startSector = ClusterToSector(cluster);
    for (uint8_t i = 0; i < m_SectorsPerCluster; ++i)
    {
        if (!SDCard::Write(startSector + i, buffer + (i * m_BytesPerSector), m_BytesPerSector))
        {
            return false; // Write error
        }
    }

    return true;
}