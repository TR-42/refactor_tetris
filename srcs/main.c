#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <tetris.h>

char Table[ROW_COUNT][COL_COUNT] = {0};
int final_score = 0;

Tetromino current_shape;

int main() {
	srand(time(0));
	initscr();
	update_last_exec_time();
	set_timeout(1);

	change_tetromino();

	if (is_game_on()) {
		print_current_table(false);
	}

	while (is_game_on()) {
		int key_input = getch();
		if (key_input != ERR) {
			Tetromino temp = current_shape;
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
			print_current_table(false);
		}

		if (hasToUpdate()) {
			Tetromino temp = current_shape;
			action_down(&temp);

			print_current_table(false);
			update_last_exec_time();
		}
	}

	print_current_table(true);
	return 0;
}
