#ifndef TEST_H
#define TEST_H

#include "cpu.h"
#include "memory.h"
#include "debug.h"

#define TEST_START_PRINT() print("running %s ", __func__);
#define TEST_SUCCESS_PRINT() print("[SUCCESS]\n");
#define TEST_FAIL_PRINT() print("[FAIL]\n");
#define TEST_SUMMARY_START_PRINT() print("running unit tests\n");
#define TEST_SUMMARY_SUCCESS_PRINT() print("test summary [SUCCESS]\n");
#define TEST_SUMMARY_FAIL_PRINT() print("test summary [FAIL]\n");
#define TEST_START(x) bool test_##x() { TEST_START_PRINT();
#define TEST_FAIL() { TEST_FAIL_PRINT(); return false; }
#define TEST_SUCCESS() { TEST_SUCCESS_PRINT();  return true; }
#define TEST_END() TEST_SUCCESS(); }
#define TEST_SUMMARY_START() bool run_tests() { TEST_SUMMARY_START_PRINT();
#define TEST_SUMMARY_FAIL() { TEST_SUMMARY_FAIL_PRINT();  return false; }
#define TEST_SUMMARY_SUCCESS() { TEST_SUMMARY_SUCCESS_PRINT();  return true; }
#define TEST_SUMMARY_END() TEST_SUMMARY_SUCCESS(); }
#define TEST_RUN(x) { initialize(); if (!test_##x()) TEST_SUMMARY_FAIL(); }
#define ASSERT(x) if(!(x)) TEST_FAIL();

const byte test_byte = 0xBE;
const byte test_byte_offset = 0x02;
const byte test_zp_addr = 0x23;
const byte test_x_offset = 0x04;
const byte test_y_offset = 0x07;
const word test_addr = 0x2324;
const byte test_x_addr_offset = 0x02;
const byte test_y_addr_offset = 0x04;
const word test_init_pc = 0x1000;

TEST_START(NOP);
    const word PC_  = PC;
    const byte SP_  = SP;
    const byte A_   = A;
    const byte X_   = X;
    const byte Y_   = Y;
    const bool CF_  = CF;
    const bool ZF_  = ZF;
    const bool ID_  = ID;
    const bool DM_  = DM;
    const bool BC_  = BC;
    const bool OVF_ = OVF;
    const bool NF_  = NF;

    RAM[0x0000] = NOP_;
    execute();

    ASSERT(PC == PC_ + 1);
    ASSERT(SP == SP_);
    ASSERT(A == A_);
    ASSERT(X == X_);
    ASSERT(Y == Y_);
    ASSERT(CF == CF_);
    ASSERT(ZF == ZF_);
    ASSERT(ID == ID_);
    ASSERT(DM == DM_);
    ASSERT(BC == BC_);
    ASSERT(OVF == OVF_);
    ASSERT(NF == NF_);
TEST_END();

TEST_START(TXS);
    X = test_byte;
    RAM[0x0000] = TXS_;
    execute();

    ASSERT(SP == test_byte);
TEST_END();

TEST_START(TSX);
    SP = test_byte;
    RAM[0x0000] = TSX_;
    execute();

    ASSERT(X == test_byte);
TEST_END();

TEST_START(PHA);
    A = test_byte;
    SP = 0x12;
    RAM[0x0000] = PHA_;
    execute();

    ASSERT(RAM[0x0100 | SP] == test_byte);
TEST_END();

TEST_START(PLA);
    SP=0x12;
    RAM[0x0100 | SP] =  test_byte;
    RAM[0x0000] = PLA_;
    execute();

    ASSERT(A == test_byte);
TEST_END();

TEST_START(PHP);
    set_PS(0b11011111);
    RAM[0x0000] = PHP_;
    execute();

    ASSERT(RAM[0x0100 | SP] == get_PS());

    set_PS(0b01010101);
    RAM[0x0001] = PHP_;
    execute();

    ASSERT(RAM[0x0100 | SP] == get_PS());

    set_PS(0b00100000);
    RAM[0x0002] = PHP_;
    execute();

    ASSERT(RAM[0x0100 | SP] == 0b00000000);
    ASSERT(RAM[0x0100 | SP] == get_PS());
TEST_END();

