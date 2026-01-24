#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "tetromino.h"


void show_tetrominos(void)
{
    for (size_t i = 0; i < TETROMINO_COUNT; i++) {
	for (size_t rot = 0; rot < 4; rot++) {
	    tetromino_validate(tetrominos[i].mask[rot]);
	    tetromino_dump_mask(tetrominos[i].mask[rot]);
	    printf("\n");
	}
	puts("-----------------------------------");
    }
}

void fill_row(Board *board, uint8_t row, int content)
{
    int bit = 0;
    for (size_t i = 0; i < BOARD_GRID_WIDTH; i++) {
	if (content & 1u << i) bit = 1;
	board->cells[row][BOARD_GRID_WIDTH - 1 - i] = bit;
	bit = 0;
    }
}

void test_board_clearing()
{
    Board board = board_create();
    fill_row(&board, 0,  0b1111111111);
    fill_row(&board, 1,  0b1000000000);
    fill_row(&board, 2,  0b1111111111);
    fill_row(&board, 3,  0b1111111111);
    fill_row(&board, 4,  0b1101101100);
    fill_row(&board, 19, 0b1111111111);
    fill_row(&board, 18, 0b1100000011);

    char snap1[BOARD_GRID_HEIGHT][BOARD_GRID_WIDTH+1] = {0};
    char snap2[BOARD_GRID_HEIGHT][BOARD_GRID_WIDTH+1] = {0};
    board_snapshot(&board, snap1);
    board_clear_full_rows(&board);
    board_snapshot(&board, snap2);

    for (size_t row = 0; row < BOARD_GRID_HEIGHT; row++) {
	printf("%s | %s\n",
	       snap1[BOARD_GRID_HEIGHT - row - 1],
	       snap2[BOARD_GRID_HEIGHT - row - 1]);
    }    
}

int main(void)
{
    //show_tetrominos();
    test_board_clearing();
    
    return 0;
}
