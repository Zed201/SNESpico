#pragma once

#include <bus.h>
#include <stdint.h>

class SNES_CPU
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

    void ADC_DPIIX();
    void ADC_SR();
    void ADC_DP();
    void ADC_DPIL();
    void ADC_I();
    void ADC_A();
    void ADC_AL();
    void ADC_DPIIY();
    void ADC_DPI();
    void ADC_SRIIY();
    void ADC_DPIX();
    void ADC_DPILIY();
    void ADC_AIY();
    void ADC_AIX();
    void ADC_ALIX();

    void AND_DPIIX();
    void AND_SR();
    void AND_DP();
    void AND_DPIL();
    void AND_I();
    void AND_A();
    void AND_AL();
    void AND_DPIIY();
    void AND_DPI();
    void AND_SRIIY();
    void AND_DPIX();
    void AND_DPILIY();
    void AND_AIY();
    void AND_AIX();
    void AND_ALIX();

    void ASL_DP();
    void ASL_ACC();
    void ASL_A();
    void ASL_DPIX();
    void ASL_AIX();

    void BLT();
    void BGE();
    void BEQ();

    void BIT_DP();
    void BIT_A();
    void BIT_DPIX();
    void BIT_AIX();
    void BIT_I();

    void BMI();
    void BNE();
    void BPL();
    void BRA();

    void BRK_SI();
    void BRK_PCRL();

    void BVC();
    void BVS();
    
    void CLC();
    void CLD();
    void CLI();
    void CLV();

    void CMP_DPIIX();
    void CMP_SR();
    void CMP_DP();
    void CMP_DPIL();
    void CMP_I();
    void CMP_A();
    void CMP_AL();
    void CMP_DPIIY();
    void CMP_DPI();
    void CMP_SRIIY();
    void CMP_DPIX();
    void CMP_DPILIY();
    void CMP_AIY();
    void CMP_AIX();
    void CMP_ALIX();

    void COP();

    void CPX_I();
    void CPX_DP();
    void CPX_A();

    void CPY_I();
    void CPY_DP();
    void CPY_A();

    void DEC_ACC();
    void DEC_DP();
    void DEC_A();
    void DEC_DPIX();
    void DEC_AIX();

    void DEX();
    void DEY();

    void EOR_DPIIX();
    void EOR_SR();
    void EOR_DP();
    void EOR_DPIL();
    void EOR_I();
    void EOR_A();
    void EOR_AL();
    void EOR_DPIIY();
    void EOR_DPI();
    void EOR_SRIIY();
    void EOR_DPIX();
    void EOR_DPILIY();
    void EOR_AIY();
    void EOR_AIX();
    void EOR_ALIX();

    void INC_ACC();
    void INC_DP();
    void INC_A();
    void INC_DPIX();
    void INC_AIX();

    void INX();
    void INY();

    void JMP_A();
    void JMP_AL();
    void JMP_AI();
    void JMP_AII();
    void JMP_AIL();

    void JSR_A();
    void JSR_AL();
    void JSR_AII();

    void LDA_DPIIX();
    void LDA_SR();
    void LDA_DP();
    void LDA_DPIL();
    void LDA_I();
    void LDA_A();
    void LDA_AL();
    void LDA_DPIIY();
    void LDA_DPI();
    void LDA_SRIIY();
    void LDA_DPIX();
    void LDA_DPILIY();
    void LDA_AIY();
    void LDA_AIX();
    void LDA_ALIX();

    void LDX_I();
    void LDX_DP();
    void LDX_A();
    void LDX_DPIY();
    void LDX_AIY();

    void LDY_I();
    void LDY_DP();
    void LDY_A();
    void LDY_DPIX();
    void LDY_AIX();

    void LSR_DP();
    void LSR_ACC();
    void LSR_A();
    void LSR_DPIX();
    void LSR_AIX();

    void MVN();
    void MVP();
    void NOP();

    void ORA_DPIIX();
    void ORA_SR();
    void ORA_DP();
    void ORA_DPIL();
    void ORA_I();
    void ORA_A();
    void ORA_AL();
    void ORA_DPIIY();
    void ORA_DPI();
    void ORA_SRIIY();
    void ORA_DPIX();
    void ORA_DPILIY();
    void ORA_AIY();
    void ORA_AIX();
    void ORA_ALIX();

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

    void ROL_DP();
    void ROL_ACC();
    void ROL_A();
    void ROL_DPIX();
    void ROL_AIX();
    
    void ROR_DP();
    void ROR_ACC();
    void ROR_A();
    void ROR_DPIX();
    void ROR_AIX();

    void RTI();
    void RTL();
    void RTS();

    void SBC_DPIIX();
    void SBC_SR();
    void SBC_DP();
    void SBC_DPIL();
    void SBC_I();
    void SBC_A();
    void SBC_AL();
    void SBC_DPIIY();
    void SBC_DPI();
    void SBC_SRIIY();
    void SBC_DPIX();
    void SBC_DPIILY();
    void SBC_AIY();
    void SBC_AIX();
    void SBC_ALIX();

    void SEC();
    void SED();
    void SEI();
    void SEP();

    void STA_DPIIX();
    void STA_SR();
    void STA_DP();
    void STA_DPIL();
    void STA_A();
    void STA_AL();
    void STA_DPIIY();
    void STA_DPI();
    void STA_SRIIY();
    void STA_DPIX();
    void STA_DPILIY();
    void STA_AIY();
    void STA_AIX();
    void STA_ALIX();

    void STP();

    void STX_DP();
    void STX_A();
    void STX_DPIY();

    void STY_DP();
    void STY_A();
    void STY_DPIX();

    void STZ_DP();
    void STZ_DPIX();
    void STZ_A();
    void STZ_AIX();

    void TAX();
    void TAY();
    void TCD();
    void TCS();
    void TDC();

    void TRB_DP();
    void TRB_A();

    void TSB_DP();
    void TSB_A();

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