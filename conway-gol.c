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

#include "conway_cfg.h"
#include "gol_world.h"

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
