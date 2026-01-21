#include <stdio.h>
#include "board.h"
#include "tetromino.h"


void create_tetrominos(void)
{
    for (size_t i = 0; i < TETROMINO_COUNT; i++) {
	tetromino_generate(&shapes[i], &tetrominos[i]);
    }
}

void show_tetrominos(void)
{
    for (size_t i = 0; i < TETROMINO_COUNT; i++) {
	for (size_t rot = 0; rot < 4; rot++) {
	    tetromino_validate(tetrominos[i].mask[rot]);
	    tetromino_dump_mask(tetrominos[i].mask[rot]);
	}
	puts("-----------------------------------");
    }
}

int main(void)
{
    create_tetrominos();
    show_tetrominos();

    return 0;
}
