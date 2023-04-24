CC=g++
CFLAGS=-DNDEBUG=1

all: onegin

onegin: source/main.c
	$(CC) source/main.c $(CFLAGS) -o FileSort
