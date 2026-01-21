#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define BOARD_GRID_WIDTH  10
#define BOARD_GRID_HEIGHT  20

typedef struct {
    uint8_t cells[BOARD_GRID_HEIGHT][BOARD_GRID_WIDTH];
} Board;

Board board_create(void);
bool board_row_full(Board *board, size_t row);

#endif // BOARD_H
