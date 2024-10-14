#include "raylib.h"

int main() {

  InitWindow(640, 480, "TESTING, BITCH!");

    while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(WHITE);
      EndDrawing();
    }

    CloseWindow();

    return 0;
}
