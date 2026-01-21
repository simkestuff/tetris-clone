#include "board.h"

Board board_create()
{
    Board b = {0};
    return b;
}

bool board_row_full(Board *board, size_t row)
{
    for (size_t col = 0; col < BOARD_GRID_WIDTH; col++) {
	if (board->cells[row][col] == 0) return false;
    }
    return true;
}
