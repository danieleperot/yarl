#ifndef MAP_H
#define MAP_H

#define MAP_SIZE 50

typedef enum {
    TILE_WALL,
    TILE_PASSAGE
} Tile;

typedef struct {
    Tile data[MAP_SIZE][MAP_SIZE];
    int max_rows;
    int max_cols;
} Map;

void generate_map(Map *map);

#endif

