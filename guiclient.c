#include <stdio.h>
#include "raylib.h"
#include "game.h"
#include "board.h"

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
    
    //game_piece_move(&game, MOVE_DOWN);
    //game_piece_move(&game, MOVE_DOWN);
    //game_piece_move(&game, MOVE_DOWN);
       
    while (!WindowShouldClose()) {

	BeginDrawing();
	ClearBackground(RAYWHITE);
	game_tick(&game, GetFrameTime());
	//printf("game.gravity_timer=%f\n", game.gravity_timer);
	printf("piece row=%d\n", game.piece.row);
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
		DrawRectangle(col*20, 500-row*20, 18, 18, BLACK);
	}
    }
    uint16_t tetromino_mask = tetrominos[game->piece.type].mask[game->piece.rot];
    
    for (int row = 0; row < TETROMINO_GRID_SIZE; row++) {
	for (int col = 0; col < TETROMINO_GRID_SIZE; col++) {
	    if (tetromino_mask & TETROMINO_BIT(row,col)) {
		int br = game->piece.row + row;
		int bc = game->piece.col + col;
		if (br >= 0 && br < BOARD_GRID_HEIGHT &&
		    bc >= 0 && bc < BOARD_GRID_WIDTH) {
		    DrawRectangle(bc*20, 500 - br*20, 18, 18,RED);
		}
	    }
	}
    }
}
