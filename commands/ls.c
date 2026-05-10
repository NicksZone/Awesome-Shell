#include "lsh.h"
#include <dirent.h>

/*
    info from blog https://c-for-dummies.com/blog/?p=3246
*/

int main(int argc, char** args)
{
    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(".");
    if(folder == NULL)
    {
        printf("Unable to read current directory\n");
    }

    while( (entry=readdir(folder)) )
    {
        files++;
        printf("%s ", entry->d_name);
    }

    printf("\n");

    closedir(folder);

    return 1; // return 1 for shell to keep running
};