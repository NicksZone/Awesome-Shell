#ifndef LSH_H
#define LSH_H

// parser configs
#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Shell global state container */
typedef struct s_shell {
    char root_dir[1024];
} Shell;

/* Core loop */
void lsh_loop(Shell *sh);

/* Input / parsing */
char *lsh_read_line(void);
char **lsh_split_line(char *line);
char ***lsh_line_to_commands(char **args);

/* Execution */
int lsh_execute(Shell *sh, char **args);
int lsh_launch(Shell *sh, char **args);

/* Builtins */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/* Utilities */
void print_prompt(void);

extern char *builtin_str[];
extern int (*builtin_func[])(char **);
int lsh_num_builtins(void);

#endif