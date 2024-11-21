#pragma once

#include <bus.h>
#include <stdint.h>

class CPU
{
private:
    union
    {
        uint16_t C;
        struct
        {
            uint8_t A;
            uint8_t B;
        };
    } Accumulator;

    uint8_t DBR;
    uint8_t PBR;
    uint16_t DR;
    uint16_t PC, SP;
    uint16_t X, Y;

    struct 
    {
        uint8_t N : 1;
        uint8_t V : 1;
        uint8_t M : 1;
        uint8_t X : 1;
        uint8_t D : 1;
        uint8_t I : 1;
        uint8_t Z : 1;
        uint8_t C : 1;
        uint8_t E : 1;
        uint8_t B : 1;
    } Status;

    Bus *m_Bus;

public:
    CPU(Bus *bus);
};