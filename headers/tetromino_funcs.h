#pragma once

#include "tetromino.h"

Tetromino get_random_tetromino(void);

void tetromino_change_current();

bool can_put_tetromino(const Tetromino *shape);
void tetromino_put_to_board(const Tetromino *shape);
void tetromino_rotate(Tetromino *shape);

bool *tetromino_get_cell_p(Tetromino *shape, int row, int col);
bool *get_board_cell_p(int row, int col);

void print_current_board(bool is_final_state);
