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
   srand(time(0)); /* Provide a seed for the rand() function based on current time in ms*/

   initscr(); /* Initialize window */

   cbreak(); /* Make added characters immediately available to the program (disable line buffering) */

   #ifdef DEBUG
   nodelay(stdscr, FALSE); /* Make polling for keyboard input non-blocking. */
   #else
   nodelay(stdscr, TRUE); /* Make polling for keyboard input non-blocking. */
   #endif

   noecho(); /* Don't echo key presses */

   curs_set(FALSE); /* Don't display cursor */

   clear(); /* Clear the window */

   init_world(); /* Add random cells to the world */

   draw_world(); /* Draw our world in the console window */

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

   endwin(); /* Reset the console back to 'normal' */

   return 0;
}
