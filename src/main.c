#include <stdio.h>
#include "raylib.h"

#include "map.h"

#define GRID_SIZE 600
#define PANEL_SIZE 300
#define PLAYER_SIZE 40

typedef enum {
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
} Direction;

typedef struct {
    Vector2 pos;
    Direction direction;
} Player;

void player_draw(Player *player) {
    DrawRectangle(player->pos.x, player->pos.y, PLAYER_SIZE, PLAYER_SIZE, RED);
    DrawCircle(player->pos.x + PLAYER_SIZE / 4, player->pos.y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(player->pos.x + PLAYER_SIZE / 4, player->pos.y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
    DrawCircle(player->pos.x + PLAYER_SIZE / 4 * 3, player->pos.y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(player->pos.x + PLAYER_SIZE / 4 * 3, player->pos.y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
}

void player_draw_stats(Player *player) {
    int panel_x = GetScreenWidth() - PANEL_SIZE;
    int title_size = 24;
    int title_padding_y = 15;

    DrawRectangle(panel_x, 0, PANEL_SIZE, GetScreenHeight(), GetColor(0x676767FF));
    DrawText("Player stats", GRID_SIZE + 10, title_padding_y, title_size, WHITE);

    DrawRectangle(panel_x, title_padding_y * 2 + title_size, PANEL_SIZE, 5, DARKGRAY);
}

int main() {
    Player player = {
        .pos = {
            .x = 200,
            .y = 200,
        },
        .direction = DIR_UP,
    };

    Map map;
    generate_map(&map);

    InitWindow(GRID_SIZE + PANEL_SIZE, GRID_SIZE, "Yet Another Rouge Like");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));

        player_draw_stats(&player);

        player_draw(&player);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
