CC = gcc
CFLAGS = -Wall -Wextra
LIB_PATH = ../lib/strutils
LIB_NAME = strutils

all: main

main: main.o
	$(CC) $(CFLAGS) -o main main.o -L$(LIB_PATH) -l$(LIB_NAME) -Wl,-rpath=$(LIB_PATH)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main.o main
