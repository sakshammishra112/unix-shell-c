#include "shell.h"

/*
 * Check if command contains a pipe
 */
static int has_pipe(char **argv)
{
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0)
            return 1;
    }
    return 0;
}

/*
 * Execute a pipeline: cmd1 | cmd2 | ...
 */
int execute_pipeline(char **argv)
{
    int i;
    int in_fd = STDIN_FILENO;
    int pipefd[2];
    pid_t pid;

    int start = 0;

    while (1) {
        /* Find next pipe */
        for (i = start; argv[i] != NULL && strcmp(argv[i], "|") != 0; i++)
            ;

        int is_last = (argv[i] == NULL);

        if (!is_last) {
            pipe(pipefd);
        }

        pid = fork();

        if (pid == 0) {
            /* ---- CHILD ---- */

            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);

            /* Input from previous command */
            if (in_fd != STDIN_FILENO) {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            /* Output to next command */
            if (!is_last) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            argv[i] = NULL;  // split argv

            execvp(argv[start], &argv[start]);
            perror(argv[start]);
            exit(EXIT_FAILURE);
        }

        /* ---- PARENT ---- */

        if (in_fd != STDIN_FILENO)
            close(in_fd);

        if (!is_last) {
            close(pipefd[1]);
            in_fd = pipefd[0];
        } else {
            break;
        }

        start = i + 1;
    }

    /* Wait for all children */
    while (wait(NULL) > 0)
        ;

    return 1;
}

/*
 * Entry point for command execution
 */
int execute_command(char **argv)
{
    if (argv[0] == NULL)
        return 1;

    /* Pipes take precedence */
    if (has_pipe(argv)) {
        return execute_pipeline(argv);
    }

    /* Builtins (no pipes) */
    if (is_builtin(argv[0])) {
        return run_builtin(argv);
    }

    /* Normal command */
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        handle_redirection(argv);

        execvp(argv[0], argv);
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }

    waitpid(pid, &status, 0);
    return 1;
}
