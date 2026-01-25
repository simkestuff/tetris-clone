#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "tetromino.h"


#define BOARD_GRID_WIDTH 10
#define BOARD_GRID_HEIGHT 20

#define SPAWN_ROW  (BOARD_GRID_HEIGHT-1) 
#define SPAWN_COL  ((BOARD_GRID_WIDTH-TETROMINO_GRID_SIZE)/2)


// 10x20, at some r,c position ->if 0 is empty, if 1 is full
typedef struct {
    uint8_t cells[BOARD_GRID_HEIGHT][BOARD_GRID_WIDTH];
} Board;


// anchor = position where piece apear on the board
// piece spawns at anchor = SPAWN_ROW, SPAWN_COL
// anchor matches tetromino grid 0,0 cell
// then for each cell of the piece is
// piece.row + tetromino.row = row on board
// piece.col + tetromino.col = col on board

typedef struct {
    int row, col;        // piece anchor on the board
    uint8_t rot;         // rotation [0..3]
    TetrominoType type;
} Piece;

typedef struct {
    int drow, dcol;
} Move;

#define MOVE_LEFT  ((Move){ 0, -1})
#define MOVE_RIGHT ((Move){ 0,  1})
#define MOVE_DOWN  ((Move){-1,  0})

typedef struct {
    int drot;
} Rotation;

#define ROTATE_CW   ((Rotation) { 1 }) // clockwise
#define ROTATE_CCW  ((Rotation) {-1 }) // counter-clockwise

// Creates and returns a new empty board. All cells are initialized to 0,
// meaning no pieces are present.
Board board_create(void);

// Returns true if all cells in the given row index are occupied.
bool board_row_full(const Board *board, uint8_t row);

// Clears all cells in the specified row, setting them to 0 (empty)
void board_row_clear(Board *board, uint8_t row);

// Clears all full rows in the board and shifts above rows down.
// Returns the number of rows cleared.
int board_clear_full_rows(Board *board);

// Returns a new Piece of the given type positioned at the standard spawn location
// with rotation 0. The spawn coordinates (SPAWN_ROW, SPAWN_COL) define where the
// piece first appears on the board. The returned piece may temporarily overlap
// the top of the board, which is handled by board_piece_fits().
Piece board_piece_spawn(TetrominoType type);

// Returns true if all *filled* cells of the piece lie within the board
// and do not overlap existing board cells.
// The piece position may be temporarily out-of-bounds (e.g. during movement
// or rotation tests).
bool board_piece_fits(const Board *board, const Piece *piece);

// Merges the piece into the board by setting its filled cells.
// PRECONDITION: board_piece_fits(board, piece) == true.
// Calling this with an invalid piece is a programmer error.
void board_piece_merge(Board *board, const Piece *piece);

bool board_move_piece(const Board *board, Piece *piece, Move move);
bool board_rotate_piece(const Board *board, Piece *piece, Rotation rot);

// debug functions
void board_snapshot(const Board *board, char (*str)[BOARD_GRID_WIDTH + 1]);
void board_print_board(const Board *board);

#endif // BOARD_H
