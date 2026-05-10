/*
    Handles external programs + dispatcher.
*/

#include "lsh.h"

int lsh_execute(Shell *sh, char **args)
{
    if (args[0] == NULL)
        return 1;

    // check for a builtin function
    for (int i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) { // map the first arg (name of function) to existing one
            return (*builtin_func[i])(args); // return the sufficient function
        }
    }

    return lsh_launch(sh, args);
}

int lsh_launch(Shell *sh, char **args)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        // Child program (for externals)
        char fullpath[2048]; // define path

        // sh->root_dir: path to bin on current machine
        // args[0]: name of function to execute
        snprintf(fullpath, sizeof(fullpath), "%s/bin/%s", sh->root_dir, args[0]); // write to path

        // printf("Path debug: %s\n", fullpath);

        execv(fullpath, args); // execute the function

        perror("lsh");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error while forking
        perror("lsh");
    } else {
        // Parent program 
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}