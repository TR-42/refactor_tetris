#include <ncurses.h>
#include <string.h>
#include <tetris.h>

#define _SIZEOF_CHAR_CELL (2)
#define BUF_ROW_COUNT (ROW_COUNT)
#define BUF_COL_COUNT (COL_COUNT * _SIZEOF_CHAR_CELL)
static void _set_buf_cell(
		char (*buf)[BUF_ROW_COUNT][BUF_COL_COUNT],
		int row,
		int col,
		char c
) {
	(*buf)[row][col] = c;
}
static char _get_buf_cell(
		char (*buf)[BUF_ROW_COUNT][BUF_COL_COUNT],
		int row,
		int col
) {
	return (*buf)[row][col];
}

static void _set_shape_to_buf(
		char (*buf)[BUF_ROW_COUNT][BUF_COL_COUNT],
		const char *shape,
		int row,
		int col,
		int height,
		int width
) {
	for (int shape_cursor_row = 0; shape_cursor_row < height; shape_cursor_row++) {
		int buf_row = row + shape_cursor_row;
		bool is_buf_row_in_range = (0 <= buf_row && buf_row < BUF_ROW_COUNT);
		if (!is_buf_row_in_range) {
			continue;
		}
		for (int shape_cursor_col = 0; shape_cursor_col < width; shape_cursor_col++) {
			int buf_col = (col + shape_cursor_col) * _SIZEOF_CHAR_CELL;
			bool is_buf_col_in_range = (0 <= buf_col && buf_col < BUF_COL_COUNT);
			if (!is_buf_col_in_range) {
				continue;
			}

			int shape_index = (shape_cursor_row * width) + shape_cursor_col;
			if (shape[shape_index]) {
				_set_buf_cell(buf, buf_row, buf_col, CHAR_BLOCK);
			} else if (_get_buf_cell(buf, buf_row, buf_col) != CHAR_BLOCK) {
				_set_buf_cell(buf, buf_row, buf_col, CHAR_EMPTY);
			}
		}
	}
}

static void _set_current_board_chars(
		char (*buf)[BUF_ROW_COUNT][BUF_COL_COUNT]
) {
	memset(buf, ' ', sizeof(*buf));

	_set_shape_to_buf(
			buf,
			get_board_cell_p(0, 0),
			0,
			0,
			ROW_COUNT,
			COL_COUNT
	);

	for (int row = 0; row < (BUF_ROW_COUNT - 1); row++) {
		_set_buf_cell(buf, row, BUF_COL_COUNT - 1, '\n');
	}
	_set_buf_cell(buf, BUF_ROW_COUNT - 1, BUF_COL_COUNT - 1, '\0');
}

void print_current_board(bool is_final_state) {
	static char buf[BUF_ROW_COUNT][BUF_COL_COUNT] = {0};

	_set_current_board_chars(&buf);
	if (!is_final_state) {
		_set_shape_to_buf(
				&buf,
				tetromino_get_cell_p(&current_shape, 0, 0),
				current_shape.row,
				current_shape.col,
				current_shape.width,
				BLOCK_COUNT
		);
	}

	if (is_final_state) {
		endwin();
		printf("%s\n", &(buf[0][0]));
		printf("\nGame over!\n");
		printf("\nScore: %d\n", final_score);
	} else {
		clear();
		for (int col = 0; col < COL_COUNT - ((int)sizeof(GAME_TITLE) - 1); col++) {
			printw(" ");
		}
		printw(GAME_TITLE "\n");
		printw("%s\n", &(buf[0][0]));
		printw("\nScore: %d\n", final_score);
	}
}
