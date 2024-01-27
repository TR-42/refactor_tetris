#include <ncurses.h>
#include <string.h>
#include <tetris.h>

#define _SIZEOF_CHAR_CELL (2)
static void _set_buf_cell(
		char (*buf)[ROW_COUNT][COL_COUNT * _SIZEOF_CHAR_CELL],
		int row,
		int col,
		char c
) {
	(*buf)[row][col] = c;
}
static char _get_buf_cell(
		char (*buf)[ROW_COUNT][COL_COUNT * _SIZEOF_CHAR_CELL],
		int row,
		int col
) {
	return (*buf)[row][col];
}

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
				_set_buf_cell(buf, buf_row, buf_col, CHAR_BLOCK);
			} else if (_get_buf_cell(buf, buf_row, buf_col) != CHAR_BLOCK) {
				_set_buf_cell(buf, buf_row, buf_col, CHAR_EMPTY);
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
			&(Table[0][0]),
			0,
			0,
			ROW_COUNT,
			COL_COUNT
	);

	for (int row = 0; row < (ROW_COUNT - 1); row++) {
		_set_buf_cell(buf, row, (COL_COUNT * _SIZEOF_CHAR_CELL) - 1, '\n');
	}
	_set_buf_cell(buf, ROW_COUNT - 1, (COL_COUNT * _SIZEOF_CHAR_CELL) - 1, '\0');
}

void print_current_table() {
	static char buf[ROW_COUNT][COL_COUNT * _SIZEOF_CHAR_CELL] = {0};

	_set_current_table_chars(&buf);

	_set_shape_to_buf(
			&buf,
			&(current_shape.array[0][0]),
			current_shape.row,
			current_shape.col,
			current_shape.width,
			BLOCK_COUNT
	);

	clear();
	for (int col = 0; col < COL_COUNT - ((int)sizeof(GAME_TITLE) - 1); col++) {
		printw(" ");
	}
	printw(GAME_TITLE "\n");
	printw("%s\n", buf);
	printw("\nScore: %d\n", final_score);
}
