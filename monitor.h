#ifndef MONITOR_H
#define MONITOR_H

#include "settings.h"
#include "debug.h"
#include "memory.h"

void draw_monitor()
{
#ifdef MONITOR
    for (int h = 0; h < MONITOR_BUF_WND_H; h++)
    {
        for (int w = 0; w < MONITOR_BUF_WND_W; w++)
        {
            const word addr = MONITOR_BUF + (h * MONITOR_BUF_WND_W) + w;
            const byte color_value = 0xFF - read_byte(addr);
            draw_block(color_value, color_value, color_value);
        }
        print("\n");
    }
    print("\n");
#endif //MONITOR
}

#endif //MONITOR_H
