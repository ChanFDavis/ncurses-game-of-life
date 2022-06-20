/*
   Conway's game of life.
   Author: Chandler Davis
*/

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* The dimensions of the 'world' that holds our 'cells' */
#define WORLD_HEIGHT 30
#define WORLD_WIDTH 60

/* Number of randomly placed cells you want in the beginning */
#define INITIAL_CELLS 300

/* Delay for the animation in microseconds */
#define DELAY 60000

/* The characters we want to use to represent our cell stats */
#define LIVE_CELL '#'
#define DEAD_CELL ' '


int old_world[WORLD_HEIGHT][WORLD_WIDTH]; /* Current state of the world */
int new_world[WORLD_HEIGHT][WORLD_WIDTH]; /* The next generation's world state */

/* Returns the number of neighbors a given cell has */
int get_neighbors(int row, int col);

/**
 * Updates a given cell based on the following criteria:
 * 	1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
 *  	2. Any live cell with two or three live neighbors lives on to the next generation.
 * 	3. Any live cell with more than three live neighbors dies, as if by overpopulation.
 * 	4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 *
 * Returns the new state of the cell.
*/
int update_cell(int row, int col);

/* Updates the world */
void update_world();

/* Initialize the world with 'num' randomly placed variables */
void init_world(int num);

/* Draws the world */
void draw_world();


int main() {

   char *ch = '\0';

   /* Provide a seed for the rand() function based on current time in ms*/
   srand(time(0));

   /* Initialize window */
   initscr();

   /* Make added characters immediately available to the program (disable line buffering) */
   cbreak();

   /* Make polling for keyboard input non-blocking. */
   nodelay(stdscr, TRUE);

   /* Don't echo key presses */
   noecho();

   /* Don't display cursor */
   curs_set(FALSE);

   /* Clear the window */
   clear();

   /* Add random cells to the world */
   init_world(INITIAL_CELLS);

   /* Draw our world in the console window */
   draw_world();

   /* Print some instructions for the user */
   // mvprintw(WORLD_HEIGHT + 1, 0, "Press the SPACE key to start the simulation! Press CTRL+C to end.");

   refresh();

   /* The animation loop */
   while(getch() != 'q') {
      update_world();

      clear();
      draw_world();

      refresh();
      usleep(DELAY);
   }

   /* Reset the console back to 'normal' */
   endwin();

   return 0;
}

int get_neighbors(int row, int col) {
   int neighbors = 0;
   int i = 0;
   int j = 0;
   int tempI = 0;
   int tempJ = 0;

   for (i = row - 1; i <= row + 1; i++) {
      for (j = col - 1; j <= col + 1; j++) {

         /* Wrap the row value */
         switch (i) {
               case -1:
                  tempI = WORLD_HEIGHT - 1;
                  break;
               case WORLD_HEIGHT:
                  tempI = 0;
                  break;
               default:
                  tempI = i;
         }

         /* Wrap the colum value */
         switch (j) {
               case -1:
                  tempJ = WORLD_WIDTH - 1;
                  break;
               case WORLD_WIDTH:
                  tempJ = 0;
                  break;
               default:
                  tempJ = j;
         }

         if (!(tempI == row && tempJ == col)) {
               neighbors += old_world[tempI][tempJ];
         }
      }
   }

   return neighbors;
}

int update_cell(int row, int col) {

   int neighbors = get_neighbors(row, col);
   int retVal = 0;

   /* If current state is not zero, check first three rules. Otherwise, check rule 4. */
   if (old_world[row][col] == 1) {
      retVal = (neighbors == 2 || neighbors == 3);
   } else {
      retVal = (neighbors == 3);
   }

   return retVal;
}

void update_world() {
   int i = 0;
   int j = 0;

   /* Iterate through old_world and save the current cell's new state in new_world  */
   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         new_world[i][j] = update_cell(i, j);
      }
   }

   /* Set old_world to new_world */
   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         old_world[i][j] = new_world[i][j];
      }
   }

}

void init_world(int num) {
   int i = 0;
   int j = 0;
   int randRow, randCol;

   /* Intialize all cells to dead (spooky!) */
   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         old_world[i][j] = 0;
         new_world[i][j] = 0;
      }
   }

   /* Add random living cells to the world */
   for (i = 0; i < num; i++) {
      randRow = rand() % WORLD_HEIGHT;
      randCol = rand() % WORLD_WIDTH;
      old_world[randRow][randCol] = 1;
      new_world[randRow][randCol] = 1;
   }

}

void draw_world() {
   int i = 0;
   int j = 0;

   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         mvaddch(i, j, (new_world[i][j] == 1)? LIVE_CELL : DEAD_CELL);
      }
   }
}

