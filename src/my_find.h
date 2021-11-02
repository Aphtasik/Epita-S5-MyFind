#ifndef MY_FIND_H
#define MY_FIND_H

#include <dirent.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void my_find(char *path);

#endif