TEST_START(PLP);
    const byte test_byte_ps = 0b10010101;
    set_PS(test_byte_ps);
    RAM[0x0000] = PHP_;
    execute();

    ASSERT(RAM[0x0100 | SP] == get_PS());

    set_PS(0b00000000);
    RAM[0x0001] = PLP_;
    execute();

    ASSERT(get_PS() == test_byte_ps);
TEST_END();

TEST_START(TAX);
    A = test_byte;
    RAM[0x0000] = TAX_;
    execute();

    ASSERT(X == test_byte);
TEST_END();

TEST_START(TXA);
    X = test_byte;
    RAM[0x0000] = TXA_;
    execute();

    ASSERT(A == test_byte);
TEST_END();

TEST_START(DEX);
    X = test_byte;
    RAM[0x0000] = DEX_;
    execute();

    ASSERT(X == (test_byte - 1));
TEST_END();

TEST_START(INX);
    X = test_byte;
    RAM[0x0000] = INX_;
    execute();

    ASSERT(X == (test_byte + 1));
TEST_END();

TEST_START(TAY);
    A = test_byte;
    RAM[0x0000] = TAY_;
    execute();

    ASSERT(Y == test_byte);
TEST_END();

TEST_START(TYA);
    Y = test_byte;
    RAM[0x0000] = TYA_;
    execute();

    ASSERT(A == test_byte);
TEST_END();

TEST_START(DEY);
    Y = test_byte;
    RAM[0x0000] = DEY_;
    execute();

    ASSERT(Y == (test_byte - 1));
TEST_END();

TEST_START(INY);
    Y = test_byte;
    RAM[0x0000] = INY_;
    execute();

    ASSERT(Y == (test_byte + 1));
TEST_END();

TEST_START(CLC);
    CF = true;
    RAM[0x0000] = CLC_;
    execute();

    ASSERT(CF == false);
TEST_END();

TEST_START(SEC);
    CF = false;
    RAM[0x0000] = SEC_;
    execute();

    ASSERT(CF == true);
TEST_END();

TEST_START(CLI);
    ID = true;
    RAM[0x0000] = CLI_;
    execute();

    ASSERT(ID == false);
TEST_END();

TEST_START(SEI);
    ID = false;
    RAM[0x0000] = SEI_;
    execute();

    ASSERT(ID == true);
TEST_END();

TEST_START(CLV);
    OVF = true;
    RAM[0x0000] = CLV_;
    execute();

    ASSERT(OVF == false);
TEST_END();

TEST_START(CLD);
    DM = true;
    RAM[0x0000] = CLD_;
    execute();

    ASSERT(DM == false);
TEST_END();

TEST_START(SED);
    DM = false;
    RAM[0x0000] = SED_;
    execute();

    ASSERT(DM == true);
TEST_END();

TEST_START(BPL);
    NF = false;
    const sbyte rel_dest = 0x10;
    RAM[0x0000] = BPL_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));

    NF = true;
    RAM[0x0012] = BPL_;
    RAM[0x0013] = rel_dest;
    execute();

    ASSERT(PC == (0x0014));
TEST_END();

TEST_START(BMI);
    NF = true;
    const sbyte rel_dest = -0x02;
    RAM[0x0000] = BMI_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));
TEST_END();

TEST_START(BVC);
    OVF = false;
    const sbyte rel_dest = 0x33;
    RAM[0x0000] = BVC_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));
TEST_END();

TEST_START(BVS);
    OVF = true;
    const sbyte rel_dest = 0x33;
    RAM[0x0000] = BVS_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));
TEST_END();

TEST_START(BCC);
    CF = false;
    const sbyte rel_dest = 0x33;
    RAM[0x0000] = BCC_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));
TEST_END();

TEST_START(BCS);
    CF = true;
    const sbyte rel_dest = 0x33;
    RAM[0x0000] = BCS_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));
TEST_END();

TEST_START(BNE);
    ZF = false;
    const sbyte rel_dest = 0x33;
    RAM[0x0000] = BNE_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));
TEST_END();

TEST_START(BEQ);
    ZF = true;
    const sbyte rel_dest = 0x33;
    RAM[0x0000] = BEQ_;
    RAM[0x0001] = rel_dest;
    execute();

    ASSERT(PC == (0x0002 + rel_dest));
TEST_END();

