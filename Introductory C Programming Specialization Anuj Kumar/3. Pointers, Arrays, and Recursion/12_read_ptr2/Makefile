CFLAGS=-std=gnu99 -pedantic -Wall -Werror
test: test.o
	gcc -o test test.o
test.o: test.c
	gcc $(CFLAGS) -c test.c