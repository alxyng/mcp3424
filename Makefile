CC = gcc
CFLAGS = -std=c99 -g -pedantic -Wall
INCLUDES = -I/usr/local/include
OBJS = main.o mcp3424.o
PROGRAM = main

all: main

main: main.c mcp3424.h mcp3424.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(PROGRAM) main.c mcp3424.c

clean:
	rm -f main

.PHONY: all clean
