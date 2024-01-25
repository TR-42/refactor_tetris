#pragma once

#include <sys/time.h>

#define R 20
#define C 15
#define T 1
#define F 0

typedef struct {
	char **array;
	int width, row, col;
} Struct;

extern char Table[R][C];
extern int final;
extern suseconds_t timer;
extern Struct current;

extern struct timeval before_now, now;

Struct FunctionCS(Struct shape);
void FunctionDS(Struct shape);
int FunctionCP(Struct shape);
void FunctionRS(Struct shape);
void FunctionPT();

int hasToUpdate();

void set_timeout(int time);
