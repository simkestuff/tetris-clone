#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdint.h>
#include <assert.h>

/*
  col 0  1  2  3
  bit 15 14 13 12   row 3
  bit 11 10 09 08   row 2
  bit 07 06 05 04   row 1
  bit 03 02 01 00   row 0

  bit = row*4 + (3 - col)
 */

#define TETROMINO_BIT(row,col) (1u << ((row)*4 + (3 - (col))))


typedef struct {
    uint16_t mask[4];
} Tetromino;

typedef enum {
    TETROMINO_I,
    TETROMINO_O,
    TETROMINO_T,
    TETROMINO_S,
    TETROMINO_Z,
    TETROMINO_J,
    TETROMINO_L,
    TETROMINO_COUNT,
    
} TetrominoType;



// hand made masks representation of tetrominos
// will not be used
// static const Tetromino tetrominos[TETROMINO_COUNT] = {
//     // TETROMINO_I
//     {{ 0x0F00, 0x2222, 0x00F0, 0x4444 }},
//     // TETROMINO_O
//     {{ 0x6600, 0x6600, 0x6600, 0x6600 }},
//     // TETROMINO_T
//     {{ 0x0E40, 0x4C40, 0x4E00, 0x4640 }},
//     // TETROMINO_S
//     {{ 0x06C0, 0x8C40, 0x06C0, 0x08C4 }},
//     // TETROMINO_Z
//     {{ 0x0C60, 0x4C80, 0x0C60, 0x4C80 }},
//     // TETROMINO_J
//     {{ 0x08E0, 0x6440, 0x0E20, 0x44C0 }},
//     // TETROMINO_L
//     {{ 0x02E0, 0x4460, 0x0E80, 0xC440 }},
// };

static Tetromino tetrominos[TETROMINO_COUNT];



// Tetrominos made programatically instead of hand made
//
// Tetromino as 4x4 grid
//  +-------------------------------+
//  | (3,0) | (3,1) | (3,2) | (3,3) |
//  +-------------------------------+
//  | (2,0) | (2,1) | (2,2) | (2,3) |
//  +-------------------------------+
//  | (1,0) | (1,1) | (1,2) | (1,3) |
//  +-------------------------------+
//  | (0,0) | (0,1) | (0,2) | (0,3) |
//  +-------------------------------+

typedef struct {
    size_t row, col;
} Cell;

typedef struct {
    Cell cells[4];
} TetrominoShape;

static const TetrominoShape shape_I = { .cells = { (Cell) {0,2},(Cell) {1,2},(Cell) {2,2},(Cell) {3,2} } };
static const TetrominoShape shape_O = { .cells = { (Cell) {3,2},(Cell) {3,1},(Cell) {2,2},(Cell) {2,1} } };
static const TetrominoShape shape_T = { .cells = { (Cell) {2,0},(Cell) {2,1},(Cell) {2,2},(Cell) {1,1} } };
static const TetrominoShape shape_S = { .cells = { (Cell) {1,0},(Cell) {1,1},(Cell) {2,1},(Cell) {2,2} } };
static const TetrominoShape shape_Z = { .cells = { (Cell) {1,1},(Cell) {1,2},(Cell) {2,0},(Cell) {2,1} } };
static const TetrominoShape shape_J = { .cells = { (Cell) {1,0},(Cell) {1,1},(Cell) {1,2},(Cell) {2,0} } };
static const TetrominoShape shape_L = { .cells = { (Cell) {1,0},(Cell) {1,1},(Cell) {1,2},(Cell) {2,2} } };

static const TetrominoShape shapes[TETROMINO_COUNT] = {
    shape_I,
    shape_O,
    shape_T,
    shape_S,
    shape_Z,
    shape_J,
    shape_L,
};

uint16_t tetromino_shape_to_mask(const TetrominoShape *shape);
TetrominoShape tetromino_rotate_shape_clockwise(const TetrominoShape *shape);
void tetromino_normalize_shape(TetrominoShape *shape); // anchor tetromino to bottom left position
void tetromino_generate(const TetrominoShape *base, Tetromino *out);

//
// End of part for programatically made Tetrominos

// debugging functions
void tetromino_dump_mask(uint16_t mask);
void tetromino_validate(uint16_t mask);

#endif // TETROMINO_H
