#pragma once

#include "bus.h"
#include <stdint.h>

enum class AddressingMode { // TODO: Trocar para todos os modos de enderaçamento
    Immediate, // tem 3 tipos de imediate(memory flag, index flag e 8 bit)

    Relative,
    Relative_Long,

    Direct,
    Direct_IndexX,
    Direct_IndexY,
    Direct_Indirect,
    Direct_Indexed_Indirect,
    Direct_Indirect_Indexed,
    Direct_Indirect_Long,
    Direct_Indirect_Indexed_Long,

    Absolute,
    Absolute_Indirect,
    Absolute_Indexed_X,
    Absolute_Indexed_Y,
    Absolute_Indexed_Indirect,

    Absolute_Long,
    Absolute_Indexed_Long,
    Absolute_Indirect_Long,

    Stack_Relative,
    Stack_Relative_Indirect_Indexed,

    Implied_Accumulator,
    Block_move
};

class SNES_CPU
{
private:
    union
    {
        uint16_t C;
        struct // just in emulation mode
        {
            uint8_t A; // Most significative
            uint8_t B; // less signitifcative
        };
    } Accumulator;

    // Registers
    uint8_t DBR; // DataBank, holds the default bank for memory transfers
    uint8_t PBR; // ProgramBank, hold the bank address of al instruction fetches
    uint16_t DP; // Direct Page, it is the base for direct page addressing
    uint16_t PC, SP; // Holds memory address of the current CPU Instruction
    uint16_t X, Y; // Index registers 

    struct 
    {
        uint8_t N : 1; // Negative
        uint8_t V : 1; // Overflow
        uint8_t M : 1; // Accumulator Register size(Native mode only, 0 = 16, 1 = 8)
        uint8_t X : 1; // Index Register(Native mode only, 0 = 16, 1 = 8)
        uint8_t D : 1; // Decimal
        uint8_t I : 1; // IRQ disable
        uint8_t Z : 1; // Zero
        uint8_t C : 1; // Carry
        uint8_t E : 1; // Emulation Mode
        uint8_t B : 1; // Break(Emu)
    } Regs;

    Bus *m_Bus;

    uint8_t m_CurrentValue;
    uint16_t m_CurrentAddress;
    uint8_t m_Cycles; // Cycles to "wait"
    AddressingMode m_AddressingMode;

    void Set_NZ_Flags(uint8_t v);

    void AD_Imm_Mem();
    void AD_Imm_Indx();
    void AD_Imm_8bit();
    void AD_Rel();
    void AD_Rel_Long();
    void AD_Dir();
    void AD_Dir_Indx_X();
    void AD_Dir_Indx_Y();
    void AD_Dir_Indx();
    void AD_Dir_Indx_Ind();
    void AD_Dir_Ind_Indx();
    void AD_Dir_Ind_Long();
    void AD_Dir_Ind_Indx_Long();
    void AD_Abs();
    void AD_Abs_Indx_X();
    void AD_Abs_Indx_Y();
    void AD_Abs_Long();
    void AD_Abs_Indx_Long();
    void AD_Stack_Rel();
    void AD_Stack_Rel_Ind_Indx();
    void AD_Abs_Ind();
    void AD_Abs_Ind_Long();
    void AD_Abs_Indx_Ind();
    void AD_Imp_Acc();
    void AD_Block_Mv();
    void AD_Dir_Pg();

    void Impl_ADC();

    void Impl_AND();
    void Impl_ASL();

    void BLT();
    void BGE();
    void BEQ();

    void Impl_BIT();

    void BMI();
    void BNE();
    void BPL();
    void BRA();

    void BRK_SI();

    // TODO: Vai usar?
    void BRK_PCRL();

    void BVC();
    void BVS();
    
    void CLC();
    void CLD();
    void CLI();
    void CLV();

    void Impl_CMP();

    void COP();

    void Impl_CPX();

    void Impl_CPY();

    void Impl_DEC();

    void DEX();
    void DEY();

    void Impl_INC();
    void INX();
    void INY();

    void Impl_EOR();

    void Impl_JMP();

    void Impl_JSR();

    void Impl_LDA();

    void Impl_LDX();

    void Impl_LDY();

    void Impl_LSR();

    void MVN();
    void MVP();
    void NOP();

    void Impl_ORA();

    void PEA();
    void PEI();
    void PER();

    void PHA();
    void PHB();
    void PHD();
    void PHK();
    void PHP();
    void PHX();
    void PHY();
    void PLA();
    void PLB();
    void PLP();
    void PLX();
    void PLY();
    void REP();

    void Impl_ROL();
    
    void Impl_ROR();

    void RTI();
    void RTL();
    void RTS();

    void Impl_SBC();

    void SEC();
    void SED();
    void SEI();
    void SEP();

    void Impl_STA();

    void STP();

    void Impl_STX();

    void Impl_STY();

    void Impl_STZ();

    void TAX();
    void TAY();
    void TCD();
    void TCS();
    void TDC();

    void Impl_TRB();

    void Impl_TSB();

    void TSC();
    void TSX();
    void TXA();
    void TXS();
    void TXY();
    void TYA();
    void TYX();

    void WAI();
    void WDM();
    void XBA();
    void XCE();
public:
    SNES_CPU(Bus *bus);
};