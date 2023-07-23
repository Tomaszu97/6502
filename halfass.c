#include "types.h"
#include "opcodes.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define CMD_BUF_SIZE 1024
#define INSTR_BUF_SIZE 32
#define INSTR_FMT "%31s %02X %02X\n"
#define REM_SYMBOL '#'
#define INSTR_STR_TO_BYTE(name) if (strncmp(instr_str, #name, INSTR_BUF_SIZE - 1) == 0) return name

const byte instr_str_to_byte(const char *instr_buf)
{
    char instr_str[INSTR_BUF_SIZE + 1] = { 0 };
    snprintf(instr_str, INSTR_BUF_SIZE, "%s_", instr_buf);
    INSTR_STR_TO_BYTE(INVALID_);
    INSTR_STR_TO_BYTE(NOP_);
    INSTR_STR_TO_BYTE(TXS_);
    INSTR_STR_TO_BYTE(TSX_);
    INSTR_STR_TO_BYTE(PHA_);
    INSTR_STR_TO_BYTE(PLA_);
    INSTR_STR_TO_BYTE(PHP_);
    INSTR_STR_TO_BYTE(PLP_);
    INSTR_STR_TO_BYTE(TAX_);
    INSTR_STR_TO_BYTE(TXA_);
    INSTR_STR_TO_BYTE(DEX_);
    INSTR_STR_TO_BYTE(INX_);
    INSTR_STR_TO_BYTE(TAY_);
    INSTR_STR_TO_BYTE(TYA_);
    INSTR_STR_TO_BYTE(DEY_);
    INSTR_STR_TO_BYTE(INY_);
    INSTR_STR_TO_BYTE(CLC_);
    INSTR_STR_TO_BYTE(SEC_);
    INSTR_STR_TO_BYTE(CLI_);
    INSTR_STR_TO_BYTE(SEI_);
    INSTR_STR_TO_BYTE(CLV_);
    INSTR_STR_TO_BYTE(CLD_);
    INSTR_STR_TO_BYTE(SED_);
    INSTR_STR_TO_BYTE(BPL_);
    INSTR_STR_TO_BYTE(BMI_);
    INSTR_STR_TO_BYTE(BVC_);
    INSTR_STR_TO_BYTE(BVS_);
    INSTR_STR_TO_BYTE(BCC_);
    INSTR_STR_TO_BYTE(BCS_);
    INSTR_STR_TO_BYTE(BNE_);
    INSTR_STR_TO_BYTE(BEQ_);
    INSTR_STR_TO_BYTE(CMP_imm_);
    INSTR_STR_TO_BYTE(CMP_zp_);
    INSTR_STR_TO_BYTE(CMP_zpx_);
    INSTR_STR_TO_BYTE(CMP_abs_);
    INSTR_STR_TO_BYTE(CMP_absx_);
    INSTR_STR_TO_BYTE(CMP_absy_);
    INSTR_STR_TO_BYTE(CMP_indx_);
    INSTR_STR_TO_BYTE(CMP_ind_y_);
    INSTR_STR_TO_BYTE(CPX_imm_);
    INSTR_STR_TO_BYTE(CPX_zp_);
    INSTR_STR_TO_BYTE(CPX_abs_);
    INSTR_STR_TO_BYTE(CPY_imm_);
    INSTR_STR_TO_BYTE(CPY_zp_);
    INSTR_STR_TO_BYTE(CPY_abs_);
    INSTR_STR_TO_BYTE(BIT_zp_);
    INSTR_STR_TO_BYTE(BIT_abs_);
    INSTR_STR_TO_BYTE(JMP_abs_);
    INSTR_STR_TO_BYTE(JMP_ind_);
    INSTR_STR_TO_BYTE(JSR_);
    INSTR_STR_TO_BYTE(RTS_);
    INSTR_STR_TO_BYTE(BRK_);
    INSTR_STR_TO_BYTE(RTI_);
    INSTR_STR_TO_BYTE(ADC_imm_);
    INSTR_STR_TO_BYTE(ADC_zp_);
    INSTR_STR_TO_BYTE(ADC_zpx_);
    INSTR_STR_TO_BYTE(ADC_abs_);
    INSTR_STR_TO_BYTE(ADC_absx_);
    INSTR_STR_TO_BYTE(ADC_absy_);
    INSTR_STR_TO_BYTE(ADC_indx_);
    INSTR_STR_TO_BYTE(ADC_ind_y_);
    INSTR_STR_TO_BYTE(SBC_imm_);
    INSTR_STR_TO_BYTE(SBC_zp_);
    INSTR_STR_TO_BYTE(SBC_zpx_);
    INSTR_STR_TO_BYTE(SBC_abs_);
    INSTR_STR_TO_BYTE(SBC_absx_);
    INSTR_STR_TO_BYTE(SBC_absy_);
    INSTR_STR_TO_BYTE(SBC_indx_);
    INSTR_STR_TO_BYTE(SBC_ind_y_);
    INSTR_STR_TO_BYTE(AND_imm_);
    INSTR_STR_TO_BYTE(AND_zp_);
    INSTR_STR_TO_BYTE(AND_zpx_);
    INSTR_STR_TO_BYTE(AND_abs_);
    INSTR_STR_TO_BYTE(AND_absx_);
    INSTR_STR_TO_BYTE(AND_absy_);
    INSTR_STR_TO_BYTE(AND_indx_);
    INSTR_STR_TO_BYTE(AND_ind_y_);
    INSTR_STR_TO_BYTE(ORA_imm_);
    INSTR_STR_TO_BYTE(ORA_zp_);
    INSTR_STR_TO_BYTE(ORA_zpx_);
    INSTR_STR_TO_BYTE(ORA_abs_);
    INSTR_STR_TO_BYTE(ORA_absx_);
    INSTR_STR_TO_BYTE(ORA_absy_);
    INSTR_STR_TO_BYTE(ORA_indx_);
    INSTR_STR_TO_BYTE(ORA_ind_y_);
    INSTR_STR_TO_BYTE(EOR_imm_);
    INSTR_STR_TO_BYTE(EOR_zp_);
    INSTR_STR_TO_BYTE(EOR_zpx_);
    INSTR_STR_TO_BYTE(EOR_abs_);
    INSTR_STR_TO_BYTE(EOR_absx_);
    INSTR_STR_TO_BYTE(EOR_absy_);
    INSTR_STR_TO_BYTE(EOR_indx_);
    INSTR_STR_TO_BYTE(EOR_ind_y_);
    INSTR_STR_TO_BYTE(ASL_acc_);
    INSTR_STR_TO_BYTE(ASL_zp_);
    INSTR_STR_TO_BYTE(ASL_zpx_);
    INSTR_STR_TO_BYTE(ASL_abs_);
    INSTR_STR_TO_BYTE(ASL_absx_);
    INSTR_STR_TO_BYTE(LSR_acc_);
    INSTR_STR_TO_BYTE(LSR_zp_);
    INSTR_STR_TO_BYTE(LSR_zpx_);
    INSTR_STR_TO_BYTE(LSR_abs_);
    INSTR_STR_TO_BYTE(LSR_absx_);
    INSTR_STR_TO_BYTE(ROL_acc_);
    INSTR_STR_TO_BYTE(ROL_zp_);
    INSTR_STR_TO_BYTE(ROL_zpx_);
    INSTR_STR_TO_BYTE(ROL_abs_);
    INSTR_STR_TO_BYTE(ROL_absx_);
    INSTR_STR_TO_BYTE(ROR_acc_);
    INSTR_STR_TO_BYTE(ROR_zp_);
    INSTR_STR_TO_BYTE(ROR_zpx_);
    INSTR_STR_TO_BYTE(ROR_abs_);
    INSTR_STR_TO_BYTE(ROR_absx_);
    INSTR_STR_TO_BYTE(INC_zp_);
    INSTR_STR_TO_BYTE(INC_zpx_);
    INSTR_STR_TO_BYTE(INC_abs_);
    INSTR_STR_TO_BYTE(INC_absx_);
    INSTR_STR_TO_BYTE(DEC_zp_);
    INSTR_STR_TO_BYTE(DEC_zpx_);
    INSTR_STR_TO_BYTE(DEC_abs_);
    INSTR_STR_TO_BYTE(DEC_absx_);
    INSTR_STR_TO_BYTE(LDX_imm_);
    INSTR_STR_TO_BYTE(LDX_zp_);
    INSTR_STR_TO_BYTE(LDX_zpy_);
    INSTR_STR_TO_BYTE(LDX_abs_);
    INSTR_STR_TO_BYTE(LDX_absy_);
    INSTR_STR_TO_BYTE(LDY_imm_);
    INSTR_STR_TO_BYTE(LDY_zp_);
    INSTR_STR_TO_BYTE(LDY_zpx_);
    INSTR_STR_TO_BYTE(LDY_abs_);
    INSTR_STR_TO_BYTE(LDY_absx_);
    INSTR_STR_TO_BYTE(LDA_imm_);
    INSTR_STR_TO_BYTE(LDA_zp_);
    INSTR_STR_TO_BYTE(LDA_zpx_);
    INSTR_STR_TO_BYTE(LDA_abs_);
    INSTR_STR_TO_BYTE(LDA_absx_);
    INSTR_STR_TO_BYTE(LDA_absy_);
    INSTR_STR_TO_BYTE(LDA_indx_);
    INSTR_STR_TO_BYTE(LDA_ind_y_);
    INSTR_STR_TO_BYTE(STA_zp_);
    INSTR_STR_TO_BYTE(STA_zpx_);
    INSTR_STR_TO_BYTE(STA_abs_);
    INSTR_STR_TO_BYTE(STA_absx_);
    INSTR_STR_TO_BYTE(STA_absy_);
    INSTR_STR_TO_BYTE(STA_indx_);
    INSTR_STR_TO_BYTE(STA_ind_y_);
    INSTR_STR_TO_BYTE(STX_zp_);
    INSTR_STR_TO_BYTE(STX_zpy_);
    INSTR_STR_TO_BYTE(STX_abs_);
    INSTR_STR_TO_BYTE(STY_zp_);
    INSTR_STR_TO_BYTE(STY_zpx_);
    INSTR_STR_TO_BYTE(STY_abs_);
    return  INVALID_;
}

