#include <stdio.h>
#include "raylib.h"
#include "game.h"

void game_render(Game *game);

void fill_row(Board *board, uint8_t row, int content)
{
    int bit = 0;
    for (size_t i = 0; i < BOARD_GRID_WIDTH; i++) {
	if (content & 1u << i) bit = 1;
	board->cells[row][BOARD_GRID_WIDTH - 1 - i] = bit;
	bit = 0;
    }
}


int main(void)
{
    InitWindow(800, 600, "tetris gui test");
    SetTargetFPS(60);

    Game game = game_init();
    fill_row(&game.board, 0,  0b1111111111);
    fill_row(&game.board, 1,  0b1000000000);
    fill_row(&game.board, 2,  0b1111111111);
    fill_row(&game.board, 3,  0b1111111111);
    fill_row(&game.board, 4,  0b1101101100);
    fill_row(&game.board, 8,  0b0111111110);
    fill_row(&game.board, 18, 0b1100000011);
    fill_row(&game.board, 19, 0b1111111111);
    
    while (!WindowShouldClose()) {

	BeginDrawing();
	ClearBackground(RAYWHITE);
	game_render(&game);
	EndDrawing();
    }

    CloseWindow();
    
    return 0;
}

void game_render(Game *game)
{
    Board board = game->board;
    for (int row = 0; row < BOARD_GRID_HEIGHT; row++) {
	for (int col = 0; col < BOARD_GRID_WIDTH; col++) {
	    if (board.cells[row][col])
		DrawRectangle(col*20, 500-row*20, 20, 20, BLACK);
	}
    }
}
