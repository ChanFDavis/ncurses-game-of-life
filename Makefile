# Makefile for building the Conway's Game of Life program.

SRC_FILES = conway-gol.c gol_world.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all: build run

build: $(SRC_FILES)
	gcc $^ -lncurses -o gol

run: gol
	./gol

.PHONY: clean

clean:
	rm -f $(OBJ_FILES)
