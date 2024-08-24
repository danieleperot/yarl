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

void player_draw(Player *player) {
    // Always draw player at the center of the screen (for now)
    float x = GetScreenWidth() / 2 - PLAYER_SIZE / 2;
    float y = GetScreenHeight() / 2 - PLAYER_SIZE / 2;

    DrawRectangle(x, y, PLAYER_SIZE, PLAYER_SIZE, RED);
    DrawCircle(x + PLAYER_SIZE / 4, y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(x + PLAYER_SIZE / 4, y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
    DrawCircle(x + PLAYER_SIZE / 4 * 3, y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(x + PLAYER_SIZE / 4 * 3, y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
}

void player_draw_stats(Player *player) {
    int panel_x = GetScreenWidth() - PANEL_SIZE;
    int title_size = 24;
    int title_padding_y = 15;

    DrawRectangle(panel_x, 0, PANEL_SIZE, GetScreenHeight(), GetColor(0x676767FF));
    DrawText("Player stats", GRID_SIZE + 10, title_padding_y, title_size, WHITE);

    DrawRectangle(panel_x, title_padding_y * 2 + title_size, PANEL_SIZE, 5, DARKGRAY);
}

void reset_player(Player *player) {
    player->pos.x = GetScreenWidth() / 2;
    player->pos.y = GetScreenHeight() / 2;
    player->speed = 10;
}

int main() {
    Player player = {0};

    Map map;
    generate_map(&map);

    int map_offset_x = 0;
    int map_offset_y = 0;

    float map_tile_size = 200.0; // px

    InitWindow(1600, 1200, "Yet Another Rouge Like");
    SetTargetFPS(60);

    reset_player(&player);
    while (!WindowShouldClose()) {
        log("=========================================================\n");
        if (IsKeyPressed(KEY_LEFT_BRACKET) && player.speed > 1) player.speed -= 1;
        if (IsKeyPressed(KEY_RIGHT_BRACKET) && player.speed < 100) player.speed += 1;

        if (IsKeyDown(KEY_UP)) player.pos.y -= player.speed;
        if (IsKeyDown(KEY_RIGHT)) player.pos.x += player.speed;
        if (IsKeyDown(KEY_DOWN)) player.pos.y += player.speed;
        if (IsKeyDown(KEY_LEFT)) player.pos.x -= player.speed;

        if (IsKeyDown(KEY_R)) reset_player(&player);

        map_offset_y = (int)player.pos.y % (int)map_tile_size;
        map_offset_x = (int)player.pos.x % (int)map_tile_size;

        float player_corner_x = player.pos.x - GetScreenWidth() / 2;
        float player_corner_y = player.pos.y - GetScreenHeight() / 2;
        
        log("Corner relative to screen: %f,%f", player_corner_x, player_corner_y)
        log("Player position: %f,%f - speed: %d", player.pos.x, player.pos.y, player.speed)
        log("Offset of the map: %d,%d", map_offset_x, map_offset_y)

        BeginDrawing();
        ClearBackground(GREEN);

        int map_start_y = (int)player_corner_y / (int)map_tile_size;
        if (map_start_y < 0) map_start_y = 0;
        int map_end_y = map_start_y + (GetScreenHeight() / map_tile_size) + (map_offset_y > 0 ? 1 : 0);

        int map_start_x = (int)player_corner_x / (int)map_tile_size;
        if (map_start_x < 0) map_start_x = 0;
        int map_end_x = map_start_x + (GetScreenWidth() / map_tile_size) + (map_offset_x > 0 ? 1 : 0);

        log("Map draw tiles: [(%d, %d), (%d, %d)]", map_start_x, map_start_y, map_end_x - 1, map_end_y - 1)

        for (int y = 0; y < map_end_y && y < map.max_cols; y++) {
            for (int x = 0; x < map_end_x && x < map.max_rows; x++) {
                int tile = map.data[y][x];
                Color color = BLUE;

                if (tile == 0) {
                    color = LIGHTGRAY;
                } else if (tile == 1) {
                    color = GRAY;
                }

                float x_start = map_tile_size * x - player_corner_x;
                float y_start = map_tile_size * y - player_corner_y;
                DrawRectangle(x_start, y_start, map_tile_size, map_tile_size, color);
                DrawLine(x_start, y_start, x_start + map_tile_size, y_start, DARKGRAY);
                DrawLine(x_start + map_tile_size, y_start, x_start + map_tile_size, y_start + map_tile_size, DARKGRAY);
                DrawLine(x_start, y_start + map_tile_size, x_start, y_start + map_tile_size, DARKGRAY);
                DrawLine(x_start, y_start + map_tile_size, x_start + map_tile_size, y_start + map_tile_size, DARKGRAY);

                char string[64] = "";
                sprintf(string, "(%d,%d) [%d]", x, y, tile);

                DrawText(string, x_start + 10, y_start + 10, 28, BLACK);
            }
        }

        // player_draw_stats(&player);

        player_draw(&player);

        DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RED);
        DrawLine(0, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight() / 2, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
