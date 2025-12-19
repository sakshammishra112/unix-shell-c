#include "shell.h"
#include <sys/stat.h>
#include <fcntl.h>

static int builtin_cd(char **argv);
static int builtin_exit(char **argv);
static int builtin_pwd(char **argv);
static int builtin_mkdir(char **argv);
static int builtin_rmdir(char **argv);
static int builtin_touch(char **argv);
static int builtin_rm(char **argv);

static char *builtin_names[] = {
    "cd",
    "exit",
    "pwd",
    "mkdir",
    "rmdir",
    "touch",
    "rm"
};

static int (*builtin_funcs[])(char **) = {
    builtin_cd,
    builtin_exit,
    builtin_pwd,
    builtin_mkdir,
    builtin_rmdir,
    builtin_touch,
    builtin_rm
};

static int builtin_count(void)
{
    return sizeof(builtin_names) / sizeof(char *);
}

int is_builtin(char *cmd)
{
    for (int i = 0; i < builtin_count(); i++) {
        if (strcmp(cmd, builtin_names[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int run_builtin(char **argv)
{
    for (int i = 0; i < builtin_count(); i++) {
        if (strcmp(argv[0], builtin_names[i]) == 0) {
            return builtin_funcs[i](argv);
        }
    }
    return 1;
}

/* ---- Builtin implementations ---- */
static int builtin_cd(char **argv)
{
    if (argv[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        perror("lsh");
    }

    return 1;
}

static int builtin_exit(char **argv)
{
    (void)argv;
    return 0;
}

static int builtin_pwd(char **argv)
{
    (void)argv;
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("lsh");
        return 1;
    }

    printf("%s\n", cwd);
    return 1;
}

static int builtin_mkdir(char **argv)
{
    if (argv[1] == NULL) {
        fprintf(stderr, "mkdir: missing operand\n");
        return 1;
    }

    if (mkdir(argv[1], 0755) != 0) {
        perror("mkdir");
    }

    return 1;
}

static int builtin_rmdir(char **argv)
{
    if (argv[1] == NULL) {
        fprintf(stderr, "rmdir: missing operand\n");
        return 1;
    }

    if (rmdir(argv[1]) != 0) {
        perror("rmdir");
    }

    return 1;
}

static int builtin_touch(char **argv)
{
    if (argv[1] == NULL) {
        fprintf(stderr, "touch: missing file operand\n");
        return 1;
    }

    int fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("touch");
        return 1;
    }

    close(fd);
    return 1;
}

static int builtin_rm(char **argv)
{
    if (argv[1] == NULL) {
        fprintf(stderr, "rm: missing operand\n");
        return 1;
    }

    if (unlink(argv[1]) != 0) {
        perror("rm");
    }

    return 1;
}

