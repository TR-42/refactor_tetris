#include <stdlib.h>

#include <tetris.h>

// ref: https://gist.github.com/aprell/3722962
#define ROWS_COUNT(...) (sizeof((char *[]){ __VA_ARGS__ }) / sizeof(char *))
#define ROW_GEN(...) ((char []){ __VA_ARGS__ })
#define BLOCK_GEN(...) \
	(\
		(Struct){\
			.array = (char *[]){\
				__VA_ARGS__\
			},\
			.width = ROWS_COUNT(__VA_ARGS__),\
			.row = 0,\
			.col = 0\
		}\
	)

const Struct StructsArray[BLOCK_PATTERN_COUNT] = {
	BLOCK_GEN(
		ROW_GEN(0, 1, 1),
		ROW_GEN(1, 1, 0),
		ROW_GEN(0, 0, 0),
	),
	BLOCK_GEN(
		ROW_GEN(1, 1, 0),
		ROW_GEN(0, 1, 1),
		ROW_GEN(0, 0, 0),
	),
	BLOCK_GEN(
		ROW_GEN(0, 1, 0),
		ROW_GEN(1, 1, 1),
		ROW_GEN(0, 0, 0),
	),
	BLOCK_GEN(
		ROW_GEN(0, 0, 1),
		ROW_GEN(1, 1, 1),
		ROW_GEN(0, 0, 0),
	),
	BLOCK_GEN(
		ROW_GEN(1, 0, 0),
		ROW_GEN(1, 1, 1),
		ROW_GEN(0, 0, 0),
	),
	BLOCK_GEN(
		ROW_GEN(1, 1),
		ROW_GEN(1, 1),
	),
	BLOCK_GEN(
		ROW_GEN(0, 0, 0, 0),
		ROW_GEN(1, 1, 1, 1),
		ROW_GEN(0, 0, 0, 0),
		ROW_GEN(0, 0, 0, 0),
	),
};

Struct	get_random_block(void)
{
	return (StructsArray[rand() % BLOCK_PATTERN_COUNT]);
}
