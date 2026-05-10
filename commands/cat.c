#include "lsh.h"

/* Operation list */
char *cat_str[] = {
    "\0",
    ">",
    "-n",
};

/* Function declarations */
int view_content(char **args);
int edit(char **args);
int line_numbers(char **args);

int (*cat_func[])(char **) = {
    &view_content,
    &edit,
    &line_numbers,
};

int line_numbers(char **args)
{
    puts("Unimplemented");
    return 1;
};

int view_content(char **args)
{
    // Open
    for(int i = 1; args[i] != NULL; i++) // start from 1 since args[0] is command itself
    {
        printf("Content of %s: \n", args[i]);
        FILE *fptr;

        fptr = fopen(args[i], "r");
        if(fptr == NULL)
        {
            printf("Not able to open the file.");
        }

        char myString[100];

        while (fgets(myString, 100, fptr)) {
            printf("%s", myString);
        };

        printf("\n");
        fclose(fptr);
    };

    return 1;
};

int edit(char **args)
{
    puts("Unimplemented");
    return 1;
};

int num_operations(void)
{
    return sizeof(cat_str) / sizeof(char *);
}

char getOperation(char **args)
{
    for(int i = 0; args[i] != NULL; i++) // Runs at O(n^2) maybe optimize later
    {
        for(int j = 0; cat_str[j] != NULL; j++)
        {
            if(strcmp(args[i], cat_str[j]) == 0)
                return *cat_str[j];
        };
    };

    return '\0';
};



int main(int argc, char **args)
{
    char operation = getOperation(args);

    for (int i = 0; i < num_operations(); i++) {
        if (strcmp(&operation, cat_str[i]) == 0) { // map the operation to handler function
            return (*cat_func[i])(args); // return the sufficient function
        }
    }

    return 1;
};