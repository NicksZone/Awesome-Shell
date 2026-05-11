#include "lsh.h"

/* Operation list */
char *cat_str[] = {
    ">",
    "-n",
    NULL};

/* Function declarations */
int view_content(char **args);
int modify(char **args);
int line_numbers(char **args);

int (*cat_func[])(char **) = {
    &modify,
    &line_numbers,
};

int line_numbers(char **args)
{
    // Open
    for (int i = 2; args[i] != NULL; i++) // start from 1 since args[0] is command itself
    {
        printf("Content of %s: \n", args[i]);
        FILE *fptr;

        fptr = fopen(args[i], "r");
        if (fptr == NULL)
        {
            printf("Not able to open the file.");
        }

        char myString[100];

        int count = 1;
        while (fgets(myString, 100, fptr))
        {
            printf("%d %s", count++, myString);
        };

        printf("\n");
        fclose(fptr);
    };

    return 1;
};

int view_content(char **args)
{
    // Open
    for (int i = 1; args[i] != NULL; i++) // start from 1 since args[0] is command itself
    {
        printf("Content of %s: \n", args[i]);
        FILE *fptr;

        fptr = fopen(args[i], "r");
        if (fptr == NULL)
        {
            printf("Not able to open the file.");
        }

        char myString[100];

        while (fgets(myString, 100, fptr))
        {
            printf("%s", myString);
        };

        printf("\n");
        fclose(fptr);
    };

    return 1;
};

// creates file
// merges two files
int modify(char **args)
{
    size_t cap = 4096;
    size_t len = 0;

    char *buf = malloc(cap);
    if (!buf)
        return 1;

    size_t n;

    int outFileIndex = -1;

    for (int i = 1; args[i]; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            outFileIndex = i + 1;
            break;
        }
        FILE *file = fopen(args[i], "r");
        if (!file)
        {
            perror("lsh: ");
            return 1;
        }

        while ((n = fread(buf + len, 1, cap - len, file)) > 0)
        {
            if (len + n >= cap)
            {
                cap *= 2;
                char *tmp = realloc(buf, cap);
                if (!tmp)
                {
                    free(buf);
                    return 1;
                }
                buf = tmp;
            }

            len += n;
        }

        fclose(file);
    };
    buf[len] = '\0';

    if (outFileIndex == -1 || !args[outFileIndex])
    {
        fprintf(stderr, "missing output file\n");
        return 1;
    }

    if (!args[outFileIndex])
    {
        perror("lsh: ");
        return 1;
    }

    FILE *dest = fopen(args[outFileIndex], "w");
    if (!dest)
    {
        perror("lsh: ");
        return 1;
    }

    if (len > 0)
    {
        fwrite(buf, len, 1, dest);
    };

    fclose(dest);
    return 1;
};

int num_operations(void)
{
    return sizeof(cat_str) / sizeof(char *);
}

char *getOperation(char **args)
{
    for (int i = 1; args[i] != NULL; i++) // Runs at O(n^2) maybe optimize later
    {
        for (int j = 0; cat_str[j] != NULL; j++)
        {
            if (strcmp(args[i], cat_str[j]) == 0)
            {
                return cat_str[j];
            }
        };
    };

    return NULL;
};

int main(int argc, char **args)
{
    char *operation = getOperation(args);

    for (int i = 0; i < num_operations(); i++)
    {
        if (operation && strcmp(operation, cat_str[i]) == 0)
        {                                // map the operation to handler function
            return (*cat_func[i])(args); // return the sufficient function
        }
        else if (operation == NULL)
        {
            return view_content(args);
        }
    }

    return 1;
};