#include "snes_cpu.h"

SNES_CPU::SNES_CPU(Bus *bus) : m_Bus(bus)
{
}

void SNES_CPU::Step()
{
    uint8_t opcode = m_Bus->ReadByte(PC++);
    m_Cycles = 1;

    switch (opcode)
    {
    case 0x69:
        AD_Imm(Flags.M);
        Impl_ADC();
        break;
    case 0x6D:
        AD_Abs(Flags.M);
        Impl_ADC();
        break;
    case 0x6F:
        AD_Abs_Long();
        Impl_ADC();
        break;
    case 0x65:
        AD_Dir(Flags.M);
        Impl_ADC();
        break;
    case 0x72:
        AD_Dir_Ind();
        Impl_ADC();
        break;
    case 0x67:
        AD_Dir_Ind_Long();
        Impl_ADC();
        break;
    case 0x7D:
        AD_Abs_Indx_X(Flags.M);
        Impl_ADC();
        break;
    case 0x7F:
        AD_Abs_Indx_Long();
        Impl_ADC();
        break;
    case 0x79:
        AD_Abs_Indx_Y(Flags.M);
        Impl_ADC();
        break;
    case 0x75:
        AD_Dir_Indx_X(Flags.M);
        Impl_ADC();
        break;
    case 0x61:
        AD_Dir_Indx_Ind_X();
        Impl_ADC();
        break;
	case 0x71:
		AD_Dir_Ind_Indx_Y();
        Impl_ADC();
        break;
	case 0x77:
		AD_Dir_Ind_Indx_Y();
        Impl_ADC();
        break;
	case 0x63:
        Impl_ADC();
        break;
	case 0x73:
        Impl_ADC();
        break;

    case 0x38: //SEC
        Flags.C = 1;
        m_Cycles += 2;
        break;
    case 0x78: //SED
        Flags.D = 1;
        m_Cycles += 2;
        break;
    case 0xF8: //SEI
        Flags.I = 1;
        m_Cycles += 2;
        break;

    case 0x18: //CLC
        Flags.C = 0;
        m_Cycles += 2;
        break;
    case 0x58: // CLI
        Flags.I = 0;
        m_Cycles += 2;
        break;
    case 0xD8: //CLD
        Flags.D = 0;
        m_Cycles += 2;
        break;
    case 0xB8: // CLV
        Flags.V = 0;
        m_Cycles += 2;
        break;

    case 0xAA: //TAX
        X = Flags.X ? Accumulator.A : Accumulator.C;
        m_Cycles++;
        break;
    case 0xA8: //TAY
        Y = Flags.X ? Accumulator.A : Accumulator.C;
        m_Cycles++;
        break;
    case 0x5B: //TCD
        DP = Accumulator.C;
        m_Cycles++;
        break;
    case 0x1B: //TCS
        SP = Flags.E ? 0x01FF & Accumulator.C : Accumulator.C;
        m_Cycles++;
        break;
    case 0x7B: //TDC
        Accumulator.C = DP;
        m_Cycles++;
        break;
    case 0x3B: //TSC
        Accumulator.C = SP;
        m_Cycles++;
        break;
    case 0xBA: //TSX
        X = Flags.X ? 0x00FF & SP : SP;
        m_Cycles++;
        break;
    case 0x8A: //TXA
        if (!Flags.M) Accumulator.C = Flags.X ? 0x00FF & X : X;
        else Accumulator.A = X;
        m_Cycles++;
        break;
    case 0x9A: //TXS
        SP = Flags.E ? 0x01FF & X : X;
        m_Cycles++;
        break;
    case 0x9B: //TXY
        Y = X;
        m_Cycles++;
        break;
    case 0x98: //TYA
        if (!Flags.M) Accumulator.C = Flags.X ? 0x00FF & Y : Y;
        else Accumulator.A = Y;
        m_Cycles++;
        break;
    case 0xBB: //TYX
        X = Y;
        m_Cycles++;
        break;

    case 0XEA: // NOP
        break;
    default:
        break;
    }
}

/* ADD with carry Implementation */
void SNES_CPU::Impl_ADC()
{
    uint32_t res = Accumulator.C + m_CurrentValue + Flags.C;

    Flags.V = (~(Accumulator.C ^ m_CurrentValue) & (Accumulator.C ^ res)) & 0x80u;
    Set_NZ_Flags(res);
    Flags.C = res > 0xFF;
    Accumulator.C = res;
}

