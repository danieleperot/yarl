#include <stdio.h>
#include "map.h"

void log_error(const char* message) {
    fprintf(stderr, "[YARL] ERROR: %s\n", message);
}

void log_warn(const char* message) {
    fprintf(stderr, "[YARL] WARNING: %s\n", message);
}

void log_info(const char* message) {
    fprintf(stdout, "[YARL] INFO: %s\n", message);
}

void generate_map(Map *map) {
    log_info("Loading map from file");

    FILE* file = fopen("./assets/map.txt", "r");
    if (!file) {
        log_error("Could not open map file");
        return;
    }

    int cursor = 0;
    char tile;

    while ((tile = fgetc(file)) != EOF) {
        printf("%c", tile);

        int row = cursor / MAP_SIZE;
        int col = cursor % MAP_SIZE;

        // Ignoring empty lines, they are there just for formatting
        if (tile == '\n') continue;
        else if (tile == '0') map->data[row][col] = TILE_WALL;
        else if (tile == '1') map->data[row][col] = TILE_PASSAGE;
        // No more tiles to load
        else if (tile == EOF) break;
        else {
            char message[100];
            sprintf(message, "Unknown tile: %c", tile);
            log_error(message);
        }

        cursor ++;
    }

    map->max_rows = MAP_SIZE;
    map->max_cols = MAP_SIZE;
    
    fclose(file);

    log_info("Map loaded successfully from file");
}

