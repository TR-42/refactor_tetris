#include <stdlib.h>
#include <ncurses.h>

#include <tetris.h>

char Table[ROW_COUNT][COL_COUNT] = {0};
int final = 0;
char GameOn = true;
suseconds_t timer = 400000;
int decrease = 1000;

Tetromino current;

static void action_down(
	Tetromino *temp
) {
	temp->row++;  //move down
	if(can_put_tetromino(*temp))
		current.row++;
	else {
		int i, j;
		for(i = 0; i < current.width ;i++){
			for(j = 0; j < current.width ; j++){
				if(current.array[i][j])
					Table[current.row+i][current.col+j] = current.array[i][j];
			}
		}
		int n, m, sum, count=0;
		for(n=0;n<ROW_COUNT;n++){
			sum = 0;
			for(m=0;m< COL_COUNT;m++) {
				sum+=Table[n][m];
			}
			if(sum==COL_COUNT){
				count++;
				int l, k;
				for(k = n;k >=1;k--)
					for(l=0;l<COL_COUNT;l++)
						Table[k][l]=Table[k-1][l];
				for(l=0;l<COL_COUNT;l++)
					Table[k][l]=0;
				timer-=decrease--;
			}
		}
		final += 100*count;
		Tetromino new_shape = tetromino_clone(get_random_tetromino());
		tetromino_dispose(current);
		current = new_shape;
		if(!can_put_tetromino(current)){
			GameOn = false;
		}
	}
}

void action_left(
	Tetromino *temp
) {
	temp->col--;
	if(can_put_tetromino(*temp))
		current.col--;
}
void action_right(
	Tetromino *temp
) {
	temp->col++;
	if(can_put_tetromino(*temp))
		current.col++;
}
void action_rotate(
	Tetromino *temp
) {
	tetromino_rotate(*temp);
	if(can_put_tetromino(*temp))
		tetromino_rotate(current);
}

int main() {
	srand(time(0));
	final = 0;
	int c;
	initscr();
	update_last_exec_time();
	set_timeout(1);
	Tetromino new_shape = tetromino_clone(get_random_tetromino());
	tetromino_dispose(current);
	current = new_shape;
	if(!can_put_tetromino(current)){
		GameOn = false;
	}
	print_current_table();
	while(GameOn){
		if ((c = getch()) != ERR) {
			Tetromino temp = tetromino_clone(current);
			switch(c){
				case ACTION_DOWN:
					action_down(&temp);
					break;
				case ACTION_RIGHT:
					action_right(&temp);
					break;
				case ACTION_LEFT:
					action_left(&temp);
					break;
				case ACTION_ROTATE:
					action_rotate(&temp);
					break;
			}
			tetromino_dispose(temp);
			print_current_table();
		}
		if (hasToUpdate()) {
			Tetromino temp = tetromino_clone(current);
			action_down(&temp);
	
			tetromino_dispose(temp);
			print_current_table();
			update_last_exec_time();
		}
	}
	tetromino_dispose(current);
	endwin();
	int i, j;
	for(i = 0; i < ROW_COUNT ;i++){
		for(j = 0; j < COL_COUNT ; j++){
			printf("%c ", Table[i][j] ? CHAR_BLOCK : CHAR_EMPTY);
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
	return 0;
}