TEST_START(CMP_imm);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_imm_;
    RAM[test_init_pc + 0x0001] = test_byte + test_byte_offset;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_imm_;
    RAM[test_init_pc + 0x0001] = test_byte;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_imm_;
    RAM[test_init_pc + 0x0001] = test_byte - test_byte_offset;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CMP_zp);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_zp_addr] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_zp_addr] = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_zp_addr] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CMP_zpx);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_offset;
    RAM[test_zp_addr + test_x_offset] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_zpx_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_offset;
    RAM[test_zp_addr + test_x_offset] = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_zpx_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_offset;
    RAM[test_zp_addr + test_x_offset] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_zpx_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CMP_abs);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_addr] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_addr] = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    RAM[test_addr] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CMP_absx);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_offset;
    RAM[test_addr + test_x_offset] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_absx_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_offset;
    RAM[test_addr + test_x_offset] = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_absx_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_offset;
    RAM[test_addr + test_x_offset] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_absx_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CMP_absy);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    Y = test_y_offset;
    RAM[test_addr + test_y_offset] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_absy_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    Y = test_y_offset;
    RAM[test_addr + test_y_offset] = test_byte;
    RAM[test_init_pc + 0x0000] = CMP_absy_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    Y = test_y_offset;
    RAM[test_addr + test_y_offset] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CMP_absy_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CMP_indx);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_addr_offset;
    RAM[test_addr] = test_byte + test_byte_offset;
    write_word(test_addr,
                    test_zp_addr + test_x_addr_offset);
    RAM[test_init_pc + 0x0000] = CMP_indx_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_addr_offset;
    RAM[test_addr] = test_byte;
    write_word(test_addr,
                    test_zp_addr + test_x_addr_offset);
    RAM[test_init_pc + 0x0000] = CMP_indx_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    X = test_x_addr_offset;
    RAM[test_addr] = test_byte - test_byte_offset;
    write_word(test_addr,
                    test_zp_addr + test_x_addr_offset);
    RAM[test_init_pc + 0x0000] = CMP_indx_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CMP_ind_y);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    Y = test_y_addr_offset;
    RAM[test_addr + test_y_addr_offset] = test_byte + test_byte_offset;
    write_word(test_addr,
                    test_zp_addr);
    RAM[test_init_pc + 0x0000] = CMP_ind_y_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    Y = test_y_addr_offset;
    RAM[test_addr + test_y_addr_offset] = test_byte;
    write_word(test_addr,
                    test_zp_addr);
    RAM[test_init_pc + 0x0000] = CMP_ind_y_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    A = test_byte;
    Y = test_y_addr_offset;
    RAM[test_addr + test_y_addr_offset] = test_byte - test_byte_offset;
    write_word(test_addr,
                    test_zp_addr);
    RAM[test_init_pc + 0x0000] = CMP_ind_y_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CPX_imm_);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_init_pc + 0x0000] = CPX_imm_;
    RAM[test_init_pc + 0x0001] = test_byte + test_byte_offset;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_init_pc + 0x0000] = CPX_imm_;
    RAM[test_init_pc + 0x0001] = test_byte;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_init_pc + 0x0000] = CPX_imm_;
    RAM[test_init_pc + 0x0001] = test_byte - test_byte_offset;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CPX_zp_);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_zp_addr] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPX_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_zp_addr] = test_byte;
    RAM[test_init_pc + 0x0000] = CPX_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_zp_addr] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPX_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CPX_abs_);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_addr] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPX_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_addr] = test_byte;
    RAM[test_init_pc + 0x0000] = CPX_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    X = test_byte;
    RAM[test_addr] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPX_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CPY_imm_);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_init_pc + 0x0000] = CPY_imm_;
    RAM[test_init_pc + 0x0001] = test_byte + test_byte_offset;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_init_pc + 0x0000] = CPY_imm_;
    RAM[test_init_pc + 0x0001] = test_byte;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_init_pc + 0x0000] = CPY_imm_;
    RAM[test_init_pc + 0x0001] = test_byte - test_byte_offset;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CPY_zp_);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_zp_addr] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPY_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_zp_addr] = test_byte;
    RAM[test_init_pc + 0x0000] = CPY_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_zp_addr] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPY_zp_;
    RAM[test_init_pc + 0x0001] = test_zp_addr;
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(CPY_abs_);
    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_addr] = test_byte + test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPY_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 1);
    ASSERT(ZF == 0);
    ASSERT(CF == 0);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_addr] = test_byte;
    RAM[test_init_pc + 0x0000] = CPY_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 1);
    ASSERT(CF == 1);

    PC = test_init_pc;
    NF = false;
    ZF = false;
    CF = false;
    Y = test_byte;
    RAM[test_addr] = test_byte - test_byte_offset;
    RAM[test_init_pc + 0x0000] = CPY_abs_;
    write_word(test_addr, test_init_pc + 0x0001);
    execute();

    ASSERT(NF == 0);
    ASSERT(ZF == 0);
    ASSERT(CF == 1);
