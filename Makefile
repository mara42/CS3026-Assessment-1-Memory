# Martti Aukia 51657228
CC=gcc
CFLAGS=-Wall

all: run
shell: mymemory.o shell.o
shell.o: shell.c
	gcc -c shell.c -o shell.o
mymemory.o: mymemory.c mymemory.h
	gcc -c mymemory.c -o mymemory.o

clean:
	rm -f shell shell.o mymemory.o
run: shell
	./shell
