#include "Biblio.h"


int** generatePath(int* s, Position** pos, int* sizeofpos) {
    int size;
    printf("What is the size of the map (11 - 51)? : ");
    scanf("%d", &size);
    clear_input_buffer();
    if (size < 11 || size > 51) {
        printf("Size must be between 11 and 99.\n");
        exit(1);
    }
    // Get size 
    *s = size;
    srand(time(NULL));	
    
    int** grid = malloc(size * sizeof(int*));
    if (grid == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(2);
    }

    for (int i = 0; i < size; i++) {
        grid[i] = malloc(size * sizeof(int));
        if (grid[i] == NULL) {
            printf("Erreur d'allocation mémoire pour la ligne %d.\n", i);
            exit(3);
        }
    }
    // Creat **grid for stock the path

    int currentRow = rand() % (size/3) +size/3;  
    int lastDirection = 0;
    int pastDirection = 0; 
    


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }
    
    int col = 1;
    int direction;
    grid[currentRow][0] = 100;
    grid[currentRow][1] = 1;
    
    Position* posBis = malloc(sizeof(Position) * 2 * size); // Temporary allowance for positions
    *sizeofpos = 2;
    posBis[0].x = 0;
    posBis[0].y = currentRow;    
    posBis[1].x = 1;
    posBis[1].y = currentRow;
    
    while (col != 0) {
        direction = rand() % 3; 

        if (direction == 1 && currentRow > 3 && pastDirection!=2 && lastDirection != 2) {  
            currentRow--;
            grid[currentRow][col] = 1;
            posBis[*sizeofpos].x = col;
            posBis[*sizeofpos].y = currentRow;
            (*sizeofpos)++;
            lastDirection = 1;
            pastDirection=1;
        } else if (direction == 2 && currentRow < size - 3 && pastDirection!=1 && lastDirection != 1) {
            currentRow++;
            grid[currentRow][col] = 1;
            posBis[*sizeofpos].x = col;
            posBis[*sizeofpos].y = currentRow;
            (*sizeofpos)++;
            lastDirection = 2;
            pastDirection=2;
        } else {
        		if(lastDirection == 0){
        		pastDirection=0;
        		}
            col++;
            lastDirection = 0;
            grid[currentRow][col] = 1;
            posBis[*sizeofpos].x = col;
            posBis[*sizeofpos].y = currentRow;
            (*sizeofpos)++;
            lastDirection = 0;
                if (col == size-1) {
                    grid[currentRow][col] = -1;
                    posBis[*sizeofpos].x = col;
                    posBis[*sizeofpos].y = currentRow;
                    (*sizeofpos)++;
                    col = 0;
            }
        }
    }
    // Generate the path and put it in **grid
    
    
    // Memory allocation for end positions
    *pos = malloc(sizeof(Position) * (*sizeofpos));
    if (*pos == NULL) {
        printf("Memory allocation error for positions.\n");
        exit(4);
        }
        
    // Copy posBis positions to *pos
    for (int i = 0; i < *sizeofpos; i++) {
        (*pos)[i].x = posBis[i].x;  
        (*pos)[i].y = posBis[i].y;  
    }

    free(posBis);  // Free memory allocated for posBis
    
    return grid;
}


void showPath(int** grid, int size) {int back;
    srand(time(NULL));
printf("O  ");
for (int i = 1; i < size+1; i++){
    printf("%2d  ",i);
}

//Show the path with the emojis
for (int i = 0; i < size; i++) {
    printf("\n%2d ",i+1);
    for (int j = 0; j < size; j++) {
        if(j == 0 && grid[i][0] == 100){
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


void verifyWinCrab(Attacker** crab, int size_c, int sizeMap, int** map, int* PV) {
    for(int i = 0; i < size_c; i++) {
        if(crab[i] != NULL && crab[i]->pos.x == sizeMap-1) {
            *PV -= 1;
            printf("The King Monkey has lost 1 HP! and have %d PV\n", *PV);
            if( *PV <= 0) {
                printf("Game Over! The King Monkey has been defeated!\n");
                system("make");
                exit(5);
            }
            map[crab[i]->pos.y][crab[i]->pos.x] = -1; // Mark the end
            crab[i] = NULL; // Set pointer to NULL
            for (int j = i; j < size_c - 1; j++) {
                crab[j] = crab[j + 1]; // Shift the array to remove the crab
            }
        }
    }
}


void verifyWinDefender(Attacker** crab, int size_c) {
    if (size_c <= 0) return;

    for (int i = 0; i < size_c; i++) {
        if (crab[i] != NULL) {
            return;  // At least one crab is still alive
        }
    }

    printf("Victory! All crabs have been defeated!\n");
    system("make");
    exit(12);  // End of the game
}


void save_in_file(int*** t,int* size,int* size_c,int* size_m,int* banana, Attacker*** crab, Defender*** monkey,int* size_pos,int* king_hp,char* output_file) {
	FILE* file = fopen(output_file, "w");
	if (file == NULL) {
		perror("File opening error");
		return;
	}

	fwrite(size, sizeof(int), 1, file);

	for (int i = 0; i < *size; i++) {
		fwrite(&(*size), sizeof(int), 1, file);
		for (int j = 0; j < *size; j++) {
		    fwrite(&(*t)[i][j], sizeof(int), 1, file);
		}
	}

    // Write the additional integers
	fwrite(size_c, sizeof(int), 1, file);
	fwrite(size_m, sizeof(int), 1, file);
	fwrite(banana, sizeof(int), 1, file);

	fwrite(size_pos, sizeof(int), 1, file);
	
	fwrite(king_hp, sizeof(int), 1, file);

	for (int i = 0; i < *size_c; i++) { // Loop through crab array
		fwrite(&(*crab)[i]->pos.x, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->pos.y, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->dmg, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->hp, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->level, sizeof(int), 1, file);
	}

	for (int i = 0; i < *size_m; i++) { // Loop through monkey array
		fwrite(&(*monkey)[i]->pos.x, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->pos.y, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->dmg, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->range, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->level, sizeof(int), 1, file);
	}

	fclose(file);
}


void load_from_file( int*** t,  int* size, int* size_c, int* size_m, int* banana, Attacker*** crab, Defender*** monkey, int* size_pos,int* king_hp,char* input_file) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read 'size' of t
    fread(size, sizeof(int), 1, file);

    // Allocate memory for t (array of pointers to arrays of integers)
    *t = (int**)malloc(*size * sizeof(int*));
    for (int i = 0; i < *size; i++) {
        (*t)[i] = (int*)malloc(*size * sizeof(int));
    }

    // Read data from t (array of pointers to integer arrays)
    for (int i = 0; i < *size; i++) {
        int sub_size;
        fread(&sub_size, sizeof(int), 1, file);  // Sub-array size
        if (sub_size != *size) {
            perror("Incohérence dans la taille des sous-tableaux");
            return;
        }
        for (int j = 0; j < *size; j++) {
            fread(&(*t)[i][j], sizeof(int), 1, file);
        }
    }

    // Read the additional integers
    fread(size_c, sizeof(int), 1, file);
    fread(size_m, sizeof(int), 1, file);
    fread(banana, sizeof(int), 1, file);

    // Read the crab (Attacker) and monkey (Defender) tables
    fread(size_pos, sizeof(int), 1, file);

    fread(king_hp, sizeof(int), 1, file);

    *crab = (Attacker**)malloc(*size_c * sizeof(Attacker*));
    for (int i = 0; i < *size_c; i++) {
        (*crab)[i] = (Attacker*)malloc(sizeof(Attacker));
        fread(&(*crab)[i]->pos.x, sizeof(int), 1, file);
        fread(&(*crab)[i]->pos.y, sizeof(int), 1, file);
        fread(&(*crab)[i]->dmg, sizeof(int), 1, file);
        fread(&(*crab)[i]->hp, sizeof(int), 1, file);
        fread(&(*crab)[i]->level, sizeof(int), 1, file);
    }

    *monkey = (Defender**)malloc(*size_m * sizeof(Defender*));
    for (int i = 0; i < *size_m; i++) {
        (*monkey)[i] = (Defender*)malloc(sizeof(Defender));
        fread(&(*monkey)[i]->pos.x, sizeof(int), 1, file);
        fread(&(*monkey)[i]->pos.y, sizeof(int), 1, file);
        fread(&(*monkey)[i]->dmg, sizeof(int), 1, file);
        fread(&(*monkey)[i]->range, sizeof(int), 1, file);
        fread(&(*monkey)[i]->level, sizeof(int), 1, file);
    }

    fclose(file);
}


void game(int** t, int size, int* size_c, int* size_m, int banana, Attacker** crab, Defender** monkey, int size_pos, Position** p, int King_Monkey_Pv) {
    // Game logic goes here
    int i = -1;
    printf("King Flower HP: %d\n", King_Monkey_Pv);
        while(1){
            i++;
            int choice = choose(); // Call the choose function
            if (choice == 1) {
                char* output_file = "test_output.txt";
             	save_in_file(&t, &size, size_c, size_m, &banana, &crab, &monkey, &size_pos, &King_Monkey_Pv, output_file);
             	system("make");
                break; // Returns the player to the start menu
            }
            
            if( i%3 == 0){ 
                crab[*size_c] = create_attacker(size_pos);
                posInitCrabs(t, size, crab[*size_c]);
                (*size_c)++;
                i = 0; // Reset i to 0 after adding a crab
            }
            
            showPath(t, size);
            
            
            tree(&banana,size_m,t,size,monkey);
            
            
            
            for(int j = 0; j <= *size_c; j++){
                if (crab[j] != NULL) {
                    mooveCrabs(t, size, crab[j],*p, size_pos);
                    verifyWinCrab(crab,j, size, t,&King_Monkey_Pv);
                }
                
            }
            
            if (*size_c > 0) {  // Simplified condition
               money(crab, monkey, size_c, size_m, &banana, t);
            }
            
            
            verifyWinDefender(crab,*size_c);
            
            

    }
}