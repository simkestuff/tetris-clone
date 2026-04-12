#include <stdio.h>
#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "tetris gui test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText("Hello GUI world!", 190, 200, 40, RED);
	EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
