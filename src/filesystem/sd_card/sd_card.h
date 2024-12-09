#pragma once

#include <stdint.h>

// --   Referências   --
// https://k1.spdns.de/Develop/Projects/pico/atto-filesystem/project/SD-Card/Info/Physical%20Layer%20Simplified%20Specification%20v8.00.pdf
// https://chlazza.nfshost.com/sdcardinfo.html
// https://components101.com/sites/default/files/component_datasheet/Micro%20SD%20Card%20Datasheet.pdf

class SDCard
{
private:
    static uint64_t s_CurrentAddr;

    static uint8_t SendCommand(uint8_t cmd, uint32_t arg);
public:
    static void Init();
    static void Shutdown();

    static uint64_t Read(uint8_t *dst, uint64_t len);
    static uint64_t Write(const uint8_t *src, uint64_t len);
    static void SetAddr(uint64_t addr) { s_CurrentAddr = addr; }
};