CFLAGS=-g -Wall

all: clean
	cc test.c -o test

ndebug: clean
	cc test.c -o test -DNDEBUG

clean:
	rm -f test
