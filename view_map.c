#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void showPath(int** grid, int size) {
		int back;
		srand(time(NULL));
    printf("O  ");
    for (int i = 1; i < size+1; i++){
        printf("%2d  ",i);
    }

    for (int i = 0; i < size; i++) {
        printf("\n%2d ",i+1);
        for (int j = 0; j < size; j++) {
            if(j == 0 && grid[i][0] == 1){
                printf("\xF0\x9F\x86\x96  ");
            }else if(j == size-1 && grid[i][size-1] == -1){
                printf("\xF0\x9F\x8C\xBA  ");
            }else if (grid[i][j] == 1) {
                printf("\xF0\x9F\x94\xB4  ");
            }else if(grid[i][j] == 2){
                printf("\xF0\x9F\x8C\xB7  ");
            }else if( grid[i][j] == 10){
                printf("\xF0\x9F\x90\x9D  ");
            }else {
            		back=rand()%5;
            		if (back == 0) {
            				printf("\xF0\x9F\x8D\x84  ");
            		}else if (back == 1) {
            				printf("\xF0\x9F\x8D\x80  ");
            		}else if (back == 2) {
            				printf("\xF0\x9F\x8C\xB2  ");
            		}else if (back == 3) {
            				printf("\xF0\x9F\x8C\xB3  "); 	
            		}else{
            				printf("\xE2\x97\xBD  "); 	
            		}

            }
        }
        printf("\n");
    }
}
