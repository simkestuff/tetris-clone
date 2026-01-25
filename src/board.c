#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "board.h"

Board board_create()
{
    Board b = {0};
    return b;
}

bool board_row_full(const Board *board, uint8_t row)
{
    for (size_t col = 0; col < BOARD_GRID_WIDTH; col++) {
	if (board->cells[row][col] == 0) return false;
    }
    return true;
}

void board_row_clear(Board *board, uint8_t row)
{
    assert(row < BOARD_GRID_HEIGHT && "row index out of bounds");
    for (size_t col = 0; col < BOARD_GRID_WIDTH; col++) {
	board->cells[row][col] = 0;
    }
}

int board_clear_full_rows(Board *board)
{
    int cleared = 0;
    for (int row = 0; row < BOARD_GRID_HEIGHT; row++) {
	if (board_row_full(board, row)) {
	    int rows_to_top = BOARD_GRID_HEIGHT - row - 1;
	    if (rows_to_top) {
		memmove(board->cells[row],
			board->cells[row+1],
			(sizeof board->cells[0][0]) * BOARD_GRID_WIDTH * rows_to_top);
	    }
	    board_row_clear(board, BOARD_GRID_HEIGHT - 1); 
	    cleared++;
	    row--;
	}
    }
    return cleared;
}

Piece board_piece_spawn(TetrominoType type)
{
    return (Piece) {
	.row = SPAWN_ROW,
	.col = SPAWN_COL,
	.rot = 0,
	.type = type,
    };
}

bool board_piece_fits(const Board *board, const Piece *piece)
{
    uint16_t tetromino_mask = tetrominos[piece->type].mask[piece->rot];
    for (int row = 0; row < TETROMINO_GRID_SIZE; row++) {
	for (int col = 0; col < TETROMINO_GRID_SIZE; col++) {
	    if (tetromino_mask & TETROMINO_BIT(row,col)) {
		int br = piece->row + row;
		int bc = piece->col + col;
		// "filled" tetromino cells shouldn't go outside board
		// except they can be above board i.e. tetromino didn't
		// visible on board yet
		if (br >= BOARD_GRID_HEIGHT) continue;
		if (br < 0 || bc < 0 || bc >= BOARD_GRID_WIDTH) return false;
		if (board->cells[br][bc]) return false;
	    }
	}
    }
    return true;
}

void board_piece_merge(Board *board, const Piece *piece)
{
    uint16_t tetromino_mask = tetrominos[piece->type].mask[piece->rot];
    for (int row = 0; row < TETROMINO_GRID_SIZE; row++) {
	for (int col = 0; col < TETROMINO_GRID_SIZE; col++) {
	    if (tetromino_mask & TETROMINO_BIT(row,col)) {
		int br = piece->row + row;
		int bc = piece->col + col;
		assert(br >= 0 && br < BOARD_GRID_HEIGHT &&
		       bc >= 0 && bc < BOARD_GRID_WIDTH &&
		       "tetromino outside board"); 
		board->cells[br][bc] = 1;
	    }
	}
    }
}

bool board_move_piece(const Board *board, Piece *piece, Move move)
{
    Piece tmp = *piece;
    tmp.row += move.drow;
    tmp.col += move.dcol;
    if (board_piece_fits(board, &tmp)) {
	*piece = tmp;
	return true;
    }
    return false;
}

bool board_rotate_piece(const Board *board, Piece *piece, Rotation rot)
{
    Piece tmp = *piece;
    tmp.rot = (tmp.rot + rot.drot + 4) % 4;
    if (board_piece_fits(board, &tmp)) {
	*piece = tmp;
	return true;
    }
    return false;
}

void board_snapshot(const Board *board, char (*str)[BOARD_GRID_WIDTH  + 1])
{
    for (size_t row = 0; row < BOARD_GRID_HEIGHT; row++ ) {
	for (size_t col = 0; col < BOARD_GRID_WIDTH; col++) {
	    str[row][col] = board->cells[row][col]? '#' : '.';
	}
	str[row][BOARD_GRID_WIDTH] =  '\0';
    }
}

void board_snapshot_with_piece(const Board *board, const Piece *piece, char (*str)[BOARD_GRID_WIDTH + 1])
{
    uint16_t tetromino_mask = tetrominos[piece->type].mask[piece->rot];
    for (size_t row = 0; row < BOARD_GRID_HEIGHT; row++ ) {
	for (size_t col = 0; col < BOARD_GRID_WIDTH; col++) {
	    str[row][col] = board->cells[row][col]? '#' : '.';
	}
	str[row][BOARD_GRID_WIDTH] =  '\0';
    }

    for (int row = 0; row < TETROMINO_GRID_SIZE; row++) {
	for (int col = 0; col < TETROMINO_GRID_SIZE; col++) {
	    if (tetromino_mask & TETROMINO_BIT(row,col)) {
		int br = piece->row + row;
		int bc = piece->col + col;
		if (br >= 0 && br < BOARD_GRID_HEIGHT &&
		    bc >= 0 && bc < BOARD_GRID_WIDTH) {
		    str[br][bc] = board->cells[br][bc]? '!': 'X';
		}
	    }
	}
    }
}

void board_print_board(const Board *board)
{
    char output[BOARD_GRID_HEIGHT][BOARD_GRID_WIDTH  + 1] = {0};
    board_snapshot(board, output);
    for (size_t i = BOARD_GRID_HEIGHT; i-- > 0; ) {
	printf("%s\n", output[i]);

    }
}

void board_print_board_with_piece(const Board *board, const Piece *piece)
{
    char output[BOARD_GRID_HEIGHT][BOARD_GRID_WIDTH  + 1] = {0};
    board_snapshot_with_piece(board, piece, output);
    for (size_t i = BOARD_GRID_HEIGHT; i-- > 0; ) {
	printf("%s\n", output[i]);

    }
}
