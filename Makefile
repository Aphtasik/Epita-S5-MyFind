CC= gcc
CFLAGS= -Wall -Wextra -std=c99 -pedantic

all: src/my_find.o
	$(CC) $^
	./a.out .

clean:
	$(RM) *.o src/*.o vgcore* a.out
