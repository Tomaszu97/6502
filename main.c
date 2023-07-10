#include "cpu.h"
#include "memory.h"
#include "test.h"
#include <stdio.h>

int main()
{
    initialize();
#ifdef TEST
    draw_test_banner();
    run_tests();
#else
    draw_banner();
    load_program();
    run();
#endif
    return 0;
}
