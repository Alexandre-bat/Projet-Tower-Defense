#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position pos;
    int level;
} Attacker;

void mooveCrabs( int** map, int size, Attacker* crab, Position* p, int size_pos) {
    if (crab == NULL){return;}  // Vérifier si le crabe est valide
    if(p == NULL){return;}  // Vérifier si le tableau de positions est valide
    if(size_pos <= 0){return;}  // Vérifier si la taille du tableau de positions est valide
    int l = crab->level;

    // Vérifier la position actuelle du crabe (assurer qu'il n'est pas hors limite)
    if (map[crab->pos.y][crab->pos.x] == 10) {
        // Si la position est valide, effectue un changement
        map[crab->pos.y][crab->pos.x] = 1;  // Retirer le crabe de sa position actuelle
    }
    

    // Vérifie si la position suivante est dans les limites
    if (l < size_pos && p[l].x >= 0 && p[l].y >= 0 && p[l].x < size && p[l].y < size) {
        printf("Crab moving to x: %d, y: %d\n", p[l].x, p[l].y);
        crab->pos.x = p[l].x;  // Mettre à jour la position du crabe
        crab->pos.y = p[l].y;
        crab->level++;  // Incrémenter le niveau du crabe

        // Si le crabe atteint la fin du niveau (conditions de victoire)
        if (crab->pos.x == size -1 && map[crab->pos.y][crab->pos.x + 1] == 100) {
            map[crab->pos.y][crab->pos.x] = 0;  // Retirer le crabe du map
            free(crab);  // Libérer la mémoire du crabe
            crab = NULL;  // Définir le pointeur comme NULL
            return;  // Sortir de la fonction
        }

        // Restauration de l'ancienne position si elle était un point de départ (101)
        if (map[crab->pos.y][crab->pos.x] == 0 && crab->pos.x == 0) {
            map[crab->pos.y][crab->pos.x] = 101;  // Restaurer le point de départ
        }

        // Mettre à jour la nouvelle position du crabe sur la carte
        if (map[crab->pos.y][crab->pos.x] != 10) {
            map[crab->pos.y][crab->pos.x] = 10;  // Marquer la position actuelle avec "10" pour le crabe
        }
        
    } else {
        printf("Moving conditions: level %d < size %d, pos(%d,%d) within [0,%d]\n", 
               l, size, p[l].x, p[l].y, size-1);
        printf("Invalid move for crab at level %d.\n", l);
    }
}