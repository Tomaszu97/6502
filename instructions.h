#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "debug.h"
#include "memory.h"
#include "opcodes.h"

// reference website at http://www.6502.org/tutorials/6502opcodes.html

#define instr_len 0x01
#define imm_len   0x01
#define immw_len  0x02
#define zp_len    0x01
#define zpx_len   0x01
#define zpy_len   0x01
#define rel_len   0x01
#define abs_len   0x02
#define absx_len  0x02
#define absy_len  0x02
#define ind_len   0x02
#define indx_len  0x01
#define ind_y_len 0x01

#define DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(instr, oper_reg, mode) \
void instr##_##mode() \
{ \
    debug_print("[%02X] "#instr"_"#mode" \t", instr##_##mode##_); \
\
    const sbyte reg_val = oper_reg;\
    const sbyte cmp_val = mode##_();\
\
    instr##_(reg_val, cmp_val);\
\
    PC += instr_len + mode##_##len;\
} \

const byte imm_()
{
    const byte val = read_byte(PC + 0x01);
    return val;
}

const word immw_()
{
    const word val = read_word(PC + 0x01);
    return val;
}

const byte zp_()
{
    const byte zp_addr = read_byte(PC + 0x01);
    const byte val = read_byte((word)zp_addr);
    return val;
}

byte *ptr_zp_()
{
    const byte zp_addr = read_byte(PC + 0x01);
    byte *ptr = &RAM[(word)zp_addr];
    return ptr;
}

const byte zpx_()
{
    const byte zp_addr = read_byte(PC + 0x01) + X;
    const byte val = read_byte((word)zp_addr);
    return val;
}

byte *ptr_zpx_()
{
    const byte zp_addr = read_byte(PC + 0x01) + X;
    byte *ptr = &RAM[(word)zp_addr];
    return ptr;
}

const byte zpy_()
{
    const byte zp_addr = read_byte(PC + 0x01) + Y;
    const byte val = read_byte((word)zp_addr);
    return val;
}

byte *ptr_zpy_()
{
    const byte zp_addr = read_byte(PC + 0x01) + Y;
    byte *ptr = &RAM[(word)zp_addr];
    return ptr;
}

const sbyte rel_()
{
    const sbyte val = read_byte(PC + 0x01);
    return val;
}

const byte abs_()
{
    const word addr = read_word(PC + 0x01);
    const byte val = read_byte(addr);
    return val;
}

byte *ptr_abs_()
{
    const word addr = read_word(PC + 0x01);
    byte *ptr = &RAM[(word)addr];
    return ptr;
}

const byte absx_()
{
    const word addr = read_word(PC + 0x01) + X;
    const byte val = read_byte(addr);
    return val;
}

byte *ptr_absx_()
{
    const word addr = read_word(PC + 0x01) + X;
    byte *ptr = &RAM[(word)addr];
    return ptr;
}

const byte absy_()
{
    const word addr = read_word(PC + 0x01) + Y;
    const byte val = read_byte(addr);
    return val;
}

byte *ptr_absy_()
{
    const word addr = read_word(PC + 0x01) + Y;
    byte *ptr = &RAM[(word)addr];
    return ptr;
}

const byte ind_()
{
    const word addr_addr = read_word(PC + 0x01);
    const word addr = read_word(addr_addr);
    const byte val = read_byte(addr);
    return val;
}

const byte indx_()
{
    const byte addr_zp_addr = read_byte(PC + 0x01) + X;
    const word addr = read_word(0x0000 + (word)addr_zp_addr);
    const byte val = read_byte(addr);
    return val;
}

byte *ptr_indx_()
{
    const byte addr_zp_addr = read_byte(PC + 0x01) + X;
    const word addr = read_word(0x0000 + (word)addr_zp_addr);
    byte *ptr = &RAM[addr];
    return ptr;
}

const byte ind_y_()
{
    const byte addr_zp_addr = read_byte(PC + 0x01);
    const word addr = read_word(0x0000 + (word)addr_zp_addr) + Y;
    const byte val = read_byte(addr);
    return val;
}

byte *ptr_ind_y_()
{
    const byte addr_zp_addr = read_byte(PC + 0x01);
    const word addr = read_word(0x0000 + (word)addr_zp_addr) + Y;
    byte *ptr = &RAM[addr];
    return ptr;
}

void NOP()
{
    debug_print("[%02X] NOP \t", NOP_);
    PC += instr_len;
}

void TXS()
{
    debug_print("[%02X] TXS \t", TXS_);
    SP = X;
    PC += instr_len;
}

void TSX()
{
    debug_print("[%02X] TSX \t", TSX_);
    X = SP;
    PC += instr_len;
}

void PHA()
{
    debug_print("[%02X] PHA \t", PHA_);
    push(A);
    PC += instr_len;
}

void PLA()
{
    debug_print("[%02X] PLA \t", PLA_);
    A = pull();
    PC += instr_len;
}

void PHP()
{
    debug_print("[%02X] PHP \t", PHP_);
    push(get_PS());
    PC += instr_len;
}

void PLP()
{
    debug_print("[%02X] PLP \t", PLP_);
    set_PS(pull());
    PC += instr_len;
}

void TAX()
{
    debug_print("[%02X] TAX \t", TAX_);
    X = A;
    PC += instr_len;
}

void TXA()
{
    debug_print("[%02X] TXA \t", TXA_);
    A = X;
    PC += instr_len;
}

void DEX()
{
    debug_print("[%02X] DEX \t", DEX_);
    X -= 1;
    PC += instr_len;
}

void INX()
{
    debug_print("[%02X] INX \t", INX_);
    X += 1;
    PC += instr_len;
}

void TAY()
{
    debug_print("[%02X] TAY \t", TAY_);
    Y = A;
    PC += instr_len;
}

void TYA()
{
    debug_print("[%02X] TYA \t", TYA_);
    A = Y;
    PC += instr_len;
}

void DEY()
{
    debug_print("[%02X] DEY \t", DEY_);
    Y -= 1;
    PC += instr_len;
}

void INY()
{
    debug_print("[%02X] INY \t", INY_);
    Y += 1;
    PC += instr_len;
}

void CLC()
{
    debug_print("[%02X] CLC \t", CLC_);
    CF = false;
    PC += instr_len;
}

void SEC()
{
    debug_print("[%02X] SEC \t", SEC_);
    CF = true;
    PC += instr_len;
}

void CLI()
{
    debug_print("[%02X] CLI \t", CLI_);
    ID = false;
    PC += instr_len;
}

void SEI()
{
    debug_print("[%02X] SEI \t", SEI_);
    ID = true;
    PC += instr_len;
}

void CLV()
{
    debug_print("[%02X] CLV \t", CLV_);
    OVF = false;
    PC += instr_len;
}

void CLD()
{
    debug_print("[%02X] CLD \t", CLD_);
    DM = false;
    PC += instr_len;
}

void SED()
{
    debug_print("[%02X] SED \t", SED_);
    DM = true;
    PC += instr_len;
}

void BPL()
{
    debug_print("[%02X] BPL \t", BPL_);
    if (NF == false)
        PC += rel_();
    PC += instr_len + rel_len;
}

void BMI()
{
    debug_print("[%02X] BMI \t", BMI_);
    if (NF == true)
        PC += rel_();
    PC += instr_len + rel_len;
}

void BVC()
{
    debug_print("[%02X] BVC \t", BVC_);
    if (OVF == false)
        PC += rel_();
    PC += instr_len + rel_len;
}

void BVS()
{
    debug_print("[%02X] BVS \t", BVS_);
    if (OVF == true)
        PC += rel_();
    PC += instr_len + rel_len;
}

void BCC()
{
    debug_print("[%02X] BCC \t", BCC_);
    if (CF == false)
        PC += rel_();
    PC += instr_len + rel_len;
}

void BCS()
{
    debug_print("[%02X] BCS \t", BCS_);
    if (CF == true)
        PC += rel_();
    PC += instr_len + rel_len;
}

void BNE()
{
    debug_print("[%02X] BNE \t", BNE_);
    if (ZF == false)
        PC += rel_();
    PC += instr_len + rel_len;
}

void BEQ()
{
    debug_print("[%02X] BEQ \t", BEQ_);
    if (ZF == true)
        PC += rel_();
    PC += instr_len + rel_len;
}

void CMP_(const sbyte reg_val,
          const sbyte cmp_val)
{
    const sbyte sub_res_val = reg_val - cmp_val;

    NF = ((0b10000000 & sub_res_val) != 0);
    ZF = (sub_res_val == 0);
    CF = (sub_res_val >= 0);
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, zpx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, abs);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, absx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, absy);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, indx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CMP, A, ind_y);

