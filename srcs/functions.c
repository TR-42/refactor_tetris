#include <ncurses.h>
#include <string.h>
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

#define _SIZEOF_CHAR_CELL (2)
static void _set_shape_to_buf(
		char (*buf)[ROW_COUNT][COL_COUNT * _SIZEOF_CHAR_CELL],
		const char *shape,
		int row,
		int col,
		int height,
		int width
) {
	for (int shape_cursor_row = 0; shape_cursor_row < height; shape_cursor_row++) {
		for (int shape_cursor_col = 0; shape_cursor_col < width; shape_cursor_col++) {
			int shape_index = (shape_cursor_row * width) + shape_cursor_col;
			int buf_row = row + shape_cursor_row;
			int buf_col = (col + shape_cursor_col) * _SIZEOF_CHAR_CELL;
			if (shape[shape_index]) {
				(*buf)[buf_row][buf_col] = CHAR_BLOCK;
			} else if ((*buf)[buf_row][buf_col] != CHAR_BLOCK) {
				(*buf)[buf_row][buf_col] = CHAR_EMPTY;
			}
		}
	}
}

static void _set_current_table_chars(
		char (*buf)[ROW_COUNT][COL_COUNT * _SIZEOF_CHAR_CELL]
) {
	memset(buf, ' ', ROW_COUNT * COL_COUNT * _SIZEOF_CHAR_CELL);

	_set_shape_to_buf(
			buf,
			&(current_shape.array[0][0]),
			current_shape.row,
			current_shape.col,
			current_shape.width,
			BLOCK_COUNT
	);
	_set_shape_to_buf(
			buf,
			&(Table[0][0]),
			0,
			0,
			ROW_COUNT,
			COL_COUNT
	);

	for (int row = 0; row < (ROW_COUNT - 1); row++) {
		(*buf)[row][(COL_COUNT * _SIZEOF_CHAR_CELL) - 1] = '\n';
	}
	(*buf)[ROW_COUNT - 1][(COL_COUNT * _SIZEOF_CHAR_CELL) - 1] = '\0';
}

void print_current_table() {
	static char buf[ROW_COUNT][COL_COUNT * _SIZEOF_CHAR_CELL] = {0};

	_set_current_table_chars(&buf);

	clear();
	for (int col = 0; col < COL_COUNT - ((int)sizeof(GAME_TITLE) - 1); col++) {
		printw(" ");
	}
	printw(GAME_TITLE "\n");
	printw("%s\n", buf);
	printw("\nScore: %d\n", final_score);
}