TEST_END();

TEST_START(BIT_zp_);
TEST_END();

TEST_START(BIT_abs_);
TEST_END();

TEST_START(JMP_abs_);
TEST_END();

TEST_START(JMP_ind_);
TEST_END();

TEST_START(JSR_);
TEST_END();

TEST_START(RTS_);
TEST_END();

TEST_START(BRK_);
TEST_END();

TEST_START(RTI_);
TEST_END();

TEST_START(ADC_imm_);
TEST_END();

TEST_START(ADC_zp_);
TEST_END();

TEST_START(ADC_zpx_);
TEST_END();

TEST_START(ADC_abs_);
TEST_END();

TEST_START(ADC_absx_);
TEST_END();

TEST_START(ADC_absy_);
TEST_END();

TEST_START(ADC_indx_);
TEST_END();

TEST_START(ADC_ind_y_);
TEST_END();

TEST_START(SUB_imm_);
TEST_END();

TEST_START(SUB_zp_);
TEST_END();

TEST_START(SUB_zpx_);
TEST_END();

TEST_START(SUB_abs_);
TEST_END();

TEST_START(SUB_absx_);
TEST_END();

TEST_START(SUB_absy_);
TEST_END();

TEST_START(SUB_indx_);
TEST_END();

TEST_START(SUB_ind_y_);
TEST_END();

TEST_START(AND_imm_);
TEST_END();

TEST_START(AND_zp_);
TEST_END();

TEST_START(AND_zpx_);
TEST_END();

TEST_START(AND_abs_);
TEST_END();

TEST_START(AND_absx_);
TEST_END();

TEST_START(AND_absy_);
TEST_END();

TEST_START(AND_indx_);
TEST_END();

TEST_START(AND_ind_y_);
TEST_END();

TEST_START(ORA_imm_);
TEST_END();

TEST_START(ORA_zp_);
TEST_END();

TEST_START(ORA_zpx_);
TEST_END();

TEST_START(ORA_abs_);
TEST_END();

TEST_START(ORA_absx_);
TEST_END();

TEST_START(ORA_absy_);
TEST_END();

TEST_START(ORA_indx_);
TEST_END();

TEST_START(ORA_ind_y_);
TEST_END();

TEST_START(EOR_imm_);
TEST_END();

TEST_START(EOR_zp_);
TEST_END();

TEST_START(EOR_zpx_);
TEST_END();

TEST_START(EOR_abs_);
TEST_END();

TEST_START(EOR_absx_);
TEST_END();

TEST_START(EOR_absy_);
TEST_END();

TEST_START(EOR_indx_);
TEST_END();

TEST_START(EOR_ind_y_);
TEST_END();

TEST_START(ASL_acc_);
TEST_END();

TEST_START(ASL_zp_);
TEST_END();

TEST_START(ASL_zpx_);
TEST_END();

TEST_START(ASL_abs_);
TEST_END();

TEST_START(ASL_absx_);
TEST_END();

TEST_START(LSR_acc_);
TEST_END();

TEST_START(LSR_zp_);
TEST_END();

TEST_START(LSR_zpx_);
TEST_END();

TEST_START(LSR_abs_);
TEST_END();

TEST_START(LSR_absx_);
TEST_END();

TEST_START(ROL_acc_);
TEST_END();

TEST_START(ROL_zp_);
TEST_END();

TEST_START(ROL_zpx_);
TEST_END();

TEST_START(ROL_abs_);
TEST_END();

TEST_START(ROL_absx_);
TEST_END();

TEST_START(ROR_acc_);
TEST_END();

TEST_START(ROR_zp_);
TEST_END();

TEST_START(ROR_zpx_);
TEST_END();

TEST_START(ROR_abs_);
TEST_END();

TEST_START(ROR_absx_);
TEST_END();

TEST_START(INC_zp_);
TEST_END();

