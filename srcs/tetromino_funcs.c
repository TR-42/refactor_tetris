#include <tetris.h>

bool can_put_tetromino(const Tetromino *shape) {
	for (int shape_row = 0; shape_row < shape->width; shape_row++) {
		for (int shape_col = 0; shape_col < shape->width; shape_col++) {
			int board_col = shape->col + shape_col;
			int board_row = shape->row + shape_row;
			bool is_board_row_col_out_of_range = (board_col < 0 || COL_COUNT <= board_col || board_row < 0 || ROW_COUNT <= board_row);
			if (is_board_row_col_out_of_range) {
				if (*tetromino_get_cell_p((Tetromino *)shape, shape_row, shape_col)) {
					return false;
				}
			} else if (*get_table_cell_p(board_row, board_col) && *tetromino_get_cell_p((Tetromino *)shape, shape_row, shape_col)) {
				return false;
			}
		}
	}
	return true;
}

void tetromino_put_to_table(const Tetromino *shape) {
	for (int block_row = 0; block_row < shape->width; block_row++) {
		for (int block_col = 0; block_col < shape->width; block_col++) {
			if (*tetromino_get_cell_p((Tetromino *)shape, block_row, block_col)) {
				int board_row = shape->row + block_row;
				int board_col = shape->col + block_col;
				*get_table_cell_p(board_row, board_col) = *tetromino_get_cell_p((Tetromino *)shape, block_row, block_col);
			}
		}
	}
}

void tetromino_rotate(Tetromino *shape) {
	Tetromino temp = *shape;
	int width = shape->width;
	for (
			int row_old = 0, col_new = 0;
			row_old < width;
			col_new = ++row_old
	) {
		for (
				int col_old = 0, row_new = width - 1;
				col_old < width;
				row_new = width - ++col_old - 1
		) {
			*tetromino_get_cell_p(shape, row_old, col_old) = *tetromino_get_cell_p(&temp, row_new, col_new);
		}
	}
}

char *tetromino_get_cell_p(Tetromino *shape, int row, int col) {
	return &(shape->array[row][col]);
}

char *get_table_cell_p(int row, int col) {
	return &(Table[row][col]);
}
