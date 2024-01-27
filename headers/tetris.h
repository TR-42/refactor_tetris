#pragma once

#include <stdbool.h>
#include <sys/time.h>

#define ROW_COUNT 12
#define COL_COUNT 8
#define TETROMINO_COUNT 7
#define BLOCK_COUNT 4

#define CHAR_BLOCK ('#')
#define CHAR_EMPTY ('.')

#define ACTION_DOWN ('s')
#define ACTION_LEFT ('a')
#define ACTION_RIGHT ('d')
#define ACTION_ROTATE ('w')

#define GAME_TITLE "42 Tetris"

typedef struct {
	char array[BLOCK_COUNT][BLOCK_COUNT];
	int width;
	int row;
	int col;
} Tetromino;

extern char Table[ROW_COUNT][COL_COUNT];
extern int final_score;
extern suseconds_t time_to_next_frame_us;
extern Tetromino current_shape;

Tetromino get_random_tetromino(void);

bool can_put_tetromino(const Tetromino *shape);
void tetromino_put_to_table(const Tetromino *shape);
void tetromino_rotate(Tetromino *shape);
char *tetromino_get_cell_p(Tetromino *shape, int row, int col);
char *get_table_cell_p(int row, int col);
void print_current_table(bool is_final_state);

void update_last_exec_time();
int hasToUpdate();

void set_timeout(int time);

bool is_game_on();
void change_tetromino();
void action_down(Tetromino *temp);
void action_left(Tetromino *temp);
void action_right(Tetromino *temp);
void action_rotate(Tetromino *temp);
