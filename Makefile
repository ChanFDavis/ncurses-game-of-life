# Makefile for building the Conway's Game of Life program.

CC=gcc
CPPFLAGS =
CFLAGS = -Wall -Werror
LDFLAGS = -lncurses

SRC_FILES = conway-gol.c gol_world.c

OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)

conway_gol: $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -MMD -o $@ $<

.PHONY: clean all

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES) conway_gol

run: conway_gol
	./conway_gol

all: clean run