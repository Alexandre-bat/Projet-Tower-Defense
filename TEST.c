#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generatePath() {
    int size;

    printf("What is the size of the map ( 11 - 99)? : ");
    scanf("%d", &size);
    if (size < 11 || size > 99) {
        printf("Size must be between 11 and 99.\n");
        exit(1);
    }

    if (size <= 0) {
        printf("Size must be postive.\n");
        exit(1);
    }

    int** grid = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        grid[i] = malloc(size * sizeof(int));
    }
    if (grid == NULL) {
        printf("Erreur memory allocation.\n");
        exit(1);
    }
    int currentRow = size / 2; // Commence au milieu de la grille
    int lastDirection = 0; // 0: tout droit, 1: haut, 2: bas

    // Initialisation de la grille avec des espaces vides
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }

    // Génération du chemin de droite à gauche
    for (int col = size - 1; col >= 0; col--) {
        grid[currentRow][col] = 1; // Marque le chemin

        // Si nous ne sommes pas à la première colonne
        if (col > 0) {
            int direction = rand() % 2; // 0 (tout droit), 1 (haut ou bas)

            if (direction == 1) {
                int upOrDown = rand() % 2; // 0 (haut), 1 (bas)
                
                // Empêche de tourner dans la même direction deux fois d'affilée
                if (lastDirection == 1) { // Si on est allé en haut dernièrement
                    grid[currentRow][col] = 1;
                    continue;
                } else if (lastDirection == 2) { // Si on est allé en bas dernièrement
                    grid[currentRow][col] = 1;
                    continue;
                }

                if (upOrDown == 0 && currentRow > 1) {
                    grid[currentRow-1][col] = 1; // Remplit la case du dessus
                    currentRow--;
                    lastDirection = 1;
                } else if (upOrDown == 1 && currentRow < size - 2) {
                    grid[currentRow+1][col] = 1; // Remplit la case du dessous
                    currentRow++;
                    lastDirection = 2;
                } else {
                    lastDirection = 0;
                }
            } else {
                lastDirection = 0;
            }
        }
    }

    // Affichage de la grille
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == 1) {
                printf("0");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

}

int main() {
    srand(time(NULL)); // Initialisation de la graine pour les nombres aléatoires
    generatePath();

    // Libération de la mémoire
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}