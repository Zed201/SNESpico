#pragma once

#include <stdint.h>

class SDCard
{
private:
    static uint64_t s_CurrentAddr;

    static uint8_t GenCRC7(uint8_t cmd, uint32_t arg);

    static bool CheckCRC16(const uint8_t *data, uint16_t CRC16);

    static uint8_t SendCommand(uint8_t cmd, uint32_t arg);
public:
    static void Init();
    static void Shutdown();

    static uint64_t Read(const uint8_t *dst, uint64_t len);
    static uint64_t Write(const uint8_t *src, uint64_t len);
    static void SetAddr(uint64_t addr) { s_CurrentAddr = addr }
};