#include "shell.h"

char **parse_line(char *line)
{
    char **tokens = xmalloc(sizeof(char *) * MAX_TOKENS);
    int position = 0;

    char *token = strtok(line, " \t\r\n");

    while (token != NULL && position < MAX_TOKENS - 1) {
        tokens[position++] = token;
        token = strtok(NULL, " \t\r\n");
    }

    tokens[position] = NULL;
    return tokens;
}
