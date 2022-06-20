# Makefile for building the Conway's Game of Life program.

SRC_FILES = conway-gol.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all: build run

build: conway-gol.c
	gcc conway-gol.c -lncurses -o gol

run: gol
	./gol

.PHONY: clean

clean:
	rm -f $(OBJ_FILES)
