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
	if (can_put_tetromino(temp)) {
		current.row++;
	} else {
		for (int block_row = 0; block_row < current.width; block_row++) {
			for (int block_col = 0; block_col < current.width; block_col++) {
				if (current.array[block_row][block_col]) {
					Table[current.row + block_row][current.col + block_col] = current.array[block_row][block_col];
				}
			}
		}
		int removed_line_count = 0;
		for (int board_row_cursor = 0; board_row_cursor < ROW_COUNT; board_row_cursor++) {
			int filled_block_count_one_row = 0;
			for (int board_col = 0; board_col < COL_COUNT; board_col++) {
				filled_block_count_one_row += Table[board_row_cursor][board_col];
			}
			if (filled_block_count_one_row == COL_COUNT) {
				removed_line_count++;
				for (int board_row = board_row_cursor; board_row >= 1; board_row--) {
					for (int board_col = 0; board_col < COL_COUNT; board_col++) {
						Table[board_row][board_col] = Table[board_row - 1][board_col];
					}
				}
				for (int board_col = 0; board_col < COL_COUNT; board_col++) {
					Table[0][board_col] = 0;
				}
				timer -= decrease--;
			}
		}

		final_score += 100 * removed_line_count * COL_COUNT;

		current = get_random_tetromino();
		if (!can_put_tetromino(&current)) {
			game_on = false;
		}
	}
}

static void action_left(Tetromino *temp) {
	temp->col--;
	if (can_put_tetromino(temp)) {
		current.col--;
	}
}
static void action_right(Tetromino *temp) {
	temp->col++;
	if (can_put_tetromino(temp)) {
		current.col++;
	}
}
static void action_rotate(Tetromino *temp) {
	tetromino_rotate(temp);
	if (can_put_tetromino(temp)) {
		tetromino_rotate(&current);
	}
}

int main() {
	srand(time(0));
	initscr();
	update_last_exec_time();
	set_timeout(1);

	current = get_random_tetromino();
	if (!can_put_tetromino(&current)) {
		game_on = false;
	}

	print_current_table();

	while (game_on) {
		int key_input = getch();
		if (key_input != ERR) {
			Tetromino temp = current;
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
			print_current_table();
		}

		if (hasToUpdate()) {
			Tetromino temp = current;
			action_down(&temp);

			print_current_table();
			update_last_exec_time();
		}
	}

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
