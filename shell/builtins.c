#include "lsh.h"

/* Builtin list */
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins(void)
{
    return sizeof(builtin_str) / sizeof(char *);
}

/* Builtins */
int lsh_cd(char **args)
{
    if (args[1] == NULL) {
        chdir(getenv("HOME"));
    } else {
        if (chdir(args[1]) != 0)
            perror("lsh");
    }
    return 1;
}

int lsh_help(char **args)
{
    printf("LSH shell\nBuiltins:\n");

    for (int i = 0; i < lsh_num_builtins(); i++)
        printf("  %s\n", builtin_str[i]);

    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}