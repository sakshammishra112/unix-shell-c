#include "shell.h"
#include <fcntl.h>

/*
 * Handle input/output redirection.
 * Modifies argv in-place.
 * Returns 0 on success, -1 on error.
 */
int handle_redirection(char **argv)
{
    for (int i = 0; argv[i] != NULL; i++) {

        /* Output redirection: > */
        if (strcmp(argv[i], ">") == 0) {
            if (argv[i + 1] == NULL) {
                fprintf(stderr, "lsh: expected file after '>'\n");
                return -1;
            }

            int fd = open(argv[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);
            if (fd < 0) {
                perror("open");
                return -1;
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);

            argv[i] = NULL;
            break;
        }

        /* Output append: >> */
        if (strcmp(argv[i], ">>") == 0) {
            if (argv[i + 1] == NULL) {
                fprintf(stderr, "lsh: expected file after '>>'\n");
                return -1;
            }

            int fd = open(argv[i + 1],
                          O_WRONLY | O_CREAT | O_APPEND,
                          0644);
            if (fd < 0) {
                perror("open");
                return -1;
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);

            argv[i] = NULL;
            break;
        }

        /* Input redirection: < */
        if (strcmp(argv[i], "<") == 0) {
            if (argv[i + 1] == NULL) {
                fprintf(stderr, "lsh: expected file after '<'\n");
                return -1;
            }

            int fd = open(argv[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("open");
                return -1;
            }

            dup2(fd, STDIN_FILENO);
            close(fd);

            argv[i] = NULL;
            break;
        }
    }

    return 0;
}
