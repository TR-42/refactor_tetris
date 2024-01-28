#include <action_funcs.h>
#include <tetris.h>
#include <tetromino.h>
#include <tetromino_funcs.h>

suseconds_t time_to_next_frame_us = 400000;
static int frame_time_decrease_on_each_clear_us = 1000;

static void _erase_cleared_line(int cleared_line_row) {
	for (int board_row = cleared_line_row; board_row >= 1; board_row--) {
		for (int board_col = 0; board_col < COL_COUNT; board_col++) {
			*get_board_cell_p(board_row, board_col) = *get_board_cell_p(board_row - 1, board_col);
		}
	}
	for (int board_col = 0; board_col < COL_COUNT; board_col++) {
		*get_board_cell_p(0, board_col) = 0;
	}
}

static bool _is_row_clearable(int board_row) {
	for (int board_col = 0; board_col < COL_COUNT; board_col++) {
		if (!*get_board_cell_p(board_row, board_col)) {
			return false;
		}
	}
	return true;
}

static void _erase_clearable_lines() {
	for (int board_row_cursor = 0; board_row_cursor < ROW_COUNT; board_row_cursor++) {
		if (_is_row_clearable(board_row_cursor)) {
			_erase_cleared_line(board_row_cursor);
			if (0 < frame_time_decrease_on_each_clear_us) {
				time_to_next_frame_us -= frame_time_decrease_on_each_clear_us--;
			}
			final_score += 100 * COL_COUNT;
		}
	}
}

void action_down(Tetromino *temp) {
	temp->row++;
	if (can_put_tetromino(temp)) {
		current_shape.row++;
	} else {
		tetromino_put_to_board(&current_shape);

		_erase_clearable_lines();

		tetromino_change_current();
	}
}

void action_left(Tetromino *temp) {
	temp->col--;
	if (can_put_tetromino(temp)) {
		current_shape.col--;
	}
}
void action_right(Tetromino *temp) {
	temp->col++;
	if (can_put_tetromino(temp)) {
		current_shape.col++;
	}
}
void action_rotate(Tetromino *temp) {
	tetromino_rotate(temp);
	if (can_put_tetromino(temp)) {
		current_shape = *temp;
	}
}
