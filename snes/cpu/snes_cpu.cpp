#include "snes_cpu.h"

SNES_CPU::SNES_CPU(Bus *bus)
{
}

void SNES_CPU::ADC_DPIIX(){}
void SNES_CPU::ADC_SR(){}
void SNES_CPU::ADC_DP(){}
void SNES_CPU::ADC_DPIL(){}
void SNES_CPU::ADC_I(){}
void SNES_CPU::ADC_A(){}
void SNES_CPU::ADC_AL(){}
void SNES_CPU::ADC_DPIIY(){}
void SNES_CPU::ADC_DPI(){}
void SNES_CPU::ADC_SRIIY(){}
void SNES_CPU::ADC_DPIX(){}
void SNES_CPU::ADC_DPILIY(){}
void SNES_CPU::ADC_AIY(){}
void SNES_CPU::ADC_AIX(){}
void SNES_CPU::ADC_ALIX(){}

void SNES_CPU::I_ADC(){}

void SNES_CPU::I_AND()
{
    // Performing the AND operation
    Accumulator.C = Accumulator.C & m_CurrentValue;

    // Set the Zero flag if the result is 0
    Status.Z = (Accumulator.C == 0) ? 1 : 0;

    // Set the Negative flag based on the MSB of the result
    Status.N = (Accumulator.A & 0x80) ? 1 : 0;
}
void SNES_CPU::AND_DPIIX(){
    
}
void SNES_CPU::AND_SR(){}
void SNES_CPU::AND_DP()
{
    // Read the offset
    uint32_t offset = m_Bus->ReadByte(PC);
    PC++;

    // alculate the full address
    uint32_t address = (DP & 0xFF00) | offset;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = m_Bus->ReadByte(address);
    m_AddressingMode = AddressingMode::Direct;

    // Perform the AND operation
    I_AND();
}
void SNES_CPU::AND_DPIL(){}
void SNES_CPU::AND_I(){

}
void SNES_CPU::AND_A()
{
    // Calculate the absolute address with the bank defined by DBR 
    uint32_t address = DBR;
    address = (address << 16) | m_Bus->ReadWord(PC);
    PC += 2;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = m_Bus->ReadByte(address);
    m_AddressingMode = AddressingMode::Absolute;

    // Perform the AND operation
    I_AND();
}
void SNES_CPU::AND_AL()
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

    // Perform the AND operation
    I_AND();
}
void SNES_CPU::AND_DPIIY(){}
void SNES_CPU::AND_DPI(){}
void SNES_CPU::AND_SRIIY(){}
void SNES_CPU::AND_DPIX(){}
void SNES_CPU::AND_DPILIY(){}
void SNES_CPU::AND_AIY(){}
void SNES_CPU::AND_AIX(){}
void SNES_CPU::AND_ALIX(){}

void SNES_CPU::ASL_DP(){}
void SNES_CPU::ASL_ACC(){}
void SNES_CPU::ASL_A(){}
void SNES_CPU::ASL_DPIX(){}
void SNES_CPU::ASL_AIX(){}

void SNES_CPU::BLT(){}
void SNES_CPU::BGE(){}
void SNES_CPU::BEQ(){}

void SNES_CPU::BIT_DP(){}
void SNES_CPU::BIT_A(){}
void SNES_CPU::BIT_DPIX(){}
void SNES_CPU::BIT_AIX(){}
void SNES_CPU::BIT_I(){}

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

void SNES_CPU::CMP_DPIIX(){}
void SNES_CPU::CMP_SR(){}
void SNES_CPU::CMP_DP(){}
void SNES_CPU::CMP_DPIL(){}
void SNES_CPU::CMP_I(){}
void SNES_CPU::CMP_A(){}
void SNES_CPU::CMP_AL(){}
void SNES_CPU::CMP_DPIIY(){}
void SNES_CPU::CMP_DPI(){}
void SNES_CPU::CMP_SRIIY(){}
void SNES_CPU::CMP_DPIX(){}
void SNES_CPU::CMP_DPILIY(){}
void SNES_CPU::CMP_AIY(){}
void SNES_CPU::CMP_AIX(){}
void SNES_CPU::CMP_ALIX(){}

