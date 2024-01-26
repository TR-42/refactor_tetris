#include <stdlib.h>
#include <tetris.h>

// clang-format off
// ref: https://gist.github.com/aprell/3722962
#define ROWS_COUNT(...) (sizeof((char *[]){ __VA_ARGS__ }) / sizeof(char *))
#define ROW_GEN(...) ((char []){ __VA_ARGS__ })
#define BLOCK_GEN(...) \
	(\
		(Tetromino){\
			.array = (char *[]){\
				__VA_ARGS__\
			},\
			.width = ROWS_COUNT(__VA_ARGS__),\
			.row = 0,\
			.col = 0\
		}\
	)

#define X 1
#define _ 0

static const Tetromino TetrominoPatternArray[TETROMINO_COUNT] = {
	BLOCK_GEN(
		ROW_GEN(_, X, X),
		ROW_GEN(X, X, _),
		ROW_GEN(_, _, _),
	),
	BLOCK_GEN(
		ROW_GEN(X, X, _),
		ROW_GEN(_, X, X),
		ROW_GEN(_, _, _),
	),
	BLOCK_GEN(
		ROW_GEN(_, X, _),
		ROW_GEN(X, X, X),
		ROW_GEN(_, _, _),
	),
	BLOCK_GEN(
		ROW_GEN(_, _, X),
		ROW_GEN(X, X, X),
		ROW_GEN(_, _, _),
	),
	BLOCK_GEN(
		ROW_GEN(X, _, _),
		ROW_GEN(X, X, X),
		ROW_GEN(_, _, _),
	),
	BLOCK_GEN(
		ROW_GEN(X, X),
		ROW_GEN(X, X),
	),
	BLOCK_GEN(
		ROW_GEN(_, _, _, _),
		ROW_GEN(X, X, X, X),
		ROW_GEN(_, _, _, _),
		ROW_GEN(_, _, _, _),
	),
};
// clang-format on

Tetromino get_random_tetromino(void) {
	Tetromino next_shape = TetrominoPatternArray[rand() % TETROMINO_COUNT];

	next_shape.col = rand() % (COL_COUNT - next_shape.width + 1);
	next_shape.row = 0;
	return (next_shape);
}
