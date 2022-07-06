/*
   Conway's game of life.
   Author: Chandler Davis
*/

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "conway_cfg.h"
#include "gol_world.h"

typedef struct {
   int x;
   int y;
   bool clicked;
} cursor_stats_t;

static void init_color_pairs(void);

static void move_cursor(cursor_stats_t *cursor, int d_y, int d_x);

int main(void) {

   bool end_loop = FALSE;
   bool paused = FALSE;
   bool cursor_active = FALSE;

   /* Initialize the cursor stats structure. */
   cursor_stats_t cursor = {0};

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
   /* TODO: Add in instructions being drawn on the side for the user. */
   // mvprintw(WORLD_HEIGHT + 1, 0, "Press the SPACE key to start the simulation! Press CTRL+C to end.");

   refresh();

   /* The animation loop */
   while(!end_loop) {
      
      clear();
      draw_world();

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
         case 'p':
         case 'P':
            paused = !paused; /* Toggle pause on and off. */
            break;
         case 'c':
            cursor_active = !cursor_active;
            break;
         case 'i':
            move_cursor(&cursor, -1, 0);
            break;
         case 'k':
            move_cursor(&cursor, 1, 0);
            break;
         case 'j':
            move_cursor(&cursor, 0, -1);
            break;
         case 'l':
            move_cursor(&cursor, 0, 1);
            break;
         case ' ':
            /* Place a new cell into the old and new worlds at the current cursor position. */
            add_cell(cursor.y, cursor.x);
            break;
         default:
            break;
      }

      if (cursor_active) {
         mvaddch(cursor.y, cursor.x, CURSOR);
      }

      if (!paused) {
         update_world();
      }

      refresh();
      usleep(DELAY);
   }

   endwin(); /* Reset the console back to 'normal' */

   return 0;
}

/* Moves the cursor according to the given differences in the x and y coordinates. */
static void move_cursor(cursor_stats_t *cursor, int d_y, int d_x) {

   int new_y = cursor->y + d_y;
   int new_x = cursor->x + d_x;

   /* Check the bounds of the coordinates and wrap them. */
   if (new_y >= WORLD_HEIGHT) {
      cursor->y = 0;
   } else if (new_y < 0) {
      cursor->y = WORLD_HEIGHT - 1;
   } else {
      cursor->y = new_y;
   }
   
   if (new_x >= WORLD_WIDTH) {
      cursor->x = 0;
   } else if (new_x < 0) {
      cursor->x = WORLD_WIDTH - 1;
   } else {
      cursor->x = new_x;
   }
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