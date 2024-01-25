#pragma once

#include <sys/time.h>
#include <stdbool.h>

#define ROW_COUNT 8
#define COL_COUNT 6
#define BLOCK_PATTERN_COUNT 7

#define CHAR_BLOCK ('#')
#define CHAR_EMPTY ('.')

#define ACTION_DOWN ('s')
#define ACTION_LEFT ('a')
#define ACTION_RIGHT ('d')
#define ACTION_ROTATE ('w')

typedef struct {
	char **array;
	int width, row, col;
} Struct;

extern char Table[ROW_COUNT][COL_COUNT];
extern int final;
extern suseconds_t timer;
extern Struct current;

Struct	get_random_block(void);

Struct FunctionCS(Struct shape);
void FunctionDS(Struct shape);
bool FunctionCP(Struct shape);
void FunctionRS(Struct shape);
void FunctionPT();

void update_last_exec_time();
int hasToUpdate();

void set_timeout(int time);
