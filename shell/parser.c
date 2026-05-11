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

char*** lsh_line_to_commands(char **tokens)
{
    // create commands array
    size_t cap = 4; // we will increase cap if exceeded
    size_t cmd_count = 0;
    int prevPipeIndex = 0;
    size_t tokenCount = 0;
    char *** commands = malloc(cap * sizeof(char **));

    if(!commands)
    {
        perror("lsh: ");
        return NULL;
    }


    
    for(int i = 0; tokens[i] != NULL; i++)
    {
        if(strcmp(tokens[i], "|") == 0) {
            char **buffer = malloc((i - prevPipeIndex) * sizeof(char*));
            for(int j = prevPipeIndex; j < i; j++)
            {
                buffer[j - prevPipeIndex] = tokens[j];
            };
            commands[cmd_count] = buffer;
            if(cmd_count >= cap)
            {
                cap *= 2;
                commands = realloc(commands, cap * sizeof(char**));
            }
            cmd_count++;
            prevPipeIndex = i + 1;
        };
        tokenCount = i;
    }

    //Debug
    // printf("DEBUG: PRINTING PIPE PARSED COMMANDS\n");
    // for(size_t i = 0; i < cmd_count; i++)
    // {
    //     for(size_t j = 0; j < tokenCount; j++)
    //     {
    //         printf("%s \n", commands[i][j]);
    //     };
    // }

    return commands;
};