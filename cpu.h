#ifndef CPU_H
#define CPU_H

#include "debug.h"
#include "types.h"
#include "memory.h"
#include "monitor.h"
#include "opcodes.h"
#include "instructions.h"
#include <unistd.h>

void debug_print_registers()
{
    debug_print("[");
    debug_print("PC:%04X ", PC);
    debug_print("SP:%02X ", SP);
    debug_print("A:%02X ", A);
    debug_print("X:%02X ", X);
    debug_print("Y:%02X ", Y);
    debug_print("| CF:%d ", CF);
    debug_print("ZF:%d ", ZF);
    debug_print("ID:%d ", ID);
    debug_print("DM:%d ", DM);
    debug_print("BC:%d ", BC);
    debug_print("OVF:%d ", OVF);
    debug_print("NF:%d", NF);
    debug_print("] \n");
}

const bool execute()
{
    bool retcode = true;

    switch (RAM[PC]) {
        case NOP_:
            NOP();
            break;
        case TXS_:
            TXS();
            break;
        case TSX_:
            TSX();
            break;
        case PHA_:
            PHA();
            break;
        case PLA_:
            PLA();
            break;
        case PHP_:
            PHP();
            break;
        case PLP_:
            PLP();
            break;
        case TAX_:
            TAX();
            break;
        case TXA_:
            TXA();
            break;
        case DEX_:
            DEX();
            break;
        case INX_:
            INX();
            break;
        case TAY_:
            TAY();
            break;
        case TYA_:
            TYA();
            break;
        case DEY_:
            DEY();
            break;
        case INY_:
            INY();
            break;
        case CLC_:
            CLC();
            break;
        case SEC_:
            SEC();
            break;
        case CLI_:
            CLI();
            break;
        case SEI_:
            SEI();
            break;
        case CLV_:
            CLV();
            break;
        case CLD_:
            CLD();
            break;
        case SED_:
            SED();
            break;
        case BPL_:
            BPL();
            break;
        case BMI_:
            BMI();
            break;
        case BVC_:
            BVC();
            break;
        case BVS_:
            BVS();
            break;
        case BCC_:
            BCC();
            break;
        case BCS_:
            BCS();
            break;
        case BNE_:
            BNE();
            break;
        case BEQ_:
            BEQ();
            break;
        case CMP_imm_:
            CMP_imm();
            break;
        case CMP_zp_:
            CMP_zp();
            break;
        case CMP_zpx_:
            CMP_zpx();
            break;
        case CMP_abs_:
            CMP_abs();
            break;
        case CMP_absx_:
            CMP_absx();
            break;
        case CMP_absy_:
            CMP_absy();
            break;
        case CMP_indx_:
            CMP_indx();
            break;
        case CMP_ind_y_:
            CMP_ind_y();
            break;
        case CPX_imm_:
            CPX_imm();
            break;
        case CPX_zp_:
            CPX_zp();
            break;
        case CPX_abs_:
            CPX_abs();
            break;
        case CPY_imm_:
            CPY_imm();
            break;
        case CPY_zp_:
            CPY_zp();
            break;
        case CPY_abs_:
            CPY_abs();
            break;
        case BIT_zp_:
            BIT_zp();
            break;
        case BIT_abs_:
            BIT_abs();
            break;
        case JMP_abs_:
            JMP_abs();
            break;
        case JMP_ind_:
            JMP_ind();
            break;
        case JSR_:
            JSR();
            break;
        case RTS_:
            RTS();
            break;
        case BRK_:
            BRK();
            break;
        case RTI_:
            RTI();
            break;
        case ADC_imm_:
            ADC_imm();
            break;
        case ADC_zp_:
            ADC_zp();
            break;
        case ADC_zpx_:
            ADC_zpx();
            break;
        case ADC_abs_:
            ADC_abs();
            break;
        case ADC_absx_:
            ADC_absx();
            break;
        case ADC_absy_:
            ADC_absy();
            break;
        case ADC_indx_:
            ADC_indx();
            break;
        case ADC_ind_y_:
            ADC_ind_y();
            break;
        case SBC_imm_:
            SBC_imm();
            break;
        case SBC_zp_:
            SBC_zp();
            break;
        case SBC_zpx_:
            SBC_zpx();
            break;
        case SBC_abs_:
            SBC_abs();
            break;
        case SBC_absx_:
            SBC_absx();
            break;
        case SBC_absy_:
            SBC_absy();
            break;
        case SBC_indx_:
            SBC_indx();
            break;
        case SBC_ind_y_:
            SBC_ind_y();
            break;
        case AND_imm_:
            AND_imm();
            break;
        case AND_zp_:
            AND_zp();
            break;
        case AND_zpx_:
            AND_zpx();
            break;
        case AND_abs_:
            AND_abs();
            break;
        case AND_absx_:
            AND_absx();
            break;
        case AND_absy_:
            AND_absy();
            break;
        case AND_indx_:
            AND_indx();
            break;
        case AND_ind_y_:
            AND_ind_y();
            break;
        case ORA_imm_:
            ORA_imm();
            break;
        case ORA_zp_:
            ORA_zp();
            break;
        case ORA_zpx_:
            ORA_zpx();
            break;
        case ORA_abs_:
            ORA_abs();
            break;
        case ORA_absx_:
            ORA_absx();
            break;
        case ORA_absy_:
            ORA_absy();
            break;
        case ORA_indx_:
            ORA_indx();
            break;
        case ORA_ind_y_:
            ORA_ind_y();
            break;
        case EOR_imm_:
            EOR_imm();
            break;
        case EOR_zp_:
            EOR_zp();
            break;
        case EOR_zpx_:
            EOR_zpx();
            break;
        case EOR_abs_:
            EOR_abs();
            break;
        case EOR_absx_:
            EOR_absx();
            break;
        case EOR_absy_:
            EOR_absy();
            break;
        case EOR_indx_:
            EOR_indx();
            break;
        case EOR_ind_y_:
            EOR_ind_y();
            break;
        case ASL_acc_:
            ASL_acc();
            break;
        case ASL_zp_:
            ASL_zp();
            break;
        case ASL_zpx_:
            ASL_zpx();
            break;
        case ASL_abs_:
            ASL_abs();
            break;
        case ASL_absx_:
            ASL_absx();
            break;
        case LSR_acc_:
            LSR_acc();
            break;
        case LSR_zp_:
            LSR_zp();
            break;
        case LSR_zpx_:
            LSR_zpx();
            break;
        case LSR_abs_:
            LSR_abs();
            break;
        case LSR_absx_:
            LSR_absx();
            break;
        case ROL_acc_:
            ROL_acc();
            break;
        case ROL_zp_:
            ROL_zp();
            break;
        case ROL_zpx_:
            ROL_zpx();
            break;
        case ROL_abs_:
            ROL_abs();
            break;
        case ROL_absx_:
            ROL_absx();
            break;
        case ROR_acc_:
            ROR_acc();
            break;
        case ROR_zp_:
            ROR_zp();
            break;
        case ROR_zpx_:
            ROR_zpx();
            break;
        case ROR_abs_:
            ROR_abs();
            break;
        case ROR_absx_:
            ROR_absx();
            break;
        case INC_zp_:
            INC_zp();
            break;
        case INC_zpx_:
            INC_zpx();
            break;
        case INC_abs_:
            INC_abs();
            break;
        case INC_absx_:
            INC_absx();
            break;
        case DEC_zp_:
            DEC_zp();
            break;
        case DEC_zpx_:
            DEC_zpx();
            break;
        case DEC_abs_:
            DEC_abs();
            break;
        case DEC_absx_:
            DEC_absx();
            break;
        case LDX_imm_:
            LDX_imm();
            break;
        case LDX_zp_:
            LDX_zp();
            break;
        case LDX_zpy_:
            LDX_zpy();
            break;
        case LDX_abs_:
            LDX_abs();
            break;
        case LDX_absy_:
            LDX_absy();
            break;
        case LDY_imm_:
            LDY_imm();
            break;
        case LDY_zp_:
            LDY_zp();
            break;
        case LDY_zpx_:
            LDY_zpx();
            break;
        case LDY_abs_:
            LDY_abs();
            break;
        case LDY_absx_:
            LDY_absx();
            break;
        case LDA_imm_:
            LDA_imm();
            break;
        case LDA_zp_:
            LDA_zp();
            break;
        case LDA_zpx_:
            LDA_zpx();
            break;
        case LDA_abs_:
            LDA_abs();
            break;
        case LDA_absx_:
            LDA_absx();
            break;
        case LDA_absy_:
            LDA_absy();
            break;
        case LDA_indx_:
            LDA_indx();
            break;
        case LDA_ind_y_:
            LDA_ind_y();
            break;
        case STA_zp_:
            STA_zp();
            break;
        case STA_zpx_:
            STA_zpx();
            break;
        case STA_abs_:
            STA_abs();
            break;
        case STA_absx_:
            STA_absx();
            break;
        case STA_absy_:
            STA_absy();
            break;
        case STA_indx_:
            STA_indx();
            break;
        case STA_ind_y_:
            STA_ind_y();
            break;
        case STX_zp_:
            STX_zp();
            break;
        case STX_zpy_:
            STX_zpy();
            break;
        case STX_abs_:
            STX_abs();
            break;
        case STY_zp_:
            STY_zp();
            break;
        case STY_zpx_:
            STY_zpx();
            break;
        case STY_abs_:
            STY_abs();
            break;
        default:
            debug_print("[%02X] UNKNOWN ", RAM[PC]);
            retcode = false;
            break;
    };
    debug_print_registers();

    usleep(INSTR_DELAY_US);

    return retcode;
}

void initialize()
{
    init_CPU();
    init_PC();
    init_RAM();
}

void run()
{
    debug_print("INITIAL STATE\t");
    debug_print_registers();

    do {
        draw_monitor();
    } while (execute() != false);

    print("execution stopped\n");
}

#endif //CPU_H