TEST_START(INC_zpx_);
TEST_END();

TEST_START(INC_abs_);
TEST_END();

TEST_START(INC_absx_);
TEST_END();

TEST_START(DEC_zp_);
TEST_END();

TEST_START(DEC_zpx_);
TEST_END();

TEST_START(DEC_abs_);
TEST_END();

TEST_START(DEC_absx_);
TEST_END();

TEST_START(LDX_imm_);
TEST_END();

TEST_START(LDX_zp_);
TEST_END();

TEST_START(LDX_zpy_);
TEST_END();

TEST_START(LDX_abs_);
TEST_END();

TEST_START(LDX_absy_);
TEST_END();

TEST_START(LDY_imm_);
TEST_END();

TEST_START(LDY_zp_);
TEST_END();

TEST_START(LDY_zpx_);
TEST_END();

TEST_START(LDY_abs_);
TEST_END();

TEST_START(LDY_absx_);
TEST_END();

TEST_START(LDA_imm_);
TEST_END();

TEST_START(LDA_zp_);
TEST_END();

TEST_START(LDA_zpx_);
TEST_END();

TEST_START(LDA_abs_);
TEST_END();

TEST_START(LDA_absx_);
TEST_END();

TEST_START(LDA_absy_);
TEST_END();

TEST_START(LDA_indx_);
TEST_END();

TEST_START(LDA_ind_y_);
TEST_END();

TEST_START(STA_zp_);
TEST_END();

TEST_START(STA_zpx_);
TEST_END();

TEST_START(STA_abs_);
TEST_END();

TEST_START(STA_absx_);
TEST_END();

TEST_START(STA_absy_);
TEST_END();

TEST_START(STA_indx_);
TEST_END();

TEST_START(STA_ind_y_);
TEST_END();

TEST_START(STX_zp_);
TEST_END();

TEST_START(STX_zpy_);
TEST_END();

TEST_START(STX_abs_);
TEST_END();

TEST_START(STY_zp_);
TEST_END();

TEST_START(STY_zpx_);
TEST_END();

TEST_START(STY_abs_);
TEST_END();

