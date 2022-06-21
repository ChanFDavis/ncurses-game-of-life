# Makefile for building the Conway's Game of Life program.

CC=gcc
CPPFLAGS = -DDEBUG
CFLAGS = -Wall -Werror
LDFLAGS =

SRC_FILES = conway-gol.c gol_world.c
OBJ_FILES = $(SRC_FILES:.c=.o)

build: $(OBJ_FILES)
	$(CC) $(LDFLAGS) $^ -lncurses -o gol.exe

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

run: gol.exe
	./gol.exe

.PHONY: clean

clean:
	rm -f $(OBJ_FILES) gol.exe

all: clean build run
