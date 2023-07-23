#include "cpu.h"
#include "memory.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,
         char **argv)
{
    initialize();

#ifdef TEST
    draw_test_banner();
    run_tests();
#else
    draw_banner();
    if (argc != 2) {
        fprintf(stderr, "USAGE: ./6502 <input binary filename>\n");
        return EXIT_FAILURE;
    }
    const char *input_filename = argv[1];
    if (load_program(input_filename) == false) {
        fprintf(stderr, "program loading failed\n");
        return EXIT_FAILURE;
    }
    run();
#endif

    return EXIT_SUCCESS;
}
