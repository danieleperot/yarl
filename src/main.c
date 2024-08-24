#include <stdio.h>
#include "raylib.h"

#include "map.h"

#define GRID_SIZE 600
#define PANEL_SIZE 300
#define PLAYER_SIZE 80

#define log(...) printf("\033[0;36mINFO: "); printf(__VA_ARGS__); printf("\033[0m\n");

typedef struct {
    Vector2 pos;
    int speed;
} Player;

void player_draw(Player *player, Vector2 *world_coords) {
    float x = GetScreenWidth() / 2 - PLAYER_SIZE / 2;
    float y = GetScreenHeight() / 2 - PLAYER_SIZE / 2;

    DrawRectangle(x, y, PLAYER_SIZE, PLAYER_SIZE, RED);
    DrawCircle(x + PLAYER_SIZE / 4, y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(x + PLAYER_SIZE / 4, y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
    DrawCircle(x + PLAYER_SIZE / 4 * 3, y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(x + PLAYER_SIZE / 4 * 3, y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
}

void reset_player(Player *player) {
    player->pos.x = GetScreenWidth() / 2;
    player->pos.y = GetScreenHeight() / 2;
    player->speed = 10;
}

int main() {
    Player player = {0};
    Vector2 world_coords = {0};

    Map map = {0};
    generate_map(&map);

    int map_offset_x = 0;
    int map_offset_y = 0;

    float map_tile_size = 100.0; // px

    InitWindow(1600, 1200, "Yet Another Rouge Like");
    SetTargetFPS(60);

    reset_player(&player);
    while (!WindowShouldClose()) {
        log("=========================================================");

        if (IsKeyDown(KEY_R)) reset_player(&player);

        map_offset_y = (int)player.pos.y % (int)map_tile_size;
        map_offset_x = (int)player.pos.x % (int)map_tile_size;

        float mid_width = GetScreenWidth() / 2;
        float mid_height = GetScreenHeight() / 2;
        float player_corner_x = player.pos.x - mid_width;
        float player_corner_y = player.pos.y - mid_height;

        int map_start_y = (int)player_corner_y / (int)map_tile_size;
        if (map_start_y < 0) map_start_y = 0;
        int map_end_y = map_start_y + (GetScreenHeight() / map_tile_size) + (map_offset_y > 0 ? 1 : 0);

        int map_start_x = (int)player_corner_x / (int)map_tile_size;
        if (map_start_x < 0) map_start_x = 0;
        int map_end_x = map_start_x + (GetScreenWidth() / map_tile_size) + (map_offset_x > 0 ? 1 : 0);

        world_coords.x = map_start_x * map_tile_size + map_offset_x;
        world_coords.y = map_start_y * map_tile_size + map_offset_y;
        
        log("Corner relative to screen: %f,%f", player_corner_x, player_corner_y)
        log("World coordinates: %f,%f", world_coords.x, world_coords.y)
        log("Player position: %f,%f - speed: %d", player.pos.x, player.pos.y, player.speed)
        log("Offset of the map: %d,%d", map_offset_x, map_offset_y)
        log("Map drawing: from %d,%d to %d,%d", map_start_x, map_start_y, map_end_x, map_end_y)

        int multiplier = IsKeyDown(KEY_LEFT_SHIFT) ? 10 : 1;
        if (IsKeyPressed(KEY_LEFT_BRACKET) && player.speed > multiplier) player.speed -= multiplier;
        if (IsKeyPressed(KEY_RIGHT_BRACKET) && player.speed < 100) player.speed += multiplier;

        if (IsKeyDown(KEY_UP) && player.pos.y - PLAYER_SIZE / 2 > player.speed) player.pos.y -= player.speed;
        if (IsKeyDown(KEY_RIGHT) && player.pos.x + player.speed + PLAYER_SIZE / 2 < map.max_cols * map_tile_size) player.pos.x += player.speed;
        if (IsKeyDown(KEY_DOWN) && player.pos.y + player.speed + PLAYER_SIZE / 2 < map.max_rows * map_tile_size) player.pos.y += player.speed;
        if (IsKeyDown(KEY_LEFT) && player.pos.x - PLAYER_SIZE / 2 > player.speed) player.pos.x -= player.speed;

        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));

        for (int y = 0; y < map_end_y && y < map.max_cols; y++) {
            for (int x = 0; x < map_end_x && x < map.max_rows; x++) {
                int tile = map.data[y][x];
                Color color = BLUE;

                if (tile == 0) {
                    color = GetColor(0x171203FF);
                } else if (tile == 1) {
                    color = DARKGRAY;
                }

                float offset_x = player_corner_x; 
                float offset_y = player_corner_y; 

                float x_start = map_tile_size * x - offset_x;
                float y_start = map_tile_size * y - offset_y;
                DrawRectangle(x_start, y_start, map_tile_size, map_tile_size, color);
            }
        }

        player_draw(&player, &world_coords);

        DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RED);
        DrawLine(0, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight() / 2, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
