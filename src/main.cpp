#include "raylib.h"

int main() {
  InitWindow(1200, 600, "name");
  int i = 1;
  while (!WindowShouldClose()) {
    if (i % 2000 == 0) {
      i = 1;
      HideCursor();
    } else {
        i++;
        ShowCursor();
    }
    BeginDrawing();
    ClearBackground(BLUE);
    EndDrawing();
    }
  CloseWindow();
  return 0;
}
