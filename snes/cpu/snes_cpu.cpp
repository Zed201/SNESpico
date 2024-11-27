#include "snes_cpu.h"

SNES_CPU::SNES_CPU(Bus *bus)
{
}

void SNES_CPU::Impl_ADC(){}

void SNES_CPU::Impl_AND()
{
    // Performing the AND operation
    Accumulator.C = Accumulator.C & m_CurrentValue;

    // Set the Zero flag if the result is 0
    Status.Z = (Accumulator.C == 0) ? 1 : 0;

    // Set the Negative flag based on the MSB of the result
    Status.N = (Accumulator.A & 0x80) ? 1 : 0;
}

void SNES_CPU::Impl_TRB(){}

void SNES_CPU::Impl_TSB(){}

void SNES_CPU::Impl_ORA(){}

void SNES_CPU::Impl_ROL(){}

void SNES_CPU::Impl_ROR(){}

void SNES_CPU::Impl_EOR(){}

void SNES_CPU::Impl_JMP(){}

void SNES_CPU::Impl_JSR(){}

void SNES_CPU::Impl_LDA(){}

void SNES_CPU::Impl_LDX(){}

void SNES_CPU::Impl_LDY(){}

void SNES_CPU::Impl_LSR(){}

void SNES_CPU::Impl_INC(){}

void SNES_CPU::Impl_CPX(){}

void SNES_CPU::Impl_CPY(){}

void SNES_CPU::Impl_DEC(){}

void SNES_CPU::Impl_CMP(){}

void SNES_CPU::Impl_BIT(){}

void SNES_CPU::Impl_ASL(){}

void SNES_CPU::Impl_STA(){}

void SNES_CPU::Impl_STX(){}

void SNES_CPU::Impl_STY(){}

void SNES_CPU::Impl_STZ(){}

void SNES_CPU::Impl_SBC(){}

void SNES_CPU::Impl_ADC(){}

void SNES_CPU::AD_Imm_Mem()
{
    if (!Status.M || !Status.X) // 16 bits
    {
        m_CurrentValue = m_Bus->ReadWord(PC);
        PC += 2;
    } 
    else // 8 bits
    {
        m_CurrentValue = m_Bus->ReadByte(PC++);
    }
}
void SNES_CPU::AD_Abs()
{
    // Calculate the absolute address with the bank defined by DBR 
    uint32_t address = DBR;
    address = (address << 16) | m_Bus->ReadWord(PC);
    PC += 2;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = m_Bus->ReadByte(address);
    m_AddressingMode = AddressingMode::Absolute;
}
void SNES_CPU::AD_Abs_Long()
{
    // Read the first 2 bytes of the address (low and high)
    uint32_t address = m_Bus->ReadWord(PC);
    PC += 2;

    // Read the third byte (bank)
    address |= static_cast<uint32_t>(m_Bus->ReadByte(PC)) << 16;
    PC++;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = m_Bus->ReadWord(address);
    m_AddressingMode = AddressingMode::Absolute_Long;
}
void SNES_CPU::AD_Dir_Pg()
{
    // Read the offset
    uint32_t offset = m_Bus->ReadByte(PC);
    PC++;

    // alculate the full address
    uint32_t address = DP + offset;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = m_Bus->ReadByte(address);
    m_CurrentAddress = address;
    m_AddressingMode = AddressingMode::Direct;
}

void SNES_CPU::AD_Imm_Indx(){}
void SNES_CPU::AD_Imm_8bit(){}
void SNES_CPU::AD_Rel(){}
void SNES_CPU::AD_Rel_Long(){}
void SNES_CPU::AD_Dir(){}
void SNES_CPU::AD_Dir_Indx_X(){}
void SNES_CPU::AD_Dir_Indx_Y(){}
void SNES_CPU::AD_Dir_Indx(){}
void SNES_CPU::AD_Dir_Indx_Ind(){}
void SNES_CPU::AD_Dir_Ind_Indx(){}
void SNES_CPU::AD_Dir_Ind_Long(){}
void SNES_CPU::AD_Dir_Ind_Indx_Long(){}
void SNES_CPU::AD_Abs_Indx_X(){}
void SNES_CPU::AD_Abs_Indx_Y(){}
void SNES_CPU::AD_Abs_Indx_Long(){}
void SNES_CPU::AD_Stack_Rel(){}
void SNES_CPU::AD_Stack_Rel_Ind_Indx(){}
void SNES_CPU::AD_Abs_Ind(){}
void SNES_CPU::AD_Abs_Ind_Long(){}
void SNES_CPU::AD_Abs_Indx_Ind(){}
void SNES_CPU::AD_Imp_Acc(){}
void SNES_CPU::AD_Block_Mv(){}

void SNES_CPU::BLT(){}
void SNES_CPU::BGE(){}
void SNES_CPU::BEQ(){}

void SNES_CPU::BMI(){}
void SNES_CPU::BNE(){}
void SNES_CPU::BPL(){}
void SNES_CPU::BRA(){}

void SNES_CPU::BRK_SI(){}

void SNES_CPU::BRK_PCRL(){}

void SNES_CPU::BVC(){}
void SNES_CPU::BVS(){}

void SNES_CPU::CLC(){}
void SNES_CPU::CLD(){}
void SNES_CPU::CLI(){}
void SNES_CPU::CLV(){}

void SNES_CPU::COP(){}

void SNES_CPU::DEX(){}
void SNES_CPU::DEY(){}

void SNES_CPU::INX(){}
void SNES_CPU::INY(){}

void SNES_CPU::MVN(){}
void SNES_CPU::MVP(){}
void SNES_CPU::NOP(){}

void SNES_CPU::PEA(){}
void SNES_CPU::PEI(){}
void SNES_CPU::PER(){}

void SNES_CPU::PHA(){}
void SNES_CPU::PHB(){}
void SNES_CPU::PHD(){}
void SNES_CPU::PHK(){}
void SNES_CPU::PHP(){}
void SNES_CPU::PHX(){}
void SNES_CPU::PHY(){}
void SNES_CPU::PLA(){}
void SNES_CPU::PLB(){}
void SNES_CPU::PLP(){}
void SNES_CPU::PLX(){}
void SNES_CPU::PLY(){}
void SNES_CPU::REP(){}

void SNES_CPU::RTI(){}
void SNES_CPU::RTL(){}
void SNES_CPU::RTS(){}

void SNES_CPU::SEC(){}
void SNES_CPU::SED(){}
void SNES_CPU::SEI(){}
void SNES_CPU::SEP(){}
void SNES_CPU::STP(){}

void SNES_CPU::TAX(){}
void SNES_CPU::TAY(){}
void SNES_CPU::TCD(){}
void SNES_CPU::TCS(){}
void SNES_CPU::TDC(){}

void SNES_CPU::TSC(){}
void SNES_CPU::TSX(){}
void SNES_CPU::TXA(){}
void SNES_CPU::TXS(){}
void SNES_CPU::TXY(){}
void SNES_CPU::TYA(){}
void SNES_CPU::TYX(){}

void SNES_CPU::WAI(){}
void SNES_CPU::WDM(){}
void SNES_CPU::XBA(){}
void SNES_CPU::XCE(){}