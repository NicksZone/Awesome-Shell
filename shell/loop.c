#include "lsh.h"

void lsh_loop(Shell *sh)
{
    char *line;
    char **args;
    int status;

    do {
        print_prompt();

        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(sh, args);

        free(line);
        free(args);

    } while (status);
}