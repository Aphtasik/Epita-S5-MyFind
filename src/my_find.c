#include "my_find.h"

int is_directory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

void print_file(char *path)
{
    printf("%s\n", path);
}

void my_find(char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        err(1, "Find: Cannot open folder");
    }
    struct dirent *file_dirent = NULL;

    while ((file_dirent = readdir(dir)) != NULL)
    {
        char buff[strlen(path) + strlen(file_dirent->d_name) + 2];
        sprintf(buff, "%s/%s", path, file_dirent->d_name);
        if (strcmp(file_dirent->d_name, ".") != 0
            && strcmp(file_dirent->d_name, "..") != 0)
        {
            if (is_directory(buff))
            {
                printf("%s\n", buff);
                my_find(buff);
            }
            else
            {
                print_file(buff);
            }
        }
    }
    closedir(dir);
    return;
}

void my_find_name(char *path, char *match)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        err(1, "Find: Cannot open folder");
    }
    struct dirent *file_dirent = NULL;

    while ((file_dirent = readdir(dir)) != NULL)
    {
        char buff[strlen(path) + strlen(file_dirent->d_name) + 2];
        sprintf(buff, "%s/%s", path, file_dirent->d_name);
        if (strcmp(file_dirent->d_name, ".") != 0
            && strcmp(file_dirent->d_name, "..") != 0)
        {
            if (is_directory(buff))
            {
                my_find_name(buff, match);
            }
            else if (fnmatch(match, file_dirent->d_name, 0) == 0)
            {
                print_file(buff);
            }
        }
    }
    closedir(dir);
    return;
}

void rm_last_backslash(char *path)
{
    unsigned long i = strlen(path);

    if (path[i - 1] == '/')
    {
        path[i - 1] = '\0';
    }
}

void find_head_name(char *path, char *match)
{
    rm_last_backslash(path);
    printf("%s/\n", path);
    my_find_name(path, match);
}

void find_head(char *path)
{
    rm_last_backslash(path);
    printf("%s/\n", path);
    my_find(path);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        my_find(".");
    }
    else
    {
        char **starting_points = calloc(argc - 1, sizeof(char *) * argc);
        int i;
        // Gather all starting points
        for (i = 1; i < argc && argv[i][0] != '-'; i++)
        {
            starting_points[i - 1] = argv[i];
        }

        // If there is only starting points
        if (i == argc)
        {
            for (int j = 0; starting_points[j] != 0; j++)
            {
                find_head(starting_points[j]);
            }
        }
        else
        {
            for (int j = i; j < argc; j++)
            {
                char *arg = argv[j];

                if (strcmp(arg, "-name") == 0)
                {
                    if (j + 1 <= argc)
                    {
                        for (int k = 0; starting_points[k] != 0; k++)
                        {
                            find_head_name(starting_points[k], argv[j + 1]);
                        }
                    }
                    else
                    {
                        err(1, "no arg after -name");
                    }
                }
                else if (strcmp(argv[j], "-print") == 0)
                {
                    for (int k = 0; starting_points[k] != 0; k++)
                    {
                        find_head(starting_points[k]);
                    }
                }
            }
        }
        free(starting_points);
    }
    return 0;
}
