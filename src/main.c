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
    int scene_x;
    int scene_y;
    Direction direction;
} Player;

void player_draw(Player *player) {
    DrawRectangle(player->scene_x, player->scene_y, PLAYER_SIZE, PLAYER_SIZE, RED);
    DrawCircle(player->scene_x + PLAYER_SIZE / 4, player->scene_y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(player->scene_x + PLAYER_SIZE / 4, player->scene_y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
    DrawCircle(player->scene_x + PLAYER_SIZE / 4 * 3, player->scene_y + PLAYER_SIZE / 4, PLAYER_SIZE / 6, WHITE);
    DrawCircle(player->scene_x + PLAYER_SIZE / 4 * 3, player->scene_y + PLAYER_SIZE / 4, PLAYER_SIZE / 12, BLACK);
}

int main() {
    Player player = {
        .scene_x = 200,
        .scene_y = 200,
        .direction = DIR_UP
    };

    float dx = 7;
    float dy = 7;

    InitWindow(800, 600, "Yet Another Rouge Like");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (player.scene_x <= 0 || player.scene_x + PLAYER_SIZE >= GetScreenWidth()) {
            dx *= -1;
        }

        if (player.scene_y <= 0 || player.scene_y + PLAYER_SIZE >= GetScreenHeight()) {
            dy *= -1;
        }

        player.scene_x += dx;
        player.scene_y += dy;

        BeginDrawing();
        ClearBackground(GetColor(0x181818FF));

        player_draw(&player);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
