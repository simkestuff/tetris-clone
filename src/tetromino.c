#include <stdio.h>
#include <assert.h>
#include "tetromino.h"

static_assert(TETROMINO_BIT(0,0) == 0x0008);
static_assert(TETROMINO_BIT(1,0) == 0x0080);
static_assert(TETROMINO_BIT(2,0) == 0x0800);
static_assert(TETROMINO_BIT(3,0) == 0x8000);
static_assert(TETROMINO_BIT(3,3) == 0x1000);


void tetromino_dump_mask(uint16_t mask)
{
    for (size_t row = 4; row-- > 0;) {
	for (size_t col = 4; col-- > 0; ) {
	    if (mask & TETROMINO_BIT(row,col)) printf("*");
	    else printf(".");
	}
	printf("\n");
    }
}

void tetromino_validate(uint16_t mask)
{
    int count = 0;
    for (size_t i = 0; i < 16; i++) {
	if (mask & (1u << i)) count++;
    }
    assert(count == 4 && "tetromino must have 4 parts");
}

uint16_t tetromino_shape_to_mask(const TetrominoShape *shape) {
    uint16_t mask = 0;
    for (size_t i = 0; i < 4; i++) {
	mask |= TETROMINO_BIT(shape->cells[i].row, shape->cells[i].col);
    }
    return mask;
}

TetrominoShape tetromino_rotate_shape_clockwise(const TetrominoShape *shape) {
    // r,c -> c, 3-r
    TetrominoShape ts;
    for (size_t i = 0; i < 4; i++) {
	ts.cells[i].col = 3 - shape->cells[i].row;
	ts.cells[i].row = shape->cells[i].col;
    }
    return ts;
}

// push shape to bottom left
void tetromino_normalize_shape(TetrominoShape *shape) {
    size_t min_row = 3;
    size_t min_col = 3;
    for (size_t i = 0; i < 4; i++) {
	if (shape->cells[i].row < min_row) min_row = shape->cells[i].row;
	if (shape->cells[i].col < min_col) min_col = shape->cells[i].col;
    }

    for (size_t i = 0; i < 4; i++) {
	shape->cells[i].row = shape->cells[i].row - min_row;
	shape->cells[i].col = shape->cells[i].col - min_col; 
    }
}

void tetromino_generate(const TetrominoShape *base, Tetromino *out)
{
    TetrominoShape shape = *base;
    for (size_t i = 0; i < 4; i++) {
	tetromino_normalize_shape(&shape);
	out->mask[i] = tetromino_shape_to_mask(&shape);
	shape =  tetromino_rotate_shape_clockwise(&shape);
    }
}