void CPX_(const sbyte reg_val,
          const sbyte cmp_val)
{
    CMP_(reg_val, cmp_val);
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CPX, X, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CPX, X, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CPX, X, abs);

void CPY_(const sbyte reg_val,
          const sbyte cmp_val)
{
    CMP_(reg_val, cmp_val);
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CPY, Y, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CPY, Y, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(CPY, Y, abs);

void BIT_(const sbyte reg_val,
          const sbyte cmp_val)
{
    const bool any_bit_set = ((reg_val & cmp_val) != 0);
    if (any_bit_set == true)
        ZF = true;
    else
        ZF = false;
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(BIT, A, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(BIT, A, abs);

void JMP_abs()
{
    const word jmp_addr = immw_();
    debug_print("[%02X] JMP_abs %04X \t", JMP_abs_, jmp_addr);
    PC = jmp_addr;
}

void JMP_ind()
{
    const word jmp_addr_addr = immw_();
    const word jmp_addr = read_word(jmp_addr_addr);
    debug_print("[%02X] JMP_ind (%04X) %04X \t",
                JMP_ind_,
                jmp_addr_addr, 
                jmp_addr);
    PC = jmp_addr;
}

void JSR()
{
    const word jmp_addr = immw_();
    debug_print("[%02X] JSR %04X \t", JSR_, jmp_addr);

    const word saved_addr = PC + instr_len + immw_len - 1;
    push_word(saved_addr);

    PC = jmp_addr;
}

void RTS()
{
    debug_print("[%02X] RTS \t", RTS_);

    const word saved_addr = pull_word() + 1;

    PC = saved_addr;
}

void BRK()
{
    debug_print("[%02X] BRK \t", BRK_);
    PC += instr_len;
}

void RTI()
{
    debug_print("[%02X] RTI \t", RTI_);
    PC += instr_len;
}

void ADC_(const byte reg_val,
          const byte cmp_val)
{
    const byte res = reg_val + cmp_val + (CF ? 0x01 : 0x00);
    const bool reg_val_sign = ((reg_val & 0b10000000) != 0);
    const bool cmp_val_sign = ((cmp_val & 0b10000000) != 0);
    const bool res_sign     = ((res     & 0b10000000) != 0);
    OVF = (reg_val_sign == cmp_val_sign) && (reg_val_sign != res_sign);
    CF = (((word)reg_val + (word)cmp_val) > 0xFF);
    ZF = (res == 0);
    NF = res_sign;
    A = res;
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, zpx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, abs);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, absx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, absy);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, indx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ADC, A, ind_y);

void SBC_(const byte reg_val,
          const byte cmp_val)
{
    const byte cmp_val_compl = cmp_val ^ 0xFF;
    ADC_(reg_val, cmp_val_compl);
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, zpx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, abs);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, absx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, absy);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, indx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(SBC, A, ind_y);

