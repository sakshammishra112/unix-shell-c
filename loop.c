#include "shell.h"

static char *read_line(void) {

    char *line = NULL;
    size_t size = 0;

    if( getline(&line, &size, stdin) == -1 ) {
        free(line);
        exit(EXIT_SUCCESS);
    }

    return line;

}

void shell_loop(void) {

    char *line;
    char **argv;
    int status = 1;

    while( status ) {
        printf("%s", SHELL_PROMPT);
        fflush(stdout);

        line = read_line();
        argv = parse_line(line);
        
        if( argv[0] != NULL ) {
            status = execute_command(argv);
        }

        free(argv);
        free(line);
    }

}