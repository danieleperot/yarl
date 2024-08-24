#ifndef MAP_H
#define MAP_H

#define MAP_SIZE 20

typedef enum {
    TILE_WALL,
    TILE_PASSAGE
} Tile;

typedef struct {
    Tile data[MAP_SIZE][MAP_SIZE];
} Map;

void generate_map(Map *map);

#endif