void AND_(const byte reg_val,
          const byte cmp_val)
{
    A = reg_val & cmp_val;
    ZF = (A == 0);
    NF = ((sbyte)A < 0);
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, zpx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, abs);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, absx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, absy);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, indx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(AND, A, ind_y);

void ORA_(const byte reg_val,
          const byte cmp_val)
{
    A = reg_val | cmp_val;
    ZF = (A == 0);
    NF = ((sbyte)A < 0);
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, zpx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, abs);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, absx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, absy);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, indx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(ORA, A, ind_y);

void EOR_(const byte reg_val,
          const byte cmp_val)
{
    A = reg_val ^ cmp_val;
    ZF = (A == 0);
    NF = ((sbyte)A < 0);
}

DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, imm);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, zp);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, zpx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, abs);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, absx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, absy);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, indx);
DEFINE_2_OPERAND_INSTRUCTION_REGISTER_MODE(EOR, A, ind_y);

void ASL_acc()
{
    debug_print("[%02X] ASL_acc \t", ASL_acc_);

    CF = ((A & 0x80) != 0);
    A <<= 0x01;
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len;
}

void ASL_zp()
{
    debug_print("[%02X] ASL_zp \t", ASL_zp_);

    byte *ptr = ptr_zp_();
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zp_len;
}

