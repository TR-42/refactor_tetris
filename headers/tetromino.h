#pragma once

#include <stdbool.h>

#define BLOCK_COUNT 4

typedef struct {
	bool array[BLOCK_COUNT][BLOCK_COUNT];
	int width;
	int row;
	int col;
} Tetromino;
