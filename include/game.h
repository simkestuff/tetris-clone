#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    Board board;
    Piece piece;
    int lines_cleared;
    int score;
    int level;
    int gravity_threshold; // if timer reach it try move piece down 
    int gravity_timer;     // run against treshold
    int lock_delay;        // after grounding how long piece can be adjusted
    int lock_timer;        // if reach delay touching ground turns into locking
    bool game_over;
} Game;

Game game_init(void);

// it runs every timeframe != gravity timing
void game_tick(Game *game);

#endif // GAME_H
