#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <tetris.h>

bool board_state[ROW_COUNT][COL_COUNT] = {0};
int final_score = 0;

Tetromino current_shape;

int main() {
	srand(time(0));
	initscr();
	update_last_exec_time();
	set_key_read_timeout(1);

	tetromino_change_current();

	// 最初からゲーム続行不能な場合があるため、その場合は出力を行わない
	if (is_game_on()) {
		print_current_board(false);
	}

	while (is_game_on()) {
		int key_input = getch();
		bool is_input_available = (key_input != ERR);
		if (is_input_available) {
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
			print_current_board(false);
		}

		if (is_time_to_update()) {
			Tetromino temp = current_shape;
			action_down(&temp);

			print_current_board(false);
			update_last_exec_time();
		}
	}

	print_current_board(true);
	return 0;
}
