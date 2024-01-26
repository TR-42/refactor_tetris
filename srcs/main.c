#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <tetris.h>

char Table[ROW_COUNT][COL_COUNT] = {0};
int final_score = 0;
static bool game_on = true;
suseconds_t timer = 400000;
static int decrease = 1000;

Tetromino current;

static void action_down(Tetromino *temp) {
	temp->row++;	// move down
	if (can_put_tetromino(*temp)) {
		current.row++;
	} else {
		for (int row = 0; row < current.width; row++) {
			for (int col = 0; col < current.width; col++) {
				if (current.array[row][col])
					Table[current.row + row][current.col + col] = current.array[row][col];
			}
		}
		int removed_line_count = 0;
		for (int current_row = 0; current_row < ROW_COUNT; current_row++) {
			int filled_block_count_one_row = 0;
			for (int col = 0; col < COL_COUNT; col++) {
				filled_block_count_one_row += Table[current_row][col];
			}
			if (filled_block_count_one_row == COL_COUNT) {
				removed_line_count++;
				for (int row = current_row; row >= 1; row--) {
					for (int col = 0; col < COL_COUNT; col++) {
						Table[row][col] = Table[row - 1][col];
					}
				}
				for (int col = 0; col < COL_COUNT; col++) {
					Table[current_row][col] = 0;
				}
				timer -= decrease--;
			}
		}

		final_score += 100 * removed_line_count;

		Tetromino new_shape = tetromino_clone(get_random_tetromino());
		tetromino_dispose(current);
		current = new_shape;
		if (!can_put_tetromino(current)) {
			game_on = false;
		}
	}
}

static void action_left(Tetromino *temp) {
	temp->col--;
	if (can_put_tetromino(*temp)) {
		current.col--;
	}
}
static void action_right(Tetromino *temp) {
	temp->col++;
	if (can_put_tetromino(*temp)) {
		current.col++;
	}
}
static void action_rotate(Tetromino *temp) {
	tetromino_rotate(*temp);
	if (can_put_tetromino(*temp)) {
		tetromino_rotate(current);
	}
}

int main() {
	srand(time(0));
	initscr();
	update_last_exec_time();
	set_timeout(1);

	Tetromino new_shape = tetromino_clone(get_random_tetromino());
	tetromino_dispose(current);
	current = new_shape;
	if (!can_put_tetromino(current)) {
		game_on = false;
	}

	print_current_table();

	while (game_on) {
		int key_input = getch();
		if (key_input != ERR) {
			Tetromino temp = tetromino_clone(current);
			switch (key_input) {
				case ACTION_DOWN:
					action_down(&temp);
					break;
				case ACTION_RIGHT:
					action_right(&temp);
					break;
				case ACTION_LEFT:
					action_left(&temp);
					break;
				case ACTION_ROTATE:
					action_rotate(&temp);
					break;
			}

			tetromino_dispose(temp);
			print_current_table();
		}

		if (hasToUpdate()) {
			Tetromino temp = tetromino_clone(current);
			action_down(&temp);

			tetromino_dispose(temp);
			print_current_table();
			update_last_exec_time();
		}
	}

	tetromino_dispose(current);
	endwin();
	for (int row = 0; row < ROW_COUNT; row++) {
		for (int col = 0; col < COL_COUNT; col++) {
			printf("%c ", Table[row][col] ? CHAR_BLOCK : CHAR_EMPTY);
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final_score);
	return 0;
}
