#ifndef GOL_WORLD_H
#define GOL_WORLD_H

/* Initialize the world with randomly placed living cells. */
void init_world();

/* Updates the world to the next state. */
void update_world();

/* Draws the world. */
void draw_world();

/* Inserts a cell into the old world and new world at the given location. */
void add_cell(int y, int x);

/* Kills all the cells in the world to get a "blank slate". */
void clear_world();

#endif /* GOL_WORLD_H */