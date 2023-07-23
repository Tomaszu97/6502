#ifndef OPCODES_H
#define OPCODES_H

// invalid
#define INVALID_   0xFF

// no operation
#define NOP_       0xEA

// stack instructions
#define TXS_       0x9A
#define TSX_       0xBA
#define PHA_       0x48
#define PLA_       0x68
#define PHP_       0x08
#define PLP_       0x28

// register instructions
#define TAX_       0xAA
#define TXA_       0x8A
#define DEX_       0xCA
#define INX_       0xE8
#define TAY_       0xA8
#define TYA_       0x98
#define DEY_       0x88
#define INY_       0xC8

// flag instructions
#define CLC_       0x18
#define SEC_       0x38
#define CLI_       0x58
#define SEI_       0x78
#define CLV_       0xB8
#define CLD_       0xD8
#define SED_       0xF8

// branch instructions
#define BPL_       0x10
#define BMI_       0x30
#define BVC_       0x50
#define BVS_       0x70
#define BCC_       0x90
#define BCS_       0xB0
#define BNE_       0xD0
#define BEQ_       0xF0

// compare accumulator
#define CMP_imm_   0xC9
#define CMP_zp_    0xC5
#define CMP_zpx_   0xD5
#define CMP_abs_   0xCD
#define CMP_absx_  0xDD
#define CMP_absy_  0xD9
#define CMP_indx_  0xC1
#define CMP_ind_y_ 0xD1

// compare x register
#define CPX_imm_   0xE0
#define CPX_zp_    0xE4
#define CPX_abs_   0xEC

// compare y register
#define CPY_imm_   0xC0
#define CPY_zp_    0xC4
#define CPY_abs_   0xCC

// test bits
#define BIT_zp_    0x24
#define BIT_abs_   0x2C

// jump
#define JMP_abs_   0x4C
#define JMP_ind_   0x6C

// jump to subroutine
#define JSR_       0x20

// return from subroutine
#define RTS_       0x60

// break - non-maskable interrupt
#define BRK_       0x00

// return from interrupt
#define RTI_       0x40

// add with carry
#define ADC_imm_   0x69
#define ADC_zp_    0x65
#define ADC_zpx_   0x75
#define ADC_abs_   0x6D
#define ADC_absx_  0x7D
#define ADC_absy_  0x79
#define ADC_indx_  0x61
#define ADC_ind_y_ 0x71

// subtract with carry
#define SBC_imm_   0xE9
#define SBC_zp_    0xE5
#define SBC_zpx_   0xF5
#define SBC_abs_   0xED
#define SBC_absx_  0xFD
#define SBC_absy_  0xF9
#define SBC_indx_  0xE1
#define SBC_ind_y_ 0xF1

// bitwise and with accumulator
#define AND_imm_   0x29
#define AND_zp_    0x25
#define AND_zpx_   0x35
#define AND_abs_   0x2D
#define AND_absx_  0x3D
#define AND_absy_  0x39
#define AND_indx_  0x21
#define AND_ind_y_ 0x31

// bitwise or with accumulator
#define ORA_imm_   0x09
#define ORA_zp_    0x05
#define ORA_zpx_   0x15
#define ORA_abs_   0x0D
#define ORA_absx_  0x1D
#define ORA_absy_  0x19
#define ORA_indx_  0x01
#define ORA_ind_y_ 0x11

// bitwise exclusive or with accumulator
#define EOR_imm_   0x49
#define EOR_zp_    0x45
#define EOR_zpx_   0x55
#define EOR_abs_   0x4D
#define EOR_absx_  0x5D
#define EOR_absy_  0x59
#define EOR_indx_  0x41
#define EOR_ind_y_ 0x51

// arithmetic shift left
#define ASL_acc_   0x0A
#define ASL_zp_    0x06
#define ASL_zpx_   0x16
#define ASL_abs_   0x0E
#define ASL_absx_  0x1E

// logical shift right
#define LSR_acc_   0x4A
#define LSR_zp_    0x46
#define LSR_zpx_   0x56
#define LSR_abs_   0x4E
#define LSR_absx_  0x5E

// rotate left
#define ROL_acc_   0x2A
#define ROL_zp_    0x26
#define ROL_zpx_   0x36
#define ROL_abs_   0x2E
#define ROL_absx_  0x3E

// rotate right
#define ROR_acc_   0x6A
#define ROR_zp_    0x66
#define ROR_zpx_   0x76
#define ROR_abs_   0x6E
#define ROR_absx_  0x7E

// increment memory
#define INC_zp_    0xE6
#define INC_zpx_   0xF6
#define INC_abs_   0xEE
#define INC_absx_  0xFE

// decrement memory
#define DEC_zp_    0xC6
#define DEC_zpx_   0xD6
#define DEC_abs_   0xCE
#define DEC_absx_  0xDE

// load x register from memory
#define LDX_imm_   0xA2
#define LDX_zp_    0xA6
#define LDX_zpy_   0xB6
#define LDX_abs_   0xAE
#define LDX_absy_  0xBE

// load y register from memory
#define LDY_imm_   0xA0
#define LDY_zp_    0xA4
#define LDY_zpx_   0xB4
#define LDY_abs_   0xAC
#define LDY_absx_  0xBC

// load accumulator from memory
#define LDA_imm_   0xA9
#define LDA_zp_    0xA5
#define LDA_zpx_   0xB5
#define LDA_abs_   0xAD
#define LDA_absx_  0xBD
#define LDA_absy_  0xB9
#define LDA_indx_  0xA1
#define LDA_ind_y_ 0xB1

// store accumulator in memory
#define STA_zp_    0x85
#define STA_zpx_   0x95
#define STA_abs_   0x8D
#define STA_absx_  0x9D
#define STA_absy_  0x99
#define STA_indx_  0x81
#define STA_ind_y_ 0x91

// store x register in memory
#define STX_zp_    0x86
#define STX_zpy_   0x96
#define STX_abs_   0x8E

// store y register in memory
#define STY_zp_    0x84
#define STY_zpx_   0x94
#define STY_abs_   0x8C

#endif //OPCODES_H
