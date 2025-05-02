#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int** generatePath(int* s) {
    int size;
    printf("What is the size of the map (11 - 99)? : ");
    scanf("%d", &size);
    if (size < 11 || size > 99) {
        printf("Size must be between 11 and 99.\n");
        exit(1);
    }
    *s = size;
    srand(time(NULL));
    
    int** grid = malloc(size * sizeof(int*));
    if (grid == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        grid[i] = malloc(size * sizeof(int));
        if (grid[i] == NULL) {
            printf("Erreur d'allocation mémoire pour la ligne %d.\n", i);
            exit(1);
        }
    }

    int currentRow = rand() % (size/3) +size/3;  // S'assurer que currentRow est dans les bornes
    int lastDirection = 0;
    int pastDirection = 0; // 0: tout droit, 1: haut, 2: bas

    // Initialisation de la grille avec des espaces vides
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }
    
    int col = 1;
    int direction;
    grid[currentRow][0] = 1;
    
    while (col != 0) {
        direction = rand() % 3; // Réduire la fréquence des virages

        if (direction == 1 && currentRow > 3 && pastDirection!=2 && lastDirection != 2) {  // Vérification des bornes
            currentRow--;
            grid[currentRow][col] = 1;
            lastDirection = 1;
            pastDirection=1;
        } else if (direction == 2 && currentRow < size - 3 && pastDirection!=1 && lastDirection != 1) {
            currentRow++;
            grid[currentRow][col] = 1;
            lastDirection = 2;
            pastDirection=1;
        } else {
        		if(lastDirection == 0){
        		pastDirection=0;
        		}
            col++;
            lastDirection == 0;
            if (col == size) {
                col = 0;
            }
            grid[currentRow][col] = 1;
            lastDirection = 0;
        }
    }

    // Position du début et de la fin
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == 1 && j == size - 1) {
                grid[i][j] = 100;  // Fin du chemin
            }
            if (grid[i][j] == 1 && j == 0) {
                grid[i][j] = 101;  // Début du chemin
            }
        }
    }

    return grid;
}


