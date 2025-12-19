#include "shell.h"

static void signit_handler(int signo) 
{
    (void)signo;
    
    write(STDOUT_FILENO, "\n" SHELL_PROMPT, sizeof("\n" SHELL_PROMPT) - 1);
}

void init_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = signit_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &sa, NULL);

}