#include <curses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "conway_cfg.h"
#include "gol_world.h"

/* The structure representing an individual cell in the world. */
typedef struct {
   bool alive;
   unsigned int age;
} cell_t;

static void update_cell(int row, int col);
static int get_neighbors(int row, int col);
static int age_color(int age);

cell_t old_world[WORLD_HEIGHT][WORLD_WIDTH] = {0}; /* Current state of the world */
cell_t new_world[WORLD_HEIGHT][WORLD_WIDTH] = {0}; /* The next generation's world state */

/* Initialize the world with randomly placed living cells. */
void init_world() {
   int i = 0;
   int randRow = 0;
   int randCol = 0;

   /* Add random living cells to the world */
   for (i = 0; i < INITIAL_CELLS; i++) {
      randRow = rand() % WORLD_HEIGHT;
      randCol = rand() % WORLD_WIDTH;
      old_world[randRow][randCol].alive = TRUE;
      new_world[randRow][randCol].alive = TRUE;
   }
}

/* Draws the world. */
void draw_world() {
   int i = 0;
   int j = 0;

   for (i = 0; i < WORLD_HEIGHT; i++) {
      for (j = 0; j < WORLD_WIDTH; j++) {
         attron(COLOR_PAIR(age_color(new_world[i][j].age)));
         mvaddch(i, j, (new_world[i][j].alive == TRUE)? LIVE_CELL : DEAD_CELL);
         attroff(COLOR_PAIR(age_color(new_world[i][j].age)));
      }
   }
}

static int age_color(int age) {
   int color = 0;

   switch(age) {
      case 0:
         color = WHITE_BLACK;
         break;
      case 1:
         color = MAGENTA_BLACK;
         break;
      case 2:
         color = RED_BLACK;
         break;
      case 3:
         color = YELLOW_BLACK;
         break;
      case 4:
         color = GREEN_BLACK;
         break;
      case 5:
         color = CYAN_BLACK;
         break;
      default:
         color = BLUE_BLACK;
         break;
   }

   return color;
}

/* Updates the world to the next state. */
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
         memcpy(&old_world[i][j], &new_world[i][j], sizeof(cell_t));
      }
   }
}

/**
 * Updates a given cell based on the following criteria:
 * 	1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
 *  	2. Any live cell with two or three live neighbors lives on to the next generation.
 * 	3. Any live cell with more than three live neighbors dies, as if by overpopulation.
 * 	4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 */
static void update_cell(int row, int col) {
   int neighbors = get_neighbors(row, col);

   /* If cell state is alive, check first three rules. Otherwise, check rule 4. */
   if (old_world[row][col].alive == TRUE) {
      if (neighbors == 2 || neighbors == 3) {
         new_world[row][col].alive = TRUE;
         new_world[row][col].age += 1;
      } else {
         new_world[row][col].alive = FALSE;
         new_world[row][col].age = 0;
      }
   } else {
      new_world[row][col].alive = (neighbors == 3);
      new_world[row][col].age = 0;
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