#include <stdlib.h>
#include <tetris.h>

// clang-format off
// ref: https://gist.github.com/aprell/3722962
#define ROWS_COUNT(...) (sizeof((char *[]){ __VA_ARGS__ }) / sizeof(char *))
#define ROW_GEN(...) (char []){ __VA_ARGS__ }
#define BLOCK_GEN(...) \
	(\
		(TetrominoTemplate){\
			.pattern = ((char *[]){\
				__VA_ARGS__\
			}),\
			.width = ROWS_COUNT(__VA_ARGS__),\
		}\
	)

#define X 1
#define _ 0

typedef struct {
	char **pattern;
	int width;
} TetrominoTemplate;

static const TetrominoTemplate TetrominoTemplateArray[TETROMINO_COUNT] = {
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
	TetrominoTemplate next_shape_template = TetrominoTemplateArray[rand() % TETROMINO_COUNT];
	Tetromino next_shape;

	for (int row = 0; row < next_shape_template.width; row++) {
		for (int col = 0; col < next_shape_template.width; col++) {
			next_shape.array[row][col] = next_shape_template.pattern[row][col];
		}
	}
	next_shape.width = next_shape_template.width;
	next_shape.col = rand() % (COL_COUNT - next_shape_template.width + 1);
	next_shape.row = 0;
	return (next_shape);
}
