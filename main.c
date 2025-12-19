#include "shell.h"

int main(void) {
    
    init_signals();
    shell_loop();

    return EXIT_SUCCESS;
}