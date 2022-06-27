# Makefile for building the Conway's Game of Life program.

CC=gcc
CPPFLAGS =
CFLAGS = -Wall -Werror
LDFLAGS = -lncurses

SRC_FILES = conway-gol.c gol_world.c

OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)

conway_gol: $(OBJ_FILES)
	$(CC) $^ -o gol.exe $(LDFLAGS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -MMD -o $@ $<

run: gol.exe
	./gol.exe

.PHONY: clean all

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES) conway_gol

all: clean build run
