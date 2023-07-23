#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"
#include "opcodes.h"
#include "debug.h"
#include <errno.h>
#include <stdio.h>

// cursor
#define CUR_SET_FMT "\e[<%d>;<%d>H"
#define CUR_SAVE    "\e[s"
#define CUR_RESTORE "\e[u"

// random access memory
#define RAM_SIZE 65536
byte RAM[RAM_SIZE] = { 0 };

// memory location constants
const word PC_INIT             = 0xFFFC;
const word SP_BOTTOM           = 0x01FF;
const word SP_TOP              = 0x0100;
const word MONITOR_BUF         = 0x1000;
const word MONITOR_BUF_WND_H   = 0x0010;
const word MONITOR_BUF_WND_W   = 0x0020;

// registers
word PC  = 0x0000;  // program counter
byte SP  = 0xFF;    // stack pointer
byte A   = 0x00;    // accumulator
byte X   = 0x00;
byte Y   = 0x00;

// flags
bool CF  = false;   // carry flag
bool ZF  = false;   // zero flag
bool ID  = false;   // interrupt disable
bool DM  = false;   // decimal mode
bool BC  = false;   // break command
bool OVF = false;   // overflow flag
bool NF  = false;   // negative flag

void write_byte(const byte byte_,
                const word addr)
{
    RAM[addr] = byte_;
}

const byte read_byte(const word addr)
{
    return RAM[addr];
}

void write_word(const word word_,
                const word addr)
{
    RAM[addr] = (word_ & 0x00FF);
    RAM[addr+1] = ((word_ & 0xFF00) >> 8);
}

const word read_word(const word addr)
{
    word retval = 0x0000;
    retval |= RAM[addr];
    retval |= (RAM[addr+1] << 8);
    return retval;
}

void push(const byte val)
{
    SP -= 1;
    RAM[SP_TOP | (word)SP] = val;
}

const byte pull()
{
    const byte val = RAM[SP_TOP | (word)SP];
    SP += 1;
    return val;
}

void push_word(const word val)
{
    const byte l = (val & 0x00FF);
    const byte h = ((val & 0xFF00) >> 8);
    push(h);
    push(l);
}

const word pull_word()
{
    const byte l = pull();
    const byte h = pull();
    word val = 0x0000;
    val |= l;
    val |= h;
    return val;
}

const byte get_PS()
{
    byte retval = 0x00;
    retval |= (CF ? 0x01 : 0x00)  << 0;
    retval |= (ZF ? 0x01 : 0x00)  << 1;
    retval |= (ID ? 0x01 : 0x00)  << 2;
    retval |= (DM ? 0x01 : 0x00)  << 3;
    retval |= (BC ? 0x01 : 0x00)  << 4;
    retval |= (OVF ? 0x01 : 0x00) << 6;
    retval |= (NF ? 0x01 : 0x00)  << 7;
    return retval;
}

void set_PS(byte PS)
{
    CF  = ((PS & 0b00000001) != 0);
    ZF  = ((PS & 0b00000010) != 0);
    ID  = ((PS & 0b00000100) != 0);
    DM  = ((PS & 0b00001000) != 0);
    BC  = ((PS & 0b00010000) != 0);
    OVF = ((PS & 0b01000000) != 0);
    NF  = ((PS & 0b10000000) != 0);
}

void zero_RAM_()
{
    debug_print("initializing RAM\n");
    word addr = 0xFFFF;
    do {
        RAM[addr] = 0x00;
    } while (addr-- != 0);
}

void init_CPU()
{
    debug_print("initializing CPU registers\n");
    PC  = 0x0000;
    SP  = 0xFF;
    A   = 0x00;
    X   = 0x00;
    Y   = 0x00;

    debug_print("initializing CPU flags\n");
    CF  = false;
    ZF  = false;
    ID  = false;
    DM  = false;
    BC  = false;
    OVF = false;
    NF  = false;
}

void init_RAM()
{
    zero_RAM_();
}

void init_PC()
{
    debug_print("initializing PC value from RAM\n");
    PC = read_word(PC_INIT);
}

bool load_program(const char *input_filename)
{
    debug_print("loading program into RAM\n");

    printf("opening input file\n");
    FILE *input_file = fopen(input_filename, "r");
    if (errno != 0)
    {
        perror("error opening input file");
        return false;
    }

    fread(RAM, RAM_SIZE,  1, input_file);

    printf("closing input file\n");
    fclose(input_file);
    if (errno != 0)
    {
        perror("error closing input file");
        return false;
    }

    return true;
}

#endif //MEMORY_H
