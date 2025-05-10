#include "all.h"

int** generatePath(int* nbsp, Position** pos, int* sizeofpos) {
    int size;
    printf("What is the size of the map (11 - 99)? : ");
    scanf("%d", &size);
    if (size < 11 || size > 99) {
        printf("Size must be between 11 and 99.\n");
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
    showOnlyPath(posBis, *sizeofpos);
    printf("\n");

    free(posBis);  // Libérer la mémoire allouée pour posBis
    return grid;
}

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