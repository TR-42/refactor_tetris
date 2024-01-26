#include <stdlib.h>
#include <ncurses.h>

#include <tetris.h>

Tetromino tetromino_clone(Tetromino shape){
	Tetromino new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
	int i, j;
	for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
	}
	return new_shape;
}

void tetromino_dispose(Tetromino shape){
	int i;
	for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}

bool can_put_tetromino(Tetromino shape){
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= COL_COUNT || shape.row+i >= ROW_COUNT)){
				if(array[i][j])
					return false;
				
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return false;
		}
	}
	return true;
}

void tetromino_rotate(Tetromino shape){
	Tetromino temp = tetromino_clone(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	tetromino_dispose(temp);
}

void print_current_table(){
	char Buffer[ROW_COUNT][COL_COUNT] = {0};
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	clear();
	for(i=0; i<COL_COUNT-9; i++)
	printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < ROW_COUNT ;i++){
		for(j = 0; j < COL_COUNT ; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? CHAR_BLOCK: CHAR_EMPTY);
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}