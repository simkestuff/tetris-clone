#include "game.h"

Game game_init(void)
{
    Board board = board_create();
    Piece piece = board_piece_spawn(TETROMINO_O);
    Game g = (Game) {
	.board = board,
	.piece = piece,
	.lines_cleared = 0,
	.score = 0,
	.level = 1,
	.gravity_threshold = 100,
	.gravity_timer = 0,
	.lock_delay = 25,
	.lock_timer = 0,
	.game_over = false,
    };
    return g;
}

void game_tick(Game *game)
{
    if (game->lock_timer > 0) {
	// lock_timer > 0 => piece is in lock-delay state (touching ground) 
	if (game->lock_timer >= game->lock_delay) {
	    // time for adjusting expired
	    board_piece_merge(&game->board, &game->piece);
	    game->lines_cleared += board_clear_full_rows(&game->board);
	    game->piece = board_piece_spawn(TETROMINO_O);
	    game->gravity_timer = 0;
	    if (!board_piece_fits(&game->board, &game->piece))
		game->game_over = true;
	    game->lock_timer = 0;
	} else {
	    game->lock_timer++;
	}
    } else {
	// lock_timer == 0 => piece is falling  
	game->gravity_timer++;
	if (game->gravity_timer >= game->gravity_threshold) {
	    // time for gravity to work
	    if (!board_piece_move(&game->board, &game->piece, MOVE_DOWN)) {
		// piece touched ground, still can be adjusted
		game->lock_timer = 1;
	    }
	    // start new gravity interval
	    game->gravity_timer = 0;
	    
	}
    }
}
