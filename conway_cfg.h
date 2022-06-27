#ifndef CONWAY_CFG_H
#define CONWAY_CFG_H

/* The dimensions of the 'world' that holds our 'cells' */
#define WORLD_HEIGHT 30
#define WORLD_WIDTH 60

/* Number of randomly placed cells you want in the beginning */
#define INITIAL_CELLS 250

/* Delay for the animation in microseconds */
#define DELAY 60000

/* The characters we want to use to represent our cell stats */
#define LIVE_CELL '#'
#define DEAD_CELL ' '

enum {
    WHITE_BLK = 1,
    H_MAGENTA_BLK,
    MAGENTA_BLK,
    RED_BLK,
    YELLOW_BLK,
    GREEN_BLK,
    CYAN_BLK,
    BLUE_BLK,
} color_pairs;

#endif /* CONWAY_CFG_H */