void ASL_zpx()
{
    debug_print("[%02X] ASL_zpx \t", ASL_zpx_);

    byte *ptr = ptr_zpx_();
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zpx_len;
}

void ASL_abs()
{
    debug_print("[%02X] ASL_abs \t", ASL_abs_);

    byte *ptr = ptr_abs_();
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + abs_len;
}

void ASL_absx()
{
    debug_print("[%02X] ASL_absx \t", ASL_absx_);

    byte *ptr = ptr_absx_();
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + absx_len;
}

void LSR_acc()
{
    debug_print("[%02X] LSR_acc \t", LSR_acc_);

    CF = ((A & 0x01) != 0);
    A >>= 0x01;
    A &= ~(0x80);
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len;
}

void LSR_zp()
{
    debug_print("[%02X] LSR_zp \t", LSR_zp_);

    byte *ptr = ptr_zp_();
    CF = ((*ptr & 0x80) != 0);
    *ptr >>= 0x01;
    *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zp_len;
}

void LSR_zpx()
{
    debug_print("[%02X] LSR_zpx \t", LSR_zpx_);

    byte *ptr = ptr_zpx_();
    CF = ((*ptr & 0x80) != 0);
    *ptr >>= 0x01;
    *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zpx_len;
}

void LSR_abs()
{
    debug_print("[%02X] LSR_abs \t", LSR_abs_);

    byte *ptr = ptr_abs_();
    CF = ((*ptr & 0x80) != 0);
    *ptr >>= 0x01;
    *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + abs_len;
}

void LSR_absx()
{
    debug_print("[%02X] LSR_absx \t", LSR_absx_);

    byte *ptr = ptr_absx_();
    CF = ((*ptr & 0x80) != 0);
    *ptr >>= 0x01;
    *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + absx_len;
}

void ROL_acc()
{
    debug_print("[%02X] ROL_acc \t", ROL_acc_);

    const bool orig_cf = CF;
    CF = ((A & 0x80) != 0);
    A <<= 0x01;
    if (orig_cf == true)
        A |= 0x01;
    else
        A &= ~(0x01);
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len;
}

void ROL_zp()
{
    debug_print("[%02X] ROL_zp \t", ROL_zp_);

    byte *ptr = ptr_zp_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    if (orig_cf == true)
        *ptr |= 0x01;
    else
        *ptr &= ~(0x01);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zp_len;
}

void ROL_zpx()
{
    debug_print("[%02X] ROL_zpx \t", ROL_zpx_);

    byte *ptr = ptr_zpx_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    if (orig_cf == true)
        *ptr |= 0x01;
    else
        *ptr &= ~(0x01);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zpx_len;
}

void ROL_abs()
{
    debug_print("[%02X] ROL_abs \t", ROL_abs_);

    byte *ptr = ptr_abs_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    if (orig_cf == true)
        *ptr |= 0x01;
    else
        *ptr &= ~(0x01);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + abs_len;
}

void ROL_absx()
{
    debug_print("[%02X] ROL_absx \t", ROL_absx_);

    byte *ptr = ptr_absx_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x80) != 0);
    *ptr <<= 0x01;
    if (orig_cf == true)
        *ptr |= 0x01;
    else
        *ptr &= ~(0x01);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + absx_len;
}

void ROR_acc()
{
    debug_print("[%02X] ROR_acc \t", ROR_acc_);

    const bool orig_cf = CF;
    CF = ((A & 0x01) != 0);
    A >>= 0x01;
    if (orig_cf == true)
        A |= 0x80;
    else
        A &= ~(0x80);
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len;
}

void ROR_zp()
{
    debug_print("[%02X] ROR_zp \t", ROR_zp_);

    byte *ptr = ptr_zp_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x01) != 0);
    *ptr >>= 0x01;
    if (orig_cf == true)
        *ptr |= 0x80;
    else
        *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zp_len;
}

void ROR_zpx()
{
    debug_print("[%02X] ROR_zpx \t", ROR_zpx_);

    byte *ptr = ptr_zpx_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x01) != 0);
    *ptr >>= 0x01;
    if (orig_cf == true)
        *ptr |= 0x80;
    else
        *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zpx_len;
}