TEST_SUMMARY_START();
    TEST_RUN(NOP);
    TEST_RUN(TXS);
    TEST_RUN(TSX);
    TEST_RUN(PHA);
    TEST_RUN(PLA);
    TEST_RUN(PHP);
    TEST_RUN(PLP);
    TEST_RUN(TAX);
    TEST_RUN(TXA);
    TEST_RUN(DEX);
    TEST_RUN(INX);
    TEST_RUN(TAY);
    TEST_RUN(TYA);
    TEST_RUN(DEY);
    TEST_RUN(INY);
    TEST_RUN(CLC);
    TEST_RUN(SEC);
    TEST_RUN(CLI);
    TEST_RUN(SEI);
    TEST_RUN(CLV);
    TEST_RUN(CLD);
    TEST_RUN(SED);
    TEST_RUN(BPL);
    TEST_RUN(BMI);
    TEST_RUN(BVC);
    TEST_RUN(BVS);
    TEST_RUN(BCC);
    TEST_RUN(BCS);
    TEST_RUN(BNE);
    TEST_RUN(BEQ);
    TEST_RUN(CMP_imm);
    TEST_RUN(CMP_zp);
    TEST_RUN(CMP_zpx);
    TEST_RUN(CMP_abs);
    TEST_RUN(CMP_absx);
    TEST_RUN(CMP_absy);
    TEST_RUN(CMP_indx);
    TEST_RUN(CMP_ind_y);
    TEST_RUN(CPX_imm_);
    TEST_RUN(CPX_zp_);
    TEST_RUN(CPX_abs_);
    TEST_RUN(CPY_imm_);
    TEST_RUN(CPY_zp_);
    TEST_RUN(CPY_abs_);
    TEST_RUN(BIT_zp_);
    TEST_RUN(BIT_abs_);
    TEST_RUN(JMP_abs_);
    TEST_RUN(JMP_ind_);
    TEST_RUN(JSR_);
    TEST_RUN(RTS_);
    TEST_RUN(BRK_);
    TEST_RUN(RTI_);
    TEST_RUN(ADC_imm_);
    TEST_RUN(ADC_zp_);
    TEST_RUN(ADC_zpx_);
    TEST_RUN(ADC_abs_);
    TEST_RUN(ADC_absx_);
    TEST_RUN(ADC_absy_);
    TEST_RUN(ADC_indx_);
    TEST_RUN(ADC_ind_y_);
    TEST_RUN(SUB_imm_);
    TEST_RUN(SUB_zp_);
    TEST_RUN(SUB_zpx_);
    TEST_RUN(SUB_abs_);
    TEST_RUN(SUB_absx_);
    TEST_RUN(SUB_absy_);
    TEST_RUN(SUB_indx_);
    TEST_RUN(SUB_ind_y_);
    TEST_RUN(AND_imm_);
    TEST_RUN(AND_zp_);
    TEST_RUN(AND_zpx_);
    TEST_RUN(AND_abs_);
    TEST_RUN(AND_absx_);
    TEST_RUN(AND_absy_);
    TEST_RUN(AND_indx_);
    TEST_RUN(AND_ind_y_);
    TEST_RUN(ORA_imm_);
    TEST_RUN(ORA_zp_);
    TEST_RUN(ORA_zpx_);
    TEST_RUN(ORA_abs_);
    TEST_RUN(ORA_absx_);
    TEST_RUN(ORA_absy_);
    TEST_RUN(ORA_indx_);
    TEST_RUN(ORA_ind_y_);
    TEST_RUN(EOR_imm_);
    TEST_RUN(EOR_zp_);
    TEST_RUN(EOR_zpx_);
    TEST_RUN(EOR_abs_);
    TEST_RUN(EOR_absx_);
    TEST_RUN(EOR_absy_);
    TEST_RUN(EOR_indx_);
    TEST_RUN(EOR_ind_y_);
    TEST_RUN(ASL_acc_);
    TEST_RUN(ASL_zp_);
    TEST_RUN(ASL_zpx_);
    TEST_RUN(ASL_abs_);
    TEST_RUN(ASL_absx_);
    TEST_RUN(LSR_acc_);
    TEST_RUN(LSR_zp_);
    TEST_RUN(LSR_zpx_);
    TEST_RUN(LSR_abs_);
    TEST_RUN(LSR_absx_);
    TEST_RUN(ROL_acc_);
    TEST_RUN(ROL_zp_);
    TEST_RUN(ROL_zpx_);
    TEST_RUN(ROL_abs_);
    TEST_RUN(ROL_absx_);
    TEST_RUN(ROR_acc_);
    TEST_RUN(ROR_zp_);
    TEST_RUN(ROR_zpx_);
    TEST_RUN(ROR_abs_);
    TEST_RUN(ROR_absx_);
    TEST_RUN(INC_zp_);
    TEST_RUN(INC_zpx_);
    TEST_RUN(INC_abs_);
    TEST_RUN(INC_absx_);
    TEST_RUN(DEC_zp_);
    TEST_RUN(DEC_zpx_);
    TEST_RUN(DEC_abs_);
    TEST_RUN(DEC_absx_);
    TEST_RUN(LDX_imm_);
    TEST_RUN(LDX_zp_);
    TEST_RUN(LDX_zpy_);
    TEST_RUN(LDX_abs_);
    TEST_RUN(LDX_absy_);
    TEST_RUN(LDY_imm_);
    TEST_RUN(LDY_zp_);
    TEST_RUN(LDY_zpx_);
    TEST_RUN(LDY_abs_);
    TEST_RUN(LDY_absx_);
    TEST_RUN(LDA_imm_);
    TEST_RUN(LDA_zp_);
    TEST_RUN(LDA_zpx_);
    TEST_RUN(LDA_abs_);
    TEST_RUN(LDA_absx_);
    TEST_RUN(LDA_absy_);
    TEST_RUN(LDA_indx_);
    TEST_RUN(LDA_ind_y_);
    TEST_RUN(STA_zp_);
    TEST_RUN(STA_zpx_);
    TEST_RUN(STA_abs_);
    TEST_RUN(STA_absx_);
    TEST_RUN(STA_absy_);
    TEST_RUN(STA_indx_);
    TEST_RUN(STA_ind_y_);
    TEST_RUN(STX_zp_);
    TEST_RUN(STX_zpy_);
    TEST_RUN(STX_abs_);
    TEST_RUN(STY_zp_);
    TEST_RUN(STY_zpx_);
    TEST_RUN(STY_abs_);
TEST_SUMMARY_END();

#endif //TEST_H
