#pragma once

#include <stdbool.h>
#include <sys/time.h>

#include "tetromino.h"

#define ROW_COUNT 12
#define COL_COUNT 8

#define GAME_TITLE "42 Tetris"

extern bool board_state[ROW_COUNT][COL_COUNT];
extern int final_score;
extern suseconds_t time_to_next_frame_us;
extern Tetromino current_shape;
