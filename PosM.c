#include <stdio.h>
#include <stdbool.h>
#include "Position.h"

// Vérifie si une position est adjacente au chemin
bool estAdjacentAuChemin(int x, int y, char carte[][TAILLE_CARTE]) {
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    for (int i = 0; i < 4; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        
        if (newX >= 0 && newX < TAILLE_CARTE && 
            newY >= 0 && newY < TAILLE_CARTE && 
            carte[newY][newX] == 'C') {
            return true;
        }
    }
    return false;
}

// Affiche les positions valides pour placer un singe
void afficherPositionsValides(char carte[][TAILLE_CARTE]) {
    printf("Positions valides pour placer un singe :\n");
    for(int y = 0; y < TAILLE_CARTE; y++) {
        for(int x = 0; x < TAILLE_CARTE; x++) {
            if(carte[y][x] == ' ' && estAdjacentAuChemin(x, y, carte)) {
                printf("(%d,%d) ", x, y);
            }
        }
    }
    printf("\n");
}

// Demande et valide la position d'un nouveau singe
Position demanderPosition(char carte[][TAILLE_CARTE]) {
    Position pos;
    bool positionValide = false;
    
    afficherPositionsValides(carte);
    
    while (!positionValide) {
        printf("Entrez la position du singe (x y): ");
        if(scanf("%d %d", &pos.x, &pos.y) != 2) {
            while(getchar() != '\n'); // Clear input buffer
            printf("Format invalide! Utilisez deux nombres.\n");
            continue;
        }
        
        if (pos.x >= 0 && pos.x < TAILLE_CARTE && 
            pos.y >= 0 && pos.y < TAILLE_CARTE && 
            carte[pos.y][pos.x] == ' ' && 
            estAdjacentAuChemin(pos.x, pos.y, carte)) {
            positionValide = true;
        } else {
            printf("Position invalide! Le singe doit être placé sur une case vide adjacente au chemin.\n");
        }
    }
    
    return pos;
}