/*
    Handles input + tokenizing
*/

#include "lsh.h"

char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(bufsize);
    int c;

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }

        buffer[position++] = c;

        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
        }
    }
}

char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL) {
        tokens[position++] = token;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}