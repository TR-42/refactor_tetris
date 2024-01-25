#include <stdlib.h>
#include <ncurses.h>

#include <tetris.h>

char Table[ROW_COUNT][COL_COUNT] = {0};
int final = 0;
char GameOn = true;
suseconds_t timer = 400000;
int decrease = 1000;

Struct current;

int main() {
    srand(time(0));
    final = 0;
    int c;
    initscr();
	update_last_exec_time();
	set_timeout(1);
	Struct new_shape = FunctionCS(get_random_block());
    new_shape.col = rand()%(COL_COUNT-new_shape.width+1);
    new_shape.row = 0;
    FunctionDS(current);
	current = new_shape;
	if(!FunctionCP(current)){
		GameOn = false;
	}
    FunctionPT();
	while(GameOn){
		if ((c = getch()) != ERR) {
			Struct temp = FunctionCS(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(FunctionCP(temp))
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
						Struct new_shape = FunctionCS(get_random_block());
						new_shape.col = rand()%(COL_COUNT-new_shape.width+1);
						new_shape.row = 0;
						FunctionDS(current);
						current = new_shape;
						if(!FunctionCP(current)){
							GameOn = false;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp);
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			FunctionDS(temp);
			FunctionPT();
		}
		if (hasToUpdate()) {
			Struct temp = FunctionCS(current);
			switch('s'){
				case 's':
					temp.row++;
					if(FunctionCP(temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									Table[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum;
						for(n=0;n<ROW_COUNT;n++){
							sum = 0;
							for(m=0;m< COL_COUNT;m++) {
								sum+=Table[n][m];
							}
							if(sum==COL_COUNT){
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<COL_COUNT;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<COL_COUNT;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						Struct new_shape = FunctionCS(get_random_block());
						new_shape.col = rand()%(COL_COUNT-new_shape.width+1);
						new_shape.row = 0;
						FunctionDS(current);
						current = new_shape;
						if(!FunctionCP(current)){
							GameOn = false;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp);
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			FunctionDS(temp);
			FunctionPT();
			update_last_exec_time();
		}
	}
	FunctionDS(current);
	endwin();
	int i, j;
	for(i = 0; i < ROW_COUNT ;i++){
		for(j = 0; j < COL_COUNT ; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
    return 0;
}
