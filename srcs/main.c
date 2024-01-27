#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <tetris.h>

char Table[ROW_COUNT][COL_COUNT] = {0};
int final_score = 0;
static bool game_on = true;
suseconds_t time_to_next_frame_us = 400000;
static int frame_time_decrease_on_each_clear_us = 1000;

Tetromino current_shape;

static void _erase_cleared_line(int cleared_line_row) {
	for (int board_row = cleared_line_row; board_row >= 1; board_row--) {
		for (int board_col = 0; board_col < COL_COUNT; board_col++) {
			*get_table_cell_p(board_row, board_col) = *get_table_cell_p(board_row - 1, board_col);
		}
	}
	for (int board_col = 0; board_col < COL_COUNT; board_col++) {
		*get_table_cell_p(0, board_col) = 0;
	}
}

static bool _is_row_clearable(int board_row) {
	for (int board_col = 0; board_col < COL_COUNT; board_col++) {
		if (!*get_table_cell_p(board_row, board_col)) {
			return false;
		}
	}
	return true;
}

static void _put_tetromino() {
	for (int block_row = 0; block_row < current_shape.width; block_row++) {
		for (int block_col = 0; block_col < current_shape.width; block_col++) {
			if (*tetromino_get_cell_p(&current_shape, block_row, block_col)) {
				int board_row = current_shape.row + block_row;
				int board_col = current_shape.col + block_col;
				*get_table_cell_p(board_row, board_col) = *tetromino_get_cell_p(&current_shape, block_row, block_col);
			}
		}
	}
}

static void _change_tetromino() {
	current_shape = get_random_tetromino();
	if (!can_put_tetromino(&current_shape)) {
		game_on = false;
	}
}

static void _action_down(Tetromino *temp) {
	temp->row++;
	if (can_put_tetromino(temp)) {
		current_shape.row++;
	} else {
		_put_tetromino();

		for (int board_row_cursor = 0; board_row_cursor < ROW_COUNT; board_row_cursor++) {
			if (_is_row_clearable(board_row_cursor)) {
				_erase_cleared_line(board_row_cursor);
				if (0 < frame_time_decrease_on_each_clear_us) {
					time_to_next_frame_us -= frame_time_decrease_on_each_clear_us--;
				}
				final_score += 100 * COL_COUNT;
			}
		}

		_change_tetromino();
	}
}

static void _action_left(Tetromino *temp) {
	temp->col--;
	if (can_put_tetromino(temp)) {
		current_shape.col--;
	}
}
static void _action_right(Tetromino *temp) {
	temp->col++;
	if (can_put_tetromino(temp)) {
		current_shape.col++;
	}
}
static void _action_rotate(Tetromino *temp) {
	tetromino_rotate(temp);
	if (can_put_tetromino(temp)) {
		tetromino_rotate(&current_shape);
	}
}

int main() {
	srand(time(0));
	initscr();
	update_last_exec_time();
	set_timeout(1);

	current_shape = get_random_tetromino();
	if (!can_put_tetromino(&current_shape)) {
		game_on = false;
	}

	print_current_table(false);

	while (game_on) {
		int key_input = getch();
		if (key_input != ERR) {
			Tetromino temp = current_shape;
			switch (key_input) {
				case ACTION_DOWN:
					_action_down(&temp);
					break;
				case ACTION_RIGHT:
					_action_right(&temp);
					break;
				case ACTION_LEFT:
					_action_left(&temp);
					break;
				case ACTION_ROTATE:
					_action_rotate(&temp);
					break;
			}
			print_current_table(false);
		}

		if (hasToUpdate()) {
			Tetromino temp = current_shape;
			_action_down(&temp);

			print_current_table(false);
			update_last_exec_time();
		}
	}

	print_current_table(true);
	return 0;
}