void ROR_abs()
{
    debug_print("[%02X] ROR_abs \t", ROR_abs_);

    byte *ptr = ptr_abs_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x01) != 0);
    *ptr >>= 0x01;
    if (orig_cf == true)
        *ptr |= 0x80;
    else
        *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + abs_len;
}

void ROR_absx()
{
    debug_print("[%02X] ROR_absx \t", ROR_absx_);

    byte *ptr = ptr_absx_();
    const bool orig_cf = CF;
    CF = ((*ptr & 0x01) != 0);
    *ptr >>= 0x01;
    if (orig_cf == true)
        *ptr |= 0x80;
    else
        *ptr &= ~(0x80);
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + absx_len;
}

void INC_zp()
{
    debug_print("[%02X] INC_zp \t", INC_zp_);

    byte *ptr = ptr_zp_();
    *ptr += 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zp_len;
}

void INC_zpx()
{
    debug_print("[%02X] INC_zpx \t", INC_zpx_);

    byte *ptr = ptr_zpx_();
    *ptr += 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zpx_len;
}

void INC_abs()
{
    debug_print("[%02X] INC_abs \t", INC_abs_);

    byte *ptr = ptr_abs_();
    *ptr += 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + abs_len;
}

void INC_absx()
{
    debug_print("[%02X] INC_absx \t", INC_absx_);

    byte *ptr = ptr_absx_();
    *ptr += 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + absx_len;
}

void DEC_zp()
{
    debug_print("[%02X] DEC_zp \t", DEC_zp_);

    byte *ptr = ptr_zp_();
    *ptr -= 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zp_len;
}

void DEC_zpx()
{
    debug_print("[%02X] DEC_zpx \t", DEC_zpx_);

    byte *ptr = ptr_zpx_();
    *ptr -= 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + zpx_len;
}

void DEC_abs()
{
    debug_print("[%02X] DEC_abs \t", DEC_abs_);

    byte *ptr = ptr_abs_();
    *ptr -= 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + abs_len;
}

void DEC_absx()
{
    debug_print("[%02X] DEC_absx \t", DEC_absx_);

    byte *ptr = ptr_absx_();
    *ptr -= 1;
    ZF = (*ptr == 0);
    NF = ((sbyte)*ptr < 0);

    PC += instr_len + absx_len;
}

void LDX_imm()
{
    debug_print("[%02X] LDX_imm \t", LDX_imm_);

    X = imm_();
    ZF = (X == 0);
    NF = ((sbyte)X < 0);

    PC += instr_len + imm_len;
}

void LDX_zp()
{
    debug_print("[%02X] LDX_zp \t", LDX_zp_);

    X = zp_();
    ZF = (X == 0);
    NF = ((sbyte)X < 0);

    PC += instr_len + zp_len;
}

void LDX_zpy()
{
    debug_print("[%02X] LDX_zpy \t", LDX_zpy_);

    X = zpy_();
    ZF = (X == 0);
    NF = ((sbyte)X < 0);

    PC += instr_len + zpy_len;
}

void LDX_abs()
{
    debug_print("[%02X] LDX_abs \t", LDX_abs_);

    X = abs_();
    ZF = (X == 0);
    NF = ((sbyte)X < 0);

    PC += instr_len + abs_len;
}

void LDX_absy()
{
    debug_print("[%02X] LDX_absy \t", LDX_absy_);

    X = absy_();
    ZF = (X == 0);
    NF = ((sbyte)X < 0);

    PC += instr_len + absy_len;
}

void LDY_imm()
{
    debug_print("[%02X] LDY_imm \t", LDY_imm_);

    Y = imm_();
    ZF = (Y == 0);
    NF = ((sbyte)Y < 0);

    PC += instr_len + imm_len;
}

void LDY_zp()
{
    debug_print("[%02X] LDY_zp \t", LDY_zp_);

    Y = zp_();
    ZF = (Y == 0);
    NF = ((sbyte)Y < 0);

    PC += instr_len + zp_len;
}

void LDY_zpx()
{
    debug_print("[%02X] LDY_zpx \t", LDY_zpx_);

    Y = zpx_();
    ZF = (Y == 0);
    NF = ((sbyte)Y < 0);

    PC += instr_len + zpx_len;
}

void LDY_abs()
{
    debug_print("[%02X] LDY_abs \t", LDY_abs_);

    Y = abs_();
    ZF = (Y == 0);
    NF = ((sbyte)Y < 0);

    PC += instr_len + abs_len;
}

