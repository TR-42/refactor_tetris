#include <ncurses.h>
#include <stdlib.h>
#include <tetris.h>

Tetromino tetromino_clone(Tetromino shape) {
	Tetromino new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char **)malloc(new_shape.width * sizeof(char *));
	for (int row = 0; row < new_shape.width; row++) {
		new_shape.array[row] = (char *)malloc(new_shape.width * sizeof(char));
		for (int col = 0; col < new_shape.width; col++) {
			new_shape.array[row][col] = copyshape[row][col];
		}
	}
	return new_shape;
}

void tetromino_dispose(Tetromino shape) {
	for (int row = 0; row < shape.width; row++) {
		free(shape.array[row]);
	}
	free(shape.array);
}

bool can_put_tetromino(Tetromino shape) {
	char **array = shape.array;
	for (int row = 0; row < shape.width; row++) {
		for (int col = 0; col < shape.width; col++) {
			if ((shape.col + col < 0 || shape.col + col >= COL_COUNT || shape.row + row >= ROW_COUNT)) {
				if (array[row][col])
					return false;

			} else if (Table[shape.row + row][shape.col + col] && array[row][col])
				return false;
		}
	}
	return true;
}

void tetromino_rotate(Tetromino shape) {
	Tetromino temp = tetromino_clone(shape);
	int width;
	width = shape.width;
	for (
			int row_old = 0, col_new = 0;
			row_old < width;
			col_new = ++row_old) {
		for (
				int col_old = 0, row_new = width - 1;
				col_old < width;
				row_new = width - ++col_old - 1) {
			shape.array[row_old][col_old] = temp.array[row_new][col_new];
		}
	}
	tetromino_dispose(temp);
}

void print_current_table() {
	char Buffer[ROW_COUNT][COL_COUNT] = {0};
	for (int row = 0; row < current.width; row++) {
		for (int col = 0; col < current.width; col++) {
			if (current.array[row][col])
				Buffer[current.row + row][current.col + col] = current.array[row][col];
		}
	}
	clear();
	for (int col = 0; col < COL_COUNT - (sizeof(GAME_TITLE) - 1); col++)
		printw(" ");
	printw(GAME_TITLE "\n");
	for (int row = 0; row < ROW_COUNT; row++) {
		for (int col = 0; col < COL_COUNT; col++) {
			printw("%c ", (Table[row][col] + Buffer[row][col]) ? CHAR_BLOCK : CHAR_EMPTY);
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final_score);
}