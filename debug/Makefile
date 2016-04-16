CFLAGS=-g -Wall

all: clean
	gcc test.c -o test

ndebug: clean
	gcc test.c -o test -DNDEBUG

clean:
	rm -f test