void SNES_CPU::Set_NZ_Flags(uint8_t v)
{
    Flags.N = v & 0x80u;
    Flags.Z = !v;
}

/* AND Implementation */
void SNES_CPU::Impl_AND()
{
    // Performing the AND operation
    Accumulator.C = Accumulator.C & m_CurrentValue;

    // Set the Zero flag if the result is 0
   Set_NZ_Flags(Accumulator.C);
}

/* Test and Reset Memory Bits Against Accumulator Implementation */
void SNES_CPU::Impl_TRB()
{
    Flags.Z = (m_CurrentValue & Accumulator.C) == 0;

    m_CurrentValue = m_CurrentValue & (~Accumulator.C);

    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);
}

/* Test and Set Memory Bits Against Accumulator Implementation */
void SNES_CPU::Impl_TSB()
{
    Flags.Z = (m_CurrentValue & Accumulator.C) == 0;

    m_CurrentValue = m_CurrentValue | Accumulator.C;

    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);
}

/* OR Accumulator with Memory Implementation */
void SNES_CPU::Impl_ORA()
{
    Accumulator.C = Accumulator.C | m_CurrentValue;

    Set_NZ_Flags(Accumulator.C);
}

/* Rotate Left Implementation */
void SNES_CPU::Impl_ROL()
{
    uint8_t oldValue = m_CurrentValue;
    m_CurrentValue = m_CurrentValue + m_CurrentValue + Flags.C;

    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);

    Set_NZ_Flags(m_CurrentValue);
    Flags.C = oldValue & (1 << 7);
}

/* Rotate Right Implementation */
void SNES_CPU::Impl_ROR()
{
    uint8_t oldValue = m_CurrentValue;
    m_CurrentValue = (Flags.C << (Flags.M ? 7 : 15)) | (m_CurrentValue >> 1);

    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);

    Set_NZ_Flags(m_CurrentValue);
    Flags.C = oldValue & (1 << 7);
}

/* Exclusive OR Accumulator with Memory */
void SNES_CPU::Impl_EOR()
{
    Accumulator.C = Accumulator.C ^ m_CurrentValue;

    Set_NZ_Flags(Accumulator.C);
}

/* Jump Implementation */
void SNES_CPU::Impl_JMP()
{
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    PC = m_CurrentAddress;
    m_Cycles += 2;
}

void SNES_CPU::Impl_JMP_Abs_Ind()
{
    // indirect address
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    // Real address
    m_CurrentAddress = m_Bus->ReadWord(m_CurrentAddress);
    PC = m_CurrentAddress;
    m_Cycles += 4;
}

void SNES_CPU::Impl_JMP_Abs_Indx_Ind()
{
    // indirect address
    m_CurrentAddress = m_Bus->ReadWord(PC);
    m_CurrentAddress += Flags.X ? 0x00FF & X : X;
    PC += 2;

    // Real address
    m_CurrentAddress = m_Bus->ReadWord(m_CurrentAddress);
    PC = m_CurrentAddress;
    m_Cycles += 5;
}

void SNES_CPU::Impl_JMP_Long()
{
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    m_CurrentAddress = (m_Bus->ReadByte(PC++) << 16);

    PC = m_CurrentAddress;
    PBR = (m_CurrentAddress >> 16);
    m_Cycles += 3;
}

void SNES_CPU::Impl_JMP_Ind_Long()
{
    // Indirect Address
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    m_CurrentAddress = (m_Bus->ReadByte(m_CurrentAddress + 2) << 16) | m_Bus->ReadWord(m_CurrentAddress);

    PC = m_CurrentAddress;
    PBR = (m_CurrentAddress >> 16);
    m_Cycles += 5;
}

/* Jump to subroutine Implementation */
void SNES_CPU::Impl_JSR()
{
    m_CurrentAddress = (PBR << 16) | m_Bus->ReadWord(PC);
    PC += 2;

    PC -= 1;
    SP -= 2;
    m_Bus->WriteWord(SP + 1, PC);

    PC = m_CurrentAddress;
}

void SNES_CPU::Impl_JSR_Abs_Indx_Ind()
{
    uint16_t addr_indexed = m_Bus->ReadWord(PC);
    addr_indexed += Flags.X ? 0x00FF & X : X; // Se der overflow volta para 0 e n sai do PBR
    PC += 2;

    m_CurrentAddress = (PBR << 16) | m_Bus->ReadWord((PBR << 16) | addr_indexed);

    PC -= 1;
    SP -= 2;
    m_Bus->WriteWord(SP + 1, PC);

    PC = m_CurrentAddress;
}

