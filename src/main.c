#include <stdio.h>
#include "raylib.h"

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

int main() {
    Player player = {
        .pos = {
            .x = 200,
            .y = 200,
        },
        .direction = DIR_UP,
    };

    float dx = 7;
    float dy = 7;

    InitWindow(800, 600, "Yet Another Rouge Like");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));

        player_draw(&player);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
