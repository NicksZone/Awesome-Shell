#include "lsh.h"

void lsh_loop(Shell *sh)
{
    char *line;
    char **args;
    char ***commands;
    int status;

    do {
        print_prompt();

        line = lsh_read_line();
        args = lsh_split_line(line);
        commands = lsh_line_to_commands(args);
        status = lsh_execute(sh, args);

        free(line);
        free(args);

    } while (status);
}