#ifndef DEBUG_H
#define DEBUG_H

#include "types.h"
#include "settings.h"
#include <stdio.h>
#include <stdarg.h>

// colors
#define COL_BLK "\e[0;30m"
#define COL_BLU "\e[0;34m"
#define COL_GRN "\e[0;32m"
#define COL_CYN "\e[0;36m"
#define COL_RED "\e[0;31m"
#define COL_MAG "\e[0;35m"
#define COL_YEL "\e[0;33m"
#define COL_WHT "\e[0;37m"
#define COL_RST "\e[0m"

void print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void debug_print(const char *format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif //DEBUG
}

void draw_block(const unsigned int r_,
                const unsigned int g_,
                const unsigned int b_)
{
    const bool r = r_ > 127 ? 1 : 0;
    const bool g =  g_ > 127 ? 1 : 0;
    const bool b =  b_ > 127 ? 1 : 0;
    char *col = COL_BLK;

    if ( !r && !g && !b ) col = COL_BLK;
    if ( !r && !g &&  b ) col = COL_BLU;
    if ( !r &&  g && !b ) col = COL_GRN;
    if ( !r &&  g &&  b ) col = COL_CYN;
    if ( r  && !g && !b ) col = COL_RED;
    if ( r  && !g &&  b ) col = COL_MAG;
    if ( r  &&  g && !b ) col = COL_YEL;
    if ( r  &&  g &&  b ) col = COL_WHT;

    print("%s█" COL_RST, col);
}

void draw_banner()
{
    print("\n\n");
    draw_block(128, 128, 0);
    draw_block(128, 0, 128);
    draw_block(128, 128, 0);
    print(" 6502 emulator [tomaszu 2023] ");
    draw_block(128, 128, 0);
    draw_block(128, 0, 128);
    draw_block(128, 128, 0);
    print("\n\n");
}

void draw_test_banner()
{
    print("\n\n");
    draw_block(0, 128, 0);
    draw_block(128, 0, 128);
    draw_block(0, 128, 0);
    print(" 6502 emulator [tomaszu 2023] unit test run ");
    draw_block(0, 128, 0);
    draw_block(128, 0, 128);
    draw_block(0, 128, 0);
    print("\n\n");
}

void draw_halfass_banner()
{
    print("\n\n");
    draw_block(0, 0, 128);
    draw_block(128, 0, 128);
    draw_block(0, 0, 128);
    print(" 6502 halfassembler [tomaszu 2023] ");
    draw_block(0, 0, 128);
    draw_block(128, 0, 128);
    draw_block(0, 0, 128);
    print("\n\n");
}

#endif //DEBUG_H