/* Jump to subroutine Implementation */
void SNES_CPU::Impl_JSL()
{
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;
    // Lendo PBR
    m_CurrentAddress |= (m_Bus->ReadByte(PC++) << 16);

    PC -= 1;
    SP -= 3;
    m_Bus->WriteWord(SP + 1, PC);
    m_Bus->WriteByte(SP + 3, PBR);

    PC = m_CurrentAddress;
    PBR = (m_CurrentAddress >> 16);
}

/* Load Accumulator from memory Implementation */
void SNES_CPU::Impl_LDA()
{
    Accumulator.C = m_CurrentValue;

    Set_NZ_Flags(Accumulator.C);
}

/* Load Index Reg X from memory Implementation */
void SNES_CPU::Impl_LDX()
{
    X = m_CurrentValue;
    Set_NZ_Flags(X);
}

/* Load Index Reg Y from memory Implementation */
void SNES_CPU::Impl_LDY()
{
    Y = m_CurrentValue;
    Set_NZ_Flags(Y);
}

/* Logical Shift Right Implementation */
void SNES_CPU::Impl_LSR()
{
    uint16_t oldValue = m_CurrentValue;
    m_CurrentValue = m_CurrentValue >> 1;

    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);

    Flags.N = 0;
    Flags.Z = (m_CurrentValue == 0);
    Flags.C = oldValue & 1;
}

/* Increment Implementation */
void SNES_CPU::Impl_INC()
{
    m_CurrentValue = m_CurrentValue + 1;

    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);

    Set_NZ_Flags(m_CurrentValue);
    
}

void SNES_CPU::Impl_INC_ACC()
{
    Accumulator.C = Accumulator.C + 1;
    Set_NZ_Flags(Accumulator.C);
}

void SNES_CPU::Impl_INX()
{
    X = X + 1;
    Set_NZ_Flags(X);
}

void SNES_CPU::Impl_INY()
{
    Y = Y + 1;
    Set_NZ_Flags(Y);
}

/* Decrement Implementation */
void SNES_CPU::Impl_DEC()
{
    m_CurrentValue = m_CurrentValue - 1;

    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);

    Set_NZ_Flags(m_CurrentValue);
}

void SNES_CPU::Impl_DEC_ACC()
{
    Accumulator.C = Accumulator.C - 1;

    Set_NZ_Flags(Accumulator.C);
}

void SNES_CPU::Impl_DEX()
{
    X = X - 1;
    Set_NZ_Flags(X);
}

void SNES_CPU::Impl_DEY()
{
    Y = Y - 1;
    Set_NZ_Flags(Y);
}

/* Compare Accumulator with Memory */
void SNES_CPU::Impl_CMP()
{
    uint16_t result = Accumulator.C - m_CurrentValue;

    Set_NZ_Flags(result);
    Flags.C = (Accumulator.C >= m_CurrentValue);
}

/* Compare Index Register X with Memory Implementation */
void SNES_CPU::Impl_CPX()
{
    uint16_t result = X - m_CurrentValue;

    Set_NZ_Flags(result);
    Flags.C = (X >= m_CurrentValue);
}

/* Compare Index Register Y with Memory Implementation */
void SNES_CPU::Impl_CPY()
{
    uint16_t result = Y - m_CurrentValue;

    Set_NZ_Flags(result);
    Flags.C = (Y >= m_CurrentValue);
}

/* Test memory bits against accumulator Implementation */
void SNES_CPU::Impl_BIT()
{
    Flags.N = m_CurrentAddress & 0x80u;
    Flags.V = m_CurrentAddress & 0x40u;
    Flags.Z = !(m_CurrentAddress & Accumulator.C);
}

/* Arithmetic Shift Left */
void SNES_CPU::Impl_ASL()
{
    m_CurrentValue = m_CurrentValue << 1;
    m_Bus->WriteWord(m_CurrentAddress, m_CurrentValue);
    Set_NZ_Flags(m_CurrentValue);
    Flags.C = m_CurrentAddress & 0x80u;
}

