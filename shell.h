#ifndef SHELL_H
#define SHELL_H

#define _POSIX_C_SOURCE 200809L

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

#define SHELL_PROMPT "lsh> "
#define MAX_TOKENS 128

typedef struct {
    char **argv;
} Command;

void shell_loop(void);

char **parse_line(char *line);

int execute_command(char **argv);

void init_signals(void);

int handle_redirection(char **argv);

int execute_pipeline(char **argv);

int is_builtin(char *cmd);
int run_builtin(char **argv);

void *xmalloc(size_t size);

#endif