void SNES_CPU::COP(){}

void SNES_CPU::CPX_I(){}
void SNES_CPU::CPX_DP(){}
void SNES_CPU::CPX_A(){}

void SNES_CPU::CPY_I(){}
void SNES_CPU::CPY_DP(){}
void SNES_CPU::CPY_A(){}

void SNES_CPU::DEC_ACC(){}
void SNES_CPU::DEC_DP(){}
void SNES_CPU::DEC_A(){}
void SNES_CPU::DEC_DPIX(){}
void SNES_CPU::DEC_AIX(){}

void SNES_CPU::DEX(){}
void SNES_CPU::DEY(){}

void SNES_CPU::EOR_DPIIX(){}
void SNES_CPU::EOR_SR(){}
void SNES_CPU::EOR_DP(){}
void SNES_CPU::EOR_DPIL(){}
void SNES_CPU::EOR_I(){}
void SNES_CPU::EOR_A(){}
void SNES_CPU::EOR_AL(){}
void SNES_CPU::EOR_DPIIY(){}
void SNES_CPU::EOR_DPI(){}
void SNES_CPU::EOR_SRIIY(){}
void SNES_CPU::EOR_DPIX(){}
void SNES_CPU::EOR_DPILIY(){}
void SNES_CPU::EOR_AIY(){}
void SNES_CPU::EOR_AIX(){}
void SNES_CPU::EOR_ALIX(){}

void SNES_CPU::INC_ACC(){}
void SNES_CPU::INC_DP(){}
void SNES_CPU::INC_A(){}
void SNES_CPU::INC_DPIX(){}
void SNES_CPU::INC_AIX(){}

void SNES_CPU::INX(){}
void SNES_CPU::INY(){}

void SNES_CPU::JMP_A(){}
void SNES_CPU::JMP_AL(){}
void SNES_CPU::JMP_AI(){}
void SNES_CPU::JMP_AII(){}
void SNES_CPU::JMP_AIL(){}

void SNES_CPU::JSR_A(){}
void SNES_CPU::JSR_AL(){}
void SNES_CPU::JSR_AII(){}

void SNES_CPU::LDA_DPIIX(){}
void SNES_CPU::LDA_SR(){}
void SNES_CPU::LDA_DP(){}
void SNES_CPU::LDA_DPIL(){}
void SNES_CPU::LDA_I(){}
void SNES_CPU::LDA_A(){}
void SNES_CPU::LDA_AL(){}
void SNES_CPU::LDA_DPIIY(){}
void SNES_CPU::LDA_DPI(){}
void SNES_CPU::LDA_SRIIY(){}
void SNES_CPU::LDA_DPIX(){}
void SNES_CPU::LDA_DPILIY(){}
void SNES_CPU::LDA_AIY(){}
void SNES_CPU::LDA_AIX(){}
void SNES_CPU::LDA_ALIX(){}

void SNES_CPU::LDX_I(){}
void SNES_CPU::LDX_DP(){}
void SNES_CPU::LDX_A(){}
void SNES_CPU::LDX_DPIY(){}
void SNES_CPU::LDX_AIY(){}

void SNES_CPU::LDY_I(){}
void SNES_CPU::LDY_DP(){}
void SNES_CPU::LDY_A(){}
void SNES_CPU::LDY_DPIX(){}
void SNES_CPU::LDY_AIX(){}

void SNES_CPU::LSR_DP(){}
void SNES_CPU::LSR_ACC(){}
void SNES_CPU::LSR_A(){}
void SNES_CPU::LSR_DPIX(){}
void SNES_CPU::LSR_AIX(){}

void SNES_CPU::MVN(){}
void SNES_CPU::MVP(){}
void SNES_CPU::NOP(){}