/* Store Accumulator to Memory */
void SNES_CPU::Impl_STA()
{
    m_Bus->WriteWord(m_CurrentAddress, Accumulator.C);
}

/* Store Index Register X to Memory */
void SNES_CPU::Impl_STX()
{
    m_Bus->WriteWord(m_CurrentAddress, X);
}

/* Store Index Register Y to Memory */
void SNES_CPU::Impl_STY()
{
    m_Bus->WriteWord(m_CurrentAddress, Y);
}

/* Store Zero to Memory */
void SNES_CPU::Impl_STZ()
{
    m_Bus->WriteWord(m_CurrentAddress, 0);
}

/* Subtract with Borrow from Accumulator */
void SNES_CPU::Impl_SBC()
{
    Accumulator.C = Accumulator.C + (~m_CurrentValue) + Flags.C;

    Set_NZ_Flags(Accumulator.C);
    // TODO: Setar as Flags C e V
}

void SNES_CPU::Impl_BCC()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.C == 0 ? value : 0;
}

void SNES_CPU::Impl_BCS()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.C == 1 ? value : 0;
}

void SNES_CPU::Impl_BNE()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.Z == 0 ? value : 0;
}

void SNES_CPU::Impl_BEQ()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.Z == 1 ? value : 0;
}

void SNES_CPU::Impl_BPL()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.N == 0 ? value : 0;
}

void SNES_CPU::Impl_BMI()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.N == 1 ? value : 0;
}

void SNES_CPU::Impl_BVC()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.V == 0 ? value : 0;
}

void SNES_CPU::Impl_BVS()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += Flags.V == 1 ? value : 0;
}

void SNES_CPU::Impl_BRA()
{
    // Valor com sinal extendido
    int16_t value = static_cast<int16_t>(static_cast<int8_t>(m_Bus->ReadByte(PC++)));

    PC += value;
}

void SNES_CPU::Impl_BRL()
{
    int16_t value = static_cast<int16_t>(m_Bus->ReadWord(PC));
    PC += 2;
    PC += value;
}


void SNES_CPU::Impl_BRK()
{
    if (Flags.E)
    {
        SP -= 3;
        m_Bus->WriteByte(SP + 1, Flags);
        m_Bus->WriteWord(SP + 2, PC);

        Flags.D = 0;
        Flags.I = 1;

        PBR = 0;
        PC = 0xFFF6;
        m_Cycles += 7;
    }
    else
    {
        SP -= 4;
        m_Bus->WriteByte(SP + 1, Flags);
        m_Bus->WriteWord(SP + 2, PC);
        m_Bus->WriteByte(SP + 4, PBR);

        Flags.D = 0;
        Flags.I = 1;

        PBR = 0;
        PC = 0xFFE6;
        m_Cycles += 8;
    }
}

void SNES_CPU::Impl_COP()
{
    if (Flags.E)
    {
        SP -= 3;
        m_Bus->WriteByte(SP + 1, Flags);
        m_Bus->WriteWord(SP + 2, PC);

        Flags.D = 0;
        Flags.I = 1;

        PBR = 0;
        PC = 0xFFF4;
        m_Cycles += 7;
    }
    else
    {
        SP -= 4;
        m_Bus->WriteByte(SP + 1, Flags);
        m_Bus->WriteWord(SP + 2, PC);
        m_Bus->WriteByte(SP + 4, PBR);

        Flags.D = 0;
        Flags.I = 1;

        PBR = 0;
        PC = 0xFFE4;
        m_Cycles += 8;
    }
}

void SNES_CPU::Impl_MVN()
{
    uint8_t srcBank = m_Bus->ReadByte(PC++);
    DBR = m_Bus->ReadByte(PC++); // DBR = destBank

    while (Accumulator.C != 0xFFFF)
    {
        uint8_t tmp = m_Bus->ReadByte((srcBank << 16) | X);
        m_Bus->WriteByte((DBR << 16) | Y, tmp);
        X += 1;
        Y += 1;
        Accumulator.C -= 1;
        m_Cycles += 7;
    }
}

void SNES_CPU::Impl_MVP()
{
    uint8_t srcBank = m_Bus->ReadByte(PC++);
    DBR = m_Bus->ReadByte(PC++); // DBR = destBank

    while (Accumulator.C != 0xFFFF)
    {
        uint8_t tmp = m_Bus->ReadByte((srcBank << 16) | X);
        m_Bus->WriteByte((DBR << 16) | Y, tmp);
        X -= 1;
        Y -= 1;
        Accumulator.C -= 1;
        m_Cycles += 7;
    }
}

