#pragma once

#include <stdint.h>

class FAT32
{
private:
    uint8_t* m_BlockBuffer; // Temporary buffer for sector I/O

    uint8_t m_SectorsPerCluster;
    uint8_t m_NumFATs;
    uint8_t m_RootDirSectors;
    uint16_t m_ReservedSectorsCount;
    uint16_t m_BytesPerSector;
    uint32_t m_FatSize;
    uint32_t m_RootCluster;
    uint32_t m_DataStartSector;
    uint32_t m_DataSector;
    uint32_t m_ClusterStartSector;
    uint32_t m_ClusterCount;
    uint32_t m_TotalClusters;
    
    bool LoadBootSector();

public:
    void Init(); // Initialize by reading the boot sector
    void ShutDown();

    uint32_t AllocateCluster();
    uint32_t GetNextCluster(uint32_t currentCluster);
    void FreeClusterChain(uint32_t startCluster);

    uint32_t ClusterToSector(uint32_t cluster) const;
    bool ReadCluster(uint32_t cluster, uint8_t* buffer);
    bool WriteCluster(uint32_t cluster, const uint8_t* buffer);
};