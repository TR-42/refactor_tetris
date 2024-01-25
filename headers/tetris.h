#pragma once

#include <sys/time.h>
#include <stdbool.h>

#define ROW_COUNT 20
#define COL_COUNT 15

typedef struct {
	char **array;
	int width, row, col;
} Struct;

extern char Table[ROW_COUNT][COL_COUNT];
extern int final;
extern suseconds_t timer;
extern Struct current;

extern struct timeval before_now, now;

Struct FunctionCS(Struct shape);
void FunctionDS(Struct shape);
bool FunctionCP(Struct shape);
void FunctionRS(Struct shape);
void FunctionPT();

int hasToUpdate();

void set_timeout(int time);