void SNES_CPU::Impl_PEA()
{
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    SP -= 2;
    m_Bus->WriteWord(SP + 1, m_CurrentAddress);
}

void SNES_CPU::Impl_PEI()
{
    // Endereço indireto
    m_CurrentAddress = DP + m_Bus->ReadByte(PC++);

    m_CurrentAddress = m_Bus->ReadWord(m_CurrentAddress);

    SP -= 2;
    m_Bus->WriteWord(SP + 1, m_CurrentAddress);
}

void SNES_CPU::Impl_PER()
{
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    m_CurrentAddress = PC + m_CurrentAddress;

    SP -= 2;
    m_Bus->WriteWord(SP + 1, m_CurrentAddress);    
}

void SNES_CPU::Impl_PHA()
{
    if (Flags.M)
    {
        SP -= 1;
        m_Bus->WriteByte(SP + 1, Accumulator.A);
        m_Cycles += 2;
    }
    else
    {
        SP -= 2;
        m_Bus->WriteWord(SP + 1, Accumulator.C);
        m_Cycles += 3;
    }
}

void SNES_CPU::Impl_PHB()
{
    SP -= 1;
    m_Bus->WriteByte(SP + 1, DBR);
    m_Cycles += 2;
}

void SNES_CPU::Impl_PHD()
{
    SP -= 2;
    m_Bus->WriteWord(SP + 1, DP);
    m_Cycles += 3;
}

void SNES_CPU::Impl_PHK()
{
    SP -= 1;
    m_Bus->WriteByte(SP + 1, PBR);
    m_Cycles += 2;
}

void SNES_CPU::Impl_PHP()
{
    SP -= 1;
    m_Bus->WriteByte(SP + 1, Flags);
    m_Cycles += 2;
}

void SNES_CPU::Impl_PHX()
{
    if (Flags.X)
    {
        SP -= 1;
        m_Bus->WriteByte(SP + 1, X);
        m_Cycles += 2;
    }
    else
    {
        SP -= 2;
        m_Bus->WriteWord(SP + 1, X);
        m_Cycles += 3;
    }
}

void SNES_CPU::Impl_PHY()
{
    if (Flags.X)
    {
        SP -= 1;
        m_Bus->WriteByte(SP + 1, Y);
        m_Cycles += 2;
    }
    else
    {
        SP -= 2;
        m_Bus->WriteWord(SP + 1, Y);
        m_Cycles += 3;
    }
}

void SNES_CPU::Impl_PLA()
{
    if (Flags.M)
    {
        Accumulator.A = m_Bus->ReadByte(SP + 1);
        SP++;
        Set_NZ_Flags(Accumulator.A);
        m_Cycles += 3;
    }
    else
    {
        Accumulator.C = m_Bus->ReadWord(SP + 1);
        SP += 2;
        Set_NZ_Flags(Accumulator.C);
        m_Cycles += 4;
    }
}

void SNES_CPU::Impl_PLB()
{
    DBR = m_Bus->ReadByte(SP + 1);
    SP++;
    Set_NZ_Flags(DBR);
    m_Cycles += 3;
}

void SNES_CPU::Impl_PLD()
{
    DP = m_Bus->ReadWord(SP + 1);
    SP += 2;
    Set_NZ_Flags(DP);
    m_Cycles += 4;
}

void SNES_CPU::Impl_PLP()
{
    if (Flags.E)
    {
        Flags = m_Bus->ReadByte(SP + 1);
        SP++;
        Flags.X = 1;
        Flags.M = 1;
    }
    else
    {
        Flags = m_Bus->ReadByte(SP + 1);
        SP++;
    }

    m_Cycles += 3;
}

void SNES_CPU::Impl_PLX()
{
    if (Flags.X)
    {
        X = m_Bus->ReadByte(SP + 1);
        SP++;
        Set_NZ_Flags(X);
        m_Cycles += 3;
    }
    else
    {
        X = m_Bus->ReadWord(SP + 1);
        SP += 2;
        Set_NZ_Flags(X);
        m_Cycles += 4;
    }
}

