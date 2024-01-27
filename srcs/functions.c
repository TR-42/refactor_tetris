#include <tetris.h>

bool can_put_tetromino(const Tetromino *shape) {
	for (int shape_row = 0; shape_row < shape->width; shape_row++) {
		for (int shape_col = 0; shape_col < shape->width; shape_col++) {
			int board_col = shape->col + shape_col;
			int board_row = shape->row + shape_row;
			if ((board_col < 0 || COL_COUNT <= board_col || ROW_COUNT <= board_row)) {
				if (shape->array[shape_row][shape_col]) {
					return false;
				}
			} else if (Table[board_row][board_col] && shape->array[shape_row][shape_col]) {
				return false;
			}
		}
	}
	return true;
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
			shape->array[row_old][col_old] = temp.array[row_new][col_new];
		}
	}
}
