#include "my_find.h"

#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

static void find(char *path)
{
    DIR *dir = NULL;
    struct dirent *file = NULL;
    dir = opendir(path);
    if (dir == NULL)
    {
        err(1, "Find: Cannot open folder");
    }

    while ((file = readdir(dir)) != NULL)
    {
        if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
        {
            printf("oui\n");
        }
    }
    closedir(dir);
    return;
}

static void my_find(char *path)
{
    DIR *dir = NULL;
    struct dirent *file = NULL;
    dir = opendir(path);
    if (dir == NULL)
    {
        err(1, "Find: Cannot open folder");
    }

    while ((file = readdir(dir)) != NULL)
    {
        if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
        {
            printf("%s\n", file->d_name);
        }
    }
    closedir(dir);
    return;
}

int main(int argc, char *argv[])
{
    my_find(argv[1]);
    return 0;
}