void SNES_CPU::Impl_PLY()
{
    if (Flags.M)
    {
        Y = m_Bus->ReadByte(SP + 1);
        SP++;
        Set_NZ_Flags(Y);
        m_Cycles += 3;
    }
    else
    {
        Y = m_Bus->ReadWord(SP + 1);
        SP += 2;
        Set_NZ_Flags(Y);
        m_Cycles += 4;
    }
}

void SNES_CPU::Impl_REP()
{
    m_CurrentValue = m_Bus->ReadByte(PC++);

    if (Flags.E)
    {
        Flags = Flags & (~m_CurrentValue);
        Flags.X = 1;
        Flags.M = 1;
    }
    else
        Flags = Flags & (~m_CurrentValue);

    m_Cycles += 3;
}

void SNES_CPU::Impl_RTI()
{
    if (Flags.E)
    {
        Flags = m_Bus->ReadByte(SP + 1);
        Flags.X = 1;
        Flags.M = 1;

        X = 0x00FF & X;
        Y = 0x00FF & Y;

        PC = m_Bus->ReadWord(SP + 2);
        SP += 3;
    }
    else
    {
        Flags = m_Bus->ReadByte(SP + 1);

        if (Flags.X)
        {
            X = 0x00FF & X;
            Y = 0x00FF & Y;
        }

        PC = m_Bus->ReadWord(SP + 2);
        PBR = m_Bus->ReadByte(SP + 4);
        SP += 4;
    }
}

void SNES_CPU::Impl_RTS()
{
    PC = m_Bus->ReadWord(SP + 1);
    SP += 2;
    PC += 1;
}

void SNES_CPU::Impl_RTL()
{
    PC = m_Bus->ReadWord(SP + 1);
    PBR = m_Bus->ReadByte(SP + 3);
    SP += 3;
    PC += 1;
}

void SNES_CPU::Impl_SEP()
{
    m_CurrentValue = m_Bus->ReadByte(PC++);
    Flags = Flags | m_CurrentValue;

    // Caso a flag X seja 1 ent
    if (Flags.X)
    {
        X = 0x00FF & X;
        Y = 0x00FF & Y;
    }
}

void SNES_CPU::STP(){}
void SNES_CPU::WAI(){}
void SNES_CPU::WDM(){}

void SNES_CPU::XBA()
{
    // t = A.h
    // A.h = A.l
    // A.l = t

    uint8_t tmp = Accumulator.B;
    Accumulator.B = Accumulator.A;
    Accumulator.A = tmp;
}

void SNES_CPU::XCE()
{
    auto tmp = Flags.C;
    Flags.C = Flags.E;
    Flags.E = tmp;

    if (Flags.E)
    {
        Flags.M = 1;
        Flags.X = 1;
        SP = 0x0100 | (SP & 0x00FF); // SP.h = 0x01
        X = 0x00FF & X; // X.h = 0x00
        Y = 0x00FF & Y; // Y.h = 0x00
    }
}

void SNES_CPU::AD_Imm(uint8_t bit)
{
    if (!bit) // 16 bits
    {
        m_CurrentValue = m_Bus->ReadWord(PC);
        PC += 2;
    }
    else // 8 bits
        m_CurrentValue = m_Bus->ReadByte(PC++);

    m_AddressingMode = AddressingMode::Immediate;
}

void SNES_CPU::AD_Dir(uint8_t bit)
{
    // Read the offset
    m_CurrentAddress = m_Bus->ReadByte(PC++);

    uint8_t dpLow = (DP & 0x00FF);
    if (dpLow != 0)
    {
        m_CurrentAddress += dpLow;
        m_Cycles++;
    }

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = bit ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
    m_AddressingMode = AddressingMode::Direct;
}

void SNES_CPU::AD_Dir_Indx_X(uint8_t bit)
{
    m_CurrentAddress = DP + m_Bus->ReadByte(PC++);

    if (Flags.X)
        m_CurrentAddress += 0x00FF & X; // Soma apenas os bits menos significativos
    else
        m_CurrentAddress += X;

    m_CurrentValue = bit ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
}

void SNES_CPU::AD_Dir_Indx_Y(uint8_t bit)
{
    m_CurrentAddress = DP + m_Bus->ReadByte(PC++);

    if (Flags.X)
        m_CurrentAddress += 0x00FF & Y; // Soma apenas os bits menos significativos
    else
        m_CurrentAddress += Y;

    m_CurrentValue = bit ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
}

void SNES_CPU::AD_Dir_Indx_Ind()
{

}

