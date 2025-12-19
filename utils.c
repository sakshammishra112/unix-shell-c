#include "shell.h"

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if( !ptr ) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}