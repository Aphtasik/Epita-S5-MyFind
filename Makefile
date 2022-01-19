CC= gcc
CFLAGS= -Wall -Wextra -std=c99 -pedantic -ggdb

my_find: src/my_find.o
	$(CC) $^ -o myfind

check:

clean:
	$(RM) *.o src/*.o vgcore* a.out