int main(int argc,
         char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    draw_halfass_banner();
    if (argc != 3) {
        fprintf(stderr, "USAGE: ./halfass <input halfassebler filename> <output binary filename>\n");
        return EXIT_FAILURE;
    }

    int ret_val = EXIT_SUCCESS;

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    printf("opening input file\n");
    FILE *input_file = fopen(input_filename, "r");
    if (errno != 0)
    {
        perror("error opening input file");
        ret_val = EXIT_FAILURE;
        goto close_and_exit;
    }

    printf("opening output file\n");
    FILE *output_file = fopen(output_filename, "w+");
    if (errno != 0)
    {
        perror("error opening output file");
        ret_val = EXIT_FAILURE;
        goto close_and_exit;
    }

    while (1)
    {
        printf("parsing line: ");

        char full_cmd_buf[CMD_BUF_SIZE] = { 0 };
        char instr_buf[INSTR_BUF_SIZE] = { 0 };
        unsigned int value_lo_buf = 0;
        unsigned int value_hi_buf = 0;

        if (fgets(full_cmd_buf, CMD_BUF_SIZE, input_file) == 0)
        {
            printf("EOF reached\n");
            break;
        }

        if (full_cmd_buf[0] == REM_SYMBOL ||
            full_cmd_buf[0] == '\0' ||
            full_cmd_buf[0] == '\n' ||
            full_cmd_buf[0] == '\t'  ||
            full_cmd_buf[0] == ' ') {
            printf("rem: %s", full_cmd_buf);
            continue;
        }

        const int matches = sscanf(full_cmd_buf,
                                   INSTR_FMT,
                                   instr_buf,
                                   &value_lo_buf,
                                   &value_hi_buf);
        const byte byte_lo = (byte) value_lo_buf;
        const byte byte_hi = (byte) value_hi_buf;

        if (errno != 0) {
            perror("sscanf error");
            ret_val = EXIT_FAILURE;
            break;
        }

        if (matches == EOF) {
            printf("line EOF reached\n");
            break;
        }

        if (matches > 3) {
            printf("incorrect line\n");
            ret_val = EXIT_FAILURE;
            break;
        }

        if (matches >= 1) {
            printf("%s ", instr_buf);
            const byte instr_val = instr_str_to_byte(instr_buf);
            fwrite(&instr_val, 1, 1, output_file);
        }

        if (matches >= 2) {
            printf("%02X ", byte_lo);
            fwrite(&byte_lo, 1, 1, output_file);
        }
        if (matches >= 3) {
            printf("%02X ", byte_hi);
            fwrite(&byte_hi, 1, 1, output_file);
        }


        printf("\n");
    }

close_and_exit:
    printf("closing input file\n");
    fclose(input_file);
    if (errno != 0)
    {
        perror("error closing input file");
        ret_val = EXIT_FAILURE;
    }

    printf("closing output file\n");
    fclose(output_file);
    if (errno != 0)
    {
        perror("error closing output file");
        ret_val = EXIT_FAILURE;
    }

    return ret_val;
}
