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

int main(int argc, char *argv[])
{
    char *path = argv[1];
    my_find(path);
    return 0;
}
