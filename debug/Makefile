CFLAGS=-g -Wall -Wextra

all: clean test

build: ndebug

ndebug: CFLAGS= -DNDEBUG
ndebug: all

clean:
	rm -f test
