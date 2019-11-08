CC=gcc
CFLAGS=-Wall

all: shell
shell: shell.o
shell.o: shell.c mymemory.h mymemory.c

clean:
	rm -f shell shell.o
run: program
	./program
