#pragma once

#include "tetromino.h"

#define ACTION_DOWN ('s')
#define ACTION_LEFT ('a')
#define ACTION_RIGHT ('d')
#define ACTION_ROTATE ('w')

bool is_game_on();
void action_down(Tetromino *temp);
void action_left(Tetromino *temp);
void action_right(Tetromino *temp);
void action_rotate(Tetromino *temp);
