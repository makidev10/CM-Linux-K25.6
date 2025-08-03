CC = gcc
CFLAGS = -Wall -Wextra
LIB_PATH = ../lib/strutils
LIB_NAME = strutils
INCLUDES = -I$(LIB_PATH)

all: main_static main_shared

main_static: main.c
	$(CC) $(CFLAGS) $(INCLUDES) -o main_static main.c $(LIB_PATH)/lib$(LIB_NAME).a

# -Wl,-rpath: Automatically search for linking file
# We can use export LD_LIBRARY_PATH=../lib/strutils as an alternative way
main_shared: main.c
	$(CC) $(CFLAGS) $(INCLUDES) -o main_shared main.c -L$(LIB_PATH) -l$(LIB_NAME) -Wl,-rpath=$(LIB_PATH)

clean:
	rm -f main_static main_shared
