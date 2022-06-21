#include <curses.h>
#include <stdlib.h>
#include <stdbool.h>

#include "conway_cfg.h"
#include "gol_world.h"

/* The structure representing an individual cell in the world. */
typedef struct {
   bool alive;
} cell_t;


static void update_cell(int row, int col);
static int get_neighbors(int row, int col);

cell_t old_world[WORLD_HEIGHT][WORLD_WIDTH] = {0}; /* Current state of the world */
cell_t new_world[WORLD_HEIGHT][WORLD_WIDTH] = {0}; /* The next generation's world state */

void init_world(int num) {
   int i = 0;
   int j = 0;
   int randRow = 0;
   int randCol = 0;

   /* Intialize all cells to dead (spooky!) */
   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         old_world[i][j].alive = FALSE;
         // new_world[i][j].alive = FALSE;
      }
   }

   /* Add random living cells to the world */
   for (i = 0; i < num; i++) {
      randRow = rand() % WORLD_HEIGHT;
      randCol = rand() % WORLD_WIDTH;
      old_world[randRow][randCol].alive = TRUE;
      // new_world[randRow][randCol].alive = TRUE;
   }
}

void draw_world() {
   int i = 0;
   int j = 0;

   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         mvaddch(i, j, (new_world[i][j].alive == TRUE)? LIVE_CELL : DEAD_CELL);
      }
   }
}

void update_world() {
   int i = 0;
   int j = 0;

   /* Iterate through old_world and save the current cell's new state in new_world  */
   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         update_cell(i, j);
      }
   }

   /* Set old_world to new_world */
   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         old_world[i][j] = new_world[i][j];
      }
   }
}

/**
 * Updates a given cell based on the following criteria:
 * 	1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
 *  	2. Any live cell with two or three live neighbors lives on to the next generation.
 * 	3. Any live cell with more than three live neighbors dies, as if by overpopulation.
 * 	4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 *
 */
static void update_cell(int row, int col) {

   int retVal = 0;
   int neighbors = get_neighbors(row, col);

   /* If current state is not zero, check first three rules. Otherwise, check rule 4. */
   if (old_world[row][col].alive = TRUE && (neighbors == 2 || neighbors == 3)) {
      new_world[row][col].alive = TRUE;
   } else if (neighbors == 3) {
      new_world[row][col].alive = TRUE;
   } else {
      new_world[row][col].alive = FALSE;
   }
}

/* Returns the number of neighbors a given cell has. */
static int get_neighbors(int row, int col) {
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
                  break;
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
                  break;
         }

         if (!(tempI == row && tempJ == col)) {
               neighbors += (old_world[tempI][tempJ].alive == TRUE);
         }
      }
   }

   return neighbors;
}