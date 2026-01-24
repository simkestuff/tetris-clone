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