void SNES_CPU::ORA_DPIIX(){}
void SNES_CPU::ORA_SR(){}
void SNES_CPU::ORA_DP(){}
void SNES_CPU::ORA_DPIL(){}
void SNES_CPU::ORA_I(){}
void SNES_CPU::ORA_A(){}
void SNES_CPU::ORA_AL(){}
void SNES_CPU::ORA_DPIIY(){}
void SNES_CPU::ORA_DPI(){}
void SNES_CPU::ORA_SRIIY(){}
void SNES_CPU::ORA_DPIX(){}
void SNES_CPU::ORA_DPILIY(){}
void SNES_CPU::ORA_AIY(){}
void SNES_CPU::ORA_AIX(){}
void SNES_CPU::ORA_ALIX(){}

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

void SNES_CPU::ROL_DP(){}
void SNES_CPU::ROL_ACC(){}
void SNES_CPU::ROL_A(){}
void SNES_CPU::ROL_DPIX(){}
void SNES_CPU::ROL_AIX(){}

void SNES_CPU::ROR_DP(){}
void SNES_CPU::ROR_ACC(){}
void SNES_CPU::ROR_A(){}
void SNES_CPU::ROR_DPIX(){}
void SNES_CPU::ROR_AIX(){}

void SNES_CPU::RTI(){}
void SNES_CPU::RTL(){}
void SNES_CPU::RTS(){}

void SNES_CPU::SBC_DPIIX(){}
void SNES_CPU::SBC_SR(){}
void SNES_CPU::SBC_DP(){}
void SNES_CPU::SBC_DPIL(){}
void SNES_CPU::SBC_I(){}
void SNES_CPU::SBC_A(){}
void SNES_CPU::SBC_AL(){}
void SNES_CPU::SBC_DPIIY(){}
void SNES_CPU::SBC_DPI(){}
void SNES_CPU::SBC_SRIIY(){}
void SNES_CPU::SBC_DPIX(){}
void SNES_CPU::SBC_DPIILY(){}
void SNES_CPU::SBC_AIY(){}
void SNES_CPU::SBC_AIX(){}
void SNES_CPU::SBC_ALIX(){}

void SNES_CPU::SEC(){}
void SNES_CPU::SED(){}
void SNES_CPU::SEI(){}
void SNES_CPU::SEP(){}

void SNES_CPU::STA_DPIIX(){}
void SNES_CPU::STA_SR(){}
void SNES_CPU::STA_DP(){}
void SNES_CPU::STA_DPIL(){}
void SNES_CPU::STA_A(){}
void SNES_CPU::STA_AL(){}
void SNES_CPU::STA_DPIIY(){}
void SNES_CPU::STA_DPI(){}
void SNES_CPU::STA_SRIIY(){}
void SNES_CPU::STA_DPIX(){}
void SNES_CPU::STA_DPILIY(){}
void SNES_CPU::STA_AIY(){}
void SNES_CPU::STA_AIX(){}
void SNES_CPU::STA_ALIX(){}

void SNES_CPU::STP(){}

void SNES_CPU::STX_DP(){}
void SNES_CPU::STX_A(){}
void SNES_CPU::STX_DPIY(){}

void SNES_CPU::STY_DP(){}
void SNES_CPU::STY_A(){}
void SNES_CPU::STY_DPIX(){}

void SNES_CPU::STZ_DP(){}
void SNES_CPU::STZ_DPIX(){}
void SNES_CPU::STZ_A(){}
void SNES_CPU::STZ_AIX(){}

void SNES_CPU::TAX(){}
void SNES_CPU::TAY(){}
void SNES_CPU::TCD(){}
void SNES_CPU::TCS(){}
void SNES_CPU::TDC(){}

void SNES_CPU::TRB_DP(){}
void SNES_CPU::TRB_A(){}

void SNES_CPU::TSB_DP(){}
void SNES_CPU::TSB_A(){}

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

