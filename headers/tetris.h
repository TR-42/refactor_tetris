#pragma once

#include <stdbool.h>
#include <sys/time.h>

#define ROW_COUNT 8
#define COL_COUNT 6
#define TETROMINO_COUNT 7

#define CHAR_BLOCK ('#')
#define CHAR_EMPTY ('.')

#define ACTION_DOWN ('s')
#define ACTION_LEFT ('a')
#define ACTION_RIGHT ('d')
#define ACTION_ROTATE ('w')

#define GAME_TITLE "42 Tetris"

typedef struct {
	char **array;
	int width, row, col;
} Tetromino;

extern char Table[ROW_COUNT][COL_COUNT];
extern int final_score;
extern suseconds_t timer;
extern Tetromino current;

Tetromino get_random_tetromino(void);

Tetromino tetromino_clone(Tetromino shape);
void tetromino_dispose(Tetromino shape);
bool can_put_tetromino(Tetromino shape);
void tetromino_rotate(Tetromino shape);
void print_current_table();

void update_last_exec_time();
int hasToUpdate();

void set_timeout(int time);
