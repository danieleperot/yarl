#include <stdio.h>
#include "raylib.h"

#define GRID_SIZE 40

int main() {
  for (int y = 0; y < GRID_SIZE; y++) {
    for (int x = 0; x < GRID_SIZE; x++) {
      printf("##");
    }

    printf("\n");
  }

  return 0;
}
