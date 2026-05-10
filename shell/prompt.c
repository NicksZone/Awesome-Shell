#include <stdio.h>
#include <unistd.h>
#include "lsh.h"

void print_prompt(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s> ", cwd);
    else
        printf("Nika's lsh> ");
}