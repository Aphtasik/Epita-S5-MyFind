#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stddef.h>
#include <dirent.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct dirent *dirp = NULL;

    if (argc > 2)
    {
        return 1;
    }
    else
    {
        if (argc == 1)
        {
            dp = opendir(".");
        }
        else
        {
            dp = opendir(argv[1]);
        }

        if (dp == NULL)
        {
            return 1;
        }

        while ((dirp = readdir(dp)) != NULL)
        {
            printf("%s\n", dirp->d_name);
        }
    }
    closedir(dp);
    return 0;
}

