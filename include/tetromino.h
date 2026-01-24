#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdint.h>

/* bit mask
  col 0  1  2  3
  bit 15 14 13 12   row 3
  bit 11 10 09 08   row 2
  bit 07 06 05 04   row 1
  bit 03 02 01 00   row 0

  bit = row*4 + (3 - col)
 */

#define TETROMINO_BIT(row,col) (1u << ((row)*4 + (3 - (col))))

#define TETROMINO_GRID_SIZE 4

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


static const Tetromino tetrominos[TETROMINO_COUNT] = {
    // TETROMINO_I
    {{ 0x0F00, 0x2222, 0x00F0, 0x4444 }},
    // TETROMINO_O
    {{ 0x6600, 0x6600, 0x6600, 0x6600 }},
    // TETROMINO_T
    {{ 0x0E40, 0x4C40, 0x4E00, 0x4640 }},
    // TETROMINO_S
    {{ 0x06C0, 0x8C40, 0x06C0, 0x08C4 }},
    // TETROMINO_Z
    {{ 0x0C60, 0x4C80, 0x0C60, 0x4C80 }},
    // TETROMINO_J
    {{ 0x08E0, 0x6440, 0x0E20, 0x44C0 }},
    // TETROMINO_L
    {{ 0x02E0, 0x4460, 0x0E80, 0xC440 }},
};


// debugging functions
void tetromino_dump_mask(uint16_t mask);
void tetromino_validate(uint16_t mask);

#endif // TETROMINO_H
