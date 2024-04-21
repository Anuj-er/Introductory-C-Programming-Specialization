CFLAGS=-Wall -Werror -pedantic -std=gnu99
test: test.o
	gcc -o test test.o
test.o: test.c
	gcc $(CFLAGS) -c test.c
.PHONY: clean
clean:
	rm -f test *.o *.c~ *.h~