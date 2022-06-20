# Makefile for building the Conway's Game of Life program.

SRC_FILES = conway-gol.c gol_world.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all: build run

build: $(OBJ_FILES)
	gcc $^ -lncurses -o gol.exe

%.o: %.c
	$(CC) -c $<

run: gol.exe
	./gol.exe

.PHONY: clean

clean:
	rm -f $(OBJ_FILES) gol.exe