void SNES_CPU::AD_Dir_Ind()
{
    uint8_t operand = m_Bus->ReadByte(PC++);

    uint8_t dpLow = (DP & 0x00FF);
    if (dpLow != 0)
        m_Cycles++;

    m_CurrentAddress = (DBR << 16) | (m_Bus->ReadByte(dpLow + operand + 1) << 8) | (m_Bus->ReadByte(dpLow + operand));
    m_CurrentValue = Flags.M ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
    m_AddressingMode = AddressingMode::Direct_Indirect;
}

void SNES_CPU::AD_Dir_Ind_Indx()
{

}

void SNES_CPU::AD_Dir_Ind_Long()
{
    uint8_t operand = m_Bus->ReadByte(PC++);

    uint8_t dpLow = (DP & 0x00FF);
    if (dpLow != 0)
        m_Cycles++;

    m_CurrentAddress = (m_Bus->ReadByte(dpLow + operand + 2) << 16) | (m_Bus->ReadByte(dpLow + operand + 1) << 8) | m_Bus->ReadByte(dpLow + operand);
    m_CurrentValue = Flags.M ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
    m_AddressingMode = AddressingMode::Direct_Indirect_Long;
}

void SNES_CPU::AD_Dir_Ind_Indx_Long()
{

}

void AD_Dir_Indx_Ind_X()
{
	
}

void AD_Dir_Ind_Indx_Y()
{

}

void SNES_CPU::AD_Rel(){}
void SNES_CPU::AD_Rel_Long(){}

void SNES_CPU::AD_Abs(uint8_t bit)
{
    // Calculate the absolute address with the bank defined by DBR 
    m_CurrentAddress = (DBR << 16) | m_Bus->ReadWord(PC);
    PC += 2;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = bit ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
    m_AddressingMode = AddressingMode::Absolute;
}

void SNES_CPU::AD_Abs_Indx_X(uint8_t bit)
{
    m_CurrentAddress = (DBR << 16) | m_Bus->ReadWord(PC);
    PC += 2;

    if (Flags.X)
        m_CurrentAddress += 0x00FF & X; // Soma apenas os bits menos significativos
    else
        m_CurrentAddress += X;

    m_CurrentValue = bit ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
    DBR = (m_CurrentAddress >> 16); // Atualiza o DBR para os 8 bits mais significativos do endereço
}

void SNES_CPU::AD_Abs_Indx_Y(uint8_t bit)
{
    m_CurrentAddress = (DBR << 16) | m_Bus->ReadWord(PC);
    PC += 2;

    if (Flags.X)
        m_CurrentAddress += 0x00FF & Y; // Soma apenas os bits menos significativos
    else
        m_CurrentAddress += Y;

    m_CurrentValue = bit ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
    DBR = (m_CurrentAddress >> 16); // Atualiza o DBR para os 8 bits mais significativos do endereço
}

void SNES_CPU::AD_Abs_Long()
{
    // Read the first 2 bytes of the address (low and high)
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    // Read the third byte (bank)
    m_CurrentAddress = (m_Bus->ReadByte(PC++) << 16) | m_CurrentAddress;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = Flags.M ? m_Bus->ReadByte(m_CurrentAddress) : m_Bus->ReadWord(m_CurrentAddress);
    m_AddressingMode = AddressingMode::Absolute_Long;
}

void SNES_CPU::AD_Abs_Indx_Long()
{
    // Read the first 2 bytes of the address (low and high)
    m_CurrentAddress = m_Bus->ReadWord(PC);
    PC += 2;

    // Read the third byte (bank)
    m_CurrentAddress = m_CurrentAddress | (m_Bus->ReadByte(PC++) << 16);

    m_CurrentAddress += Flags.X ? 0x00FF & X : X;

    // Read the value in the memory and set the addressing mode
    m_CurrentValue = m_Bus->ReadWord(m_CurrentAddress);
    m_AddressingMode = AddressingMode::Absolute_Indexed_Long;
}

void SNES_CPU::AD_Stack_Rel(){}
void SNES_CPU::AD_Stack_Rel_Ind_Indx(){}
void SNES_CPU::AD_Abs_Ind(){}
void SNES_CPU::AD_Abs_Ind_Long(){}
void SNES_CPU::AD_Abs_Indx_Ind(){}
void SNES_CPU::AD_Imp_Acc(){}
void SNES_CPU::AD_Block_Mv(){}
