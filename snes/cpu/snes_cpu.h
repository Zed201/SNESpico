#pragma once

#include <Ram.h>
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
            uint8_t A; // Less significative
            uint8_t B; // Most signitifcative
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
    } Flags;

    Ram *m_Ram;

    uint8_t m_CurrentValue;
    uint24_t m_CurrentAddress;
    uint8_t m_Cycles; // Cycles to "wait"
    AddressingMode m_AddressingMode;

    void Set_NZ_Flags(uint8_t v);

    void AD_Imm(uint8_t bit);
    void AD_Rel();
    void AD_Rel_Long();

    void AD_Dir(uint8_t bit);
    void AD_Dir_Indx_X();
    void AD_Dir_Indx_Y();
    void AD_Dir_Indx_Ind();
    void AD_Dir_Ind();
    void AD_Dir_Ind_Indx();
    void AD_Dir_Ind_Long();
    void AD_Dir_Ind_Indx_Long();

    void AD_Abs(uint8_t bit);
    void AD_Abs_Indx_X();
    void AD_Abs_Indx_Y();
    void AD_Abs_Long();
    void AD_Abs_Indx_Ind();
    void AD_Abs_Indx_Long();
    
    void AD_Abs_Ind();
    void AD_Abs_Ind_Long();
    
    void AD_Stack_Rel();
    void AD_Stack_Rel_Ind_Indx();
    void AD_Imp_Acc();
    void AD_Block_Mv();

    void Impl_ADC();

    void Impl_AND();
    void Impl_ASL();

    void Impl_BIT();

    void Impl_BCC();
    void Impl_BCS();
    void Impl_BNE();
    void Impl_BEQ();
    void Impl_BPL();
    void Impl_BMI();
    void Impl_BVC();
    void Impl_BVS();
    void Impl_BRA();
    void Impl_BRL();

    void Impl_BRK();
    void Impl_COP();

    void Impl_CMP();
    void Impl_CPX();
    void Impl_CPY();


    void Impl_DEC();
    void Impl_DEC_ACC();
    void Impl_DEX();
    void Impl_DEY();

    void Impl_INC();
    void Impl_INC_ACC();
    void Impl_INX();
    void Impl_INY();

    void Impl_EOR();

    void Impl_JMP();
    void Impl_JMP_Abs_Ind();
    void Impl_JMP_Abs_Indx_Ind();
    void Impl_JMP_Long();
    void Impl_JMP_Ind_Long();

    void Impl_JSR();
    void Impl_JSR_Abs_Indx_Ind();
    void Impl_JSL();

    void Impl_LDA();

    void Impl_LDX();

    void Impl_LDY();

    void Impl_LSR();

    void Impl_MVN();
    void Impl_MVP();

    void Impl_ORA();

    void Impl_PEA();
    void Impl_PEI();
    void Impl_PER();

    void Impl_PHA();
    void Impl_PHB();
    void Impl_PHD();
    void Impl_PHK();
    void Impl_PHP();
    void Impl_PHX();
    void Impl_PHY();

    void Impl_PLA();
    void Impl_PLB();
    void Impl_PLD();
    void Impl_PLP();
    void Impl_PLX();
    void Impl_PLY();

    void Impl_REP();

    void Impl_ROL();
    
    void Impl_ROR();

    void Impl_RTI();
    void Impl_RTS();
    void Impl_RTL();

    void Impl_SBC();

    void Impl_SEP();

    void Impl_STA();

    void STP();

    void Impl_STX();

    void Impl_STY();

    void Impl_STZ();

    void Impl_TRB();

    void Impl_TSB();

    void WAI();
    void WDM();
    void XBA();
    void XCE();
public:
    SNES_CPU(Ram *ram);

    void Step();
};