void LDY_absx()
{
    debug_print("[%02X] LDY_absx \t", LDY_absx_);

    Y = absx_();
    ZF = (Y == 0);
    NF = ((sbyte)Y < 0);

    PC += instr_len + absx_len;
}

void LDA_imm()
{
    debug_print("[%02X] LDA_imm \t", LDA_imm_);

    A = imm_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + imm_len;
}

void LDA_zp()
{
    debug_print("[%02X] LDA_zp \t", LDA_zp_);

    A = zp_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + zp_len;
}

void LDA_zpx()
{
    debug_print("[%02X] LDA_zpx \t", LDA_zpx_);

    A = zpx_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + zpx_len;
}

void LDA_abs()
{
    debug_print("[%02X] LDA_abs \t", LDA_abs_);

    A = abs_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + abs_len;
}

void LDA_absx()
{
    debug_print("[%02X] LDA_absx \t", LDA_absx_);

    A = absx_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + absx_len;
}

void LDA_absy()
{
    debug_print("[%02X] LDA_absy \t", LDA_absy_);

    A = absy_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + absy_len;
}

void LDA_indx()
{
    debug_print("[%02X] LDA_indx \t", LDA_indx_);

    A = indx_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + indx_len;
}

void LDA_ind_y()
{
    debug_print("[%02X] LDA_ind_y \t", LDA_ind_y_);

    A = ind_y_();
    ZF = (A == 0);
    NF = ((sbyte)A < 0);

    PC += instr_len + ind_y_len;
}

void STA_zp()
{
    debug_print("[%02X] STA_zp \t", STA_zp_);

    byte *ptr = ptr_zp_();
    *ptr = A;

    PC += instr_len + zp_len;
}

void STA_zpx()
{
    debug_print("[%02X] STA_zpx \t", STA_zpx_);

    byte *ptr = ptr_zpx_();
    *ptr = A;

    PC += instr_len + zpx_len;
}

void STA_abs()
{
    debug_print("[%02X] STA_abs \t", STA_abs_);

    byte *ptr = ptr_abs_();
    *ptr = A;

    PC += instr_len + abs_len;
}

void STA_absx()
{
    debug_print("[%02X] STA_absx \t", STA_absx_);

    byte *ptr = ptr_absx_();
    *ptr = A;

    PC += instr_len + absx_len;
}

void STA_absy()
{
    debug_print("[%02X] STA_absy \t", STA_absy_);

    byte *ptr = ptr_absy_();
    *ptr = A;

    PC += instr_len + absy_len;
}

void STA_indx()
{
    debug_print("[%02X] STA_indx \t", STA_indx_);

    byte *ptr = ptr_indx_();
    *ptr = A;

    PC += instr_len + indx_len;
}

void STA_ind_y()
{
    debug_print("[%02X] STA_ind_y \t", STA_ind_y_);

    byte *ptr = ptr_ind_y_();
    *ptr = A;

    PC += instr_len + ind_y_len;
}

void STX_zp()
{
    debug_print("[%02X] STX_zp \t", STX_zp_);

    byte *ptr = ptr_zp_();
    *ptr = X;

    PC += instr_len + zp_len;
}

void STX_zpy()
{
    debug_print("[%02X] STX_zpy \t", STX_zpy_);

    byte *ptr = ptr_zpy_();
    *ptr = X;

    PC += instr_len + zpy_len;
}

void STX_abs()
{
    debug_print("[%02X] STX_abs \t", STX_abs_);

    byte *ptr = ptr_abs_();
    *ptr = X;

    PC += instr_len + abs_len;
}

void STY_zp()
{
    debug_print("[%02X] STY_zp \t", STY_zp_);

    byte *ptr = ptr_zp_();
    *ptr = Y;

    PC += instr_len + zp_len;
}

void STY_zpx()
{
    debug_print("[%02X] STY_zpx \t", STY_zpx_);

    byte *ptr = ptr_zpx_();
    *ptr = Y;

    PC += instr_len + zpx_len;
}

void STY_abs()
{
    debug_print("[%02X] STY_abs \t", STY_abs_);

    byte *ptr = ptr_abs_();
    *ptr = Y;

    PC += instr_len + abs_len;
}

#endif //INSTRUCTIONS_H
