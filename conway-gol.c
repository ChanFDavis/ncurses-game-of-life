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

static void init_color_pairs(void);

int main(void) {

   bool end_loop = FALSE;

   srand(time(0)); /* Provide a seed for the rand() function based on current time in ms*/

   initscr(); /* Initialize window */

   cbreak(); /* Make added characters immediately available to the program (disable line buffering) */

   start_color(); /* Mmmm... color... */

   init_color_pairs();

   if(!has_colors())
	{
      endwin();
      printf("Your terminal does not support color! ( Lame :( )\n");
      exit(1);
	}

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
   while(!end_loop) {

      switch(getch()) {
         case 'q':
         case 'Q':
            end_loop = TRUE;
            break;
         case 'b':
         case 'B':
            standend();
            attron(A_BOLD);
            break;
         case 'd':
         case 'D':
            standend();
            attron(A_DIM);
            break;
         case 'r':
         case 'R':
            standend();
            break;
         case 's':
         case 'S':
            standend();
            attron(A_STANDOUT);
            break;
         case 'e':
         case 'E':
            standend();
            attron(A_REVERSE);
            break;
         default:
            break;
      }

      update_world();

      clear();
      draw_world();

      refresh();
      usleep(DELAY);
   }

   endwin(); /* Reset the console back to 'normal' */

   return 0;
}

static void init_color_pairs(void) {
   init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
   init_pair(BLACK_BLACK, COLOR_BLACK, COLOR_BLACK);
   init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);
   init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
   init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
   init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
   init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
   init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
}