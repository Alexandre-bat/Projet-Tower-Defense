#include "Biblio.h"

int** generatePath(int* nbsp, Position** pos, int* sizeofpos) {
    int size;
    printf("What is the size of the map (15 - 50)? : ");
    scanf("%d", &size);
    if (size < 15 || size > 50) {
        printf("Size must be between 15 and 50.\n");
        printf("Error\n");
        exit(1);
    }
    
    if (size <= 0) {
        printf("Size must be positive.\n");
        printf("Error\n");
        exit(1);
    }

    *nbsp = size; // Allocation de la mémoire pour la grille

    int** grid = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        grid[i] = malloc(size * sizeof(int));
    }
    if (grid == NULL) {
        printf("Erreur memory allocation.\n");
        printf("Error\n");
        exit(1);
    }

    int currentRow = rand() % size; // Choisir une ligne aléatoire pour commencer
    if (currentRow == 0) {
        currentRow = 1; // Assurez-vous que la ligne est au moins 1
    }

    int lastDirection = 0; // 0: tout droit, 1: haut, 2: bas

    // Initialisation de la grille avec des espaces vides
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;  // Espaces vides
        }
    }

    Position* posBis = malloc(sizeof(Position) * 2 * size); // Allocation temporaire pour les positions
    *sizeofpos = 0;  // Initialiser le compteur de positions

    // Génération du chemin de gauche à droite (au lieu de droite à gauche pour plus de clarté)
    for (int col = 0; col < size; col++) {
        grid[currentRow][col] = 1; // Marquer le chemin
        posBis[*sizeofpos].x = col;  // Sauvegarder la position
        posBis[*sizeofpos].y = currentRow;
        (*sizeofpos)++;

        // Si ce n'est pas la dernière colonne, on peut essayer de faire un virage
        if (col > 0 && col < size - 1) {
            int direction = rand() % 4; // Choisir une direction aléatoire

            if (direction == 0 && lastDirection != 1 && lastDirection != 2) {
                int upOrDown = rand() % 2; // 0: haut, 1: bas
                if (upOrDown == 0 && currentRow > 0) { // Aller vers le haut
                    currentRow--;
                    grid[currentRow][col] = 1; // Marquer la case du dessus
                    posBis[*sizeofpos].x = col;
                    posBis[*sizeofpos].y = currentRow;
                    (*sizeofpos)++;
                    lastDirection = 1;
                } else if (upOrDown == 1 && currentRow < size - 1) { // Aller vers le bas
                    currentRow++;
                    grid[currentRow][col] = 1; // Marquer la case du dessous
                    posBis[*sizeofpos].x = col;
                    posBis[*sizeofpos].y = currentRow;
                    (*sizeofpos)++;
                    lastDirection = 2;
                } else {
                    lastDirection = 0;
                }
            } else {
                lastDirection = 0;
            }
        }
    }

    // Allocation de la mémoire pour les positions finales
    *pos = malloc(sizeof(Position) * (*sizeofpos));
    if (*pos == NULL) {
        printf("Memory allocation error for positions.\n");
        exit(1);
    }

    // Copier les positions de posBis dans *pos
    for (int i = 0; i < *sizeofpos; i++) {
        (*pos)[i].x = posBis[i].x;  // Copier la position x
        (*pos)[i].y = posBis[i].y;  // Copier la position y
    }
    // Afficher les positions générées
    printf("\n");

    free(posBis);  // Libérer la mémoire allouée pour posBis
    return grid;
}

void showPath(int** grid, int size) {int back;
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
        }else if(j == size-1 && grid[i][size-1] == 1){
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
                exit(1);
            }
            map[crab[i]->pos.y][crab[i]->pos.x] = 1; // Mark the end
            crab[i] = NULL; // Set pointer to NULL
            for (int j = i; j < size_c - 1; j++) {
                crab[j] = crab[j + 1]; // Shift the array to remove the crab
            }
        }
    }
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

	fwrite(size_c, sizeof(int), 1, file);
	fwrite(size_m, sizeof(int), 1, file);
	fwrite(banana, sizeof(int), 1, file);

	fwrite(size_pos, sizeof(int), 1, file);
	
	fwrite(king_hp, sizeof(int), 1, file);

	for (int i = 0; i < *size_c; i++) {
		fwrite(&(*crab)[i]->pos.x, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->pos.y, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->dmg, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->hp, sizeof(int), 1, file);
		fwrite(&(*crab)[i]->level, sizeof(int), 1, file);
	}

	for (int i = 0; i < *size_m; i++) {
		fwrite(&(*monkey)[i]->pos.x, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->pos.y, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->dmg, sizeof(int), 1, file);
		fwrite(&(*monkey)[i]->mana, sizeof(int), 1, file);
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
        fread(&(*monkey)[i]->mana, sizeof(int), 1, file);
        fread(&(*monkey)[i]->level, sizeof(int), 1, file);
    }

    fclose(file);
}

void game(int** t, int size, int* size_c, int* size_m, int banana, Attacker** crab, Defender** monkey, int size_pos, Position** p, int King_Monkey_Pv) {
    // Game logic goes here
    int i = -1;
    printf("King Flower HP: %d\n", King_Monkey_Pv);
        while(1){  // Limit to 100 iterations for safety
            i++;
            int choice = choose(); // Call the choose function
            if (choice == 2) {
                char* output_file = "test_output.txt";
             	save_in_file(&t, &size, size_c, size_m, &banana, &crab, &monkey, &size_pos, &King_Monkey_Pv, output_file);
             	system("make");
                break; // Exit the game loop if the user chooses to save
            }
            if( i%3 == 0){ 
                crab[*size_c] = create_attacker(size_pos);
                posInitCrabs(t, size, crab[*size_c]);
                (*size_c)++;
                i = 0; // Reset i to 0 after adding a crab
            }

            showPath(t, size);
            if (*size_c > 0) {  // Simplified condition

               money(crab, monkey, size_c, size_m, &banana, t);
              
            }

            tree(&banana, size_m, t, size, monkey);
            for(int j = 0; j < *size_c; j++){
                if (crab[j] != NULL) {
                    mooveCrabs(t, size, crab[j],*p, size_pos);
                    verifyWinCrab(crab,j, size, t,&King_Monkey_Pv);
                }
            }

    }
}
