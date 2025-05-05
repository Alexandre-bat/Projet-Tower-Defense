#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
//#include <windows.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
  } Position;
  
typedef struct{
    Position pos;
    int dmg;
    int mana;
    int level;
  }Defender;
  
typedef struct{
    Position pos;
    int dmg;
    int hp;
    int level;
  }Attacker;

// Function to create a new defender
//Define icones for the defender 
Defender* create_defender() {

    Defender* new_defender = (Defender*)malloc(sizeof(Defender));

    if (new_defender == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    new_defender->mana = 0;
    new_defender->level = 1;
    new_defender->dmg = 1;

  return new_defender;
}

// Function to create a new attacker
//Define icones for the attacker
Attacker* create_attacker(){

    Attacker* new_attacker = (Attacker*)malloc(sizeof(Attacker));

    if (new_attacker == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    new_attacker->dmg = 1;
    new_attacker->hp = 3;
    new_attacker->level = 1;
    return new_attacker;
}

Defender* posMonkey(int** map, int size) {
    Defender* monkey = create_defender();
    if (monkey == NULL) return NULL;
    int x, y;

    while (1) {
        printf("Enter the position of the monkey (x): ");
        scanf("%d", &x); x -= 1;
        if (x < 1 || x > size - 1) {
            printf("Position must be between 2 and %d.\n", size - 1);
            free(monkey);
            return NULL;
        }

        printf("Enter the position of the monkey (y): ");
        scanf("%d", &y); y -= 1;
        if (y < 0 || y > size - 1) {
            printf("Position must be between 1 and %d.\n", size);
            continue;
        }

        if (map[y][x] == 1 || map[y][x] == 2) {
            printf("Can't put a monkey here.\n");
            continue;
        }

        if ((y > 0 && map[y-1][x] == 1) || (y < size-1 && map[y+1][x] == 1) || 
            (x > 0 && map[y][x-1] == 1) || (x < size-1 && map[y][x+1] == 1)) {
            map[y][x] = 2;
            monkey->pos.x = x;
            monkey->pos.y = y;
            printf("Monkey placed at (%d, %d)\n", x+1, y+1);
            return monkey;
        }

        printf("Monkey cannot be placed here.\n");
    }
}

void posInitCrabs(int** map, Position* p, Attacker* crab) {
    crab->pos.x = p->x;
    crab->pos.y= p->y;
}


void mooveCrabs(int** map, Position* p, Attacker* crab, int i) {
    int x = crab->pos.x;
    int y = crab->pos.y;
    
    map[x][y] = 1;
    
    crab->pos.x = p[i+1].x ;
    crab->pos.y = p[i+1].y ;

    // If previous position was a starting point (101), restore it
    if (map[y][x] == 1 && x == 0) {
        map[y][x] = 101;
    }

    // Update crab position on map
    if (map[crab->pos.y][crab->pos.x] != 10) {
        map[crab->pos.y][crab->pos.x] = 10;
    }
}

void tree(int* banana, int* m, int** t, int size, Defender** monkey) {
    int none;
    if(*banana >= 2){
        printf("You have %d bananas\n", *banana);
        printf("Do you want to buy a monkey? (1 for yes, 0 for no): ");
        scanf("%d", &none);
        if(none == 1){
            monkey[*m] = posMonkey(t, size);
            *banana -= 2;
            (*m)++;
            }
    }
}

void money(Attacker** c, Defender** p, int* size_c, int* size_m, int* banana, int** map) {
    if (*size_c == 0 || *size_m == 0) return;
    for (int i = 0; i < *size_m; i++) {
        if (p[i] == NULL) continue;  // ⚠️ Sécurité anti-crash

        int e = p[i]->pos.x;
        int f = p[i]->pos.y;

        int j = 0;
        while (j < *size_c- 1) {
            if (c[j] == NULL) { j++; continue; }  // ⚠️ Sécurité anti-crash

            int o = c[j]->pos.x;
            int n = c[j]->pos.y;
            int dx = abs(e - o);
            int dy = abs(f - n);
            printf("x: %d, y: %d\n", dx, dy);
            if (dx <= 1 && dy <= 1) {
                c[j]->hp -= p[i]->dmg;
                printf("Crab %d is attacked by monkey %d; HP: %d\n", j, i, c[j]->hp);
                if (c[j]->hp <= 0) {
                    map[n][o] = 1;
                    (*banana)++;
                    free(c[j]);
                    c[j] = NULL; // Libération de la mémoire
                    for (int k = j; k < *size_c - 1; k++) {
                        c[k] = c[k + 1];
                    }
                    c[*size_c - 1] = NULL; // Optionnel : nettoyage
                    (*size_c)--;
                    continue;
                }
            }
            j++;
        }
    }
}
    



int** generatePath(int* nbsp, Position* p) {
    int size;
    printf("What is the size of the map ( 11 - 99)? : ");
    scanf("%d", &size);
    
    if (size < 11 || size > 99) {
        printf("Size must be between 11 and 99.\n");
        printf("Error\n");
        exit(1);
    }

    if (size <= 0) {
        printf("Size must be postive.\n");
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
    
    int currentRow = rand()%size; // Choisir une ligne aléatoire pour commencer
    if (currentRow == 0) {
        currentRow = 1; // Assurez-vous que la ligne est au moins 1
    }

    int lastDirection = 0; // 0: tout droit, 1: haut, 2: bas

    // Initialisation de la grille avec des espaces vides
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }
	int random = 0;
    // Génération du chemin de droite à gauche
    for (int col = size - 1; col >= 0; col--) {
        grid[currentRow][col] = 1; // Marque le chemin
        p[random].x = currentRow;
        p[random].y = col;
        random += 1;
        // Si nous ne sommes pas à la première colonne
        if (col > 0) {
            int direction = rand() % 4; // Reduce frequency of turns

            if (direction == 0 && lastDirection != 1 && lastDirection != 2) {
                int upOrDown = rand() % 2; // 0 (haut), 1 (bas)
                
                if (upOrDown == 0 && currentRow > 1) {
                    currentRow--;
                    grid[currentRow][col] = 1; // Remplit la case du dessus
                    lastDirection = 1;
                } else if (upOrDown == 1 && currentRow < size - 2) {
                    currentRow++;
                    grid[currentRow][col] = 1; // Remplit la case du dessous
                    lastDirection = 2;
                } else {
                    lastDirection = 0;
                }
            } else {
                lastDirection = 0;
            }
        }
    }

    //Position of start and end
    for( int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(grid[i][j] == 1 && j == size-1){
                grid[i][j] = 100;
            }
            if(grid[i][j] == 1 && j == 0){
                grid[i][j] = 101;
            }
        }
    }

    return grid;
}

void showPath(int** grid, int size) {

    printf("O  ");
    for (int i = 1; i < 10; i++){
        printf("%.2d  ",i);
    }
    for (int i = 10; i < size+1; i++){
        printf("%.2d  ",i);
    }

    for (int i = 0; i < size; i++) {
        printf("\n%.2d ",i+1);

        for (int j = 0; j < size; j++) {
            if (grid[i][j] == 1) {
                printf("\xF0\x9F\x94\xB4  ");
            }
            else if(grid[i][j] == 2){
                printf("\xF0\x9F\x99\x88  ");
            }
            else if( grid[i][j] == 10){
                printf("\xF0\x9F\x98\xBE  ");
            }else if(grid[i][j] == 101){
                printf("\xF0\x9F\x86\x96  ");
            }else if(grid[i][j] == 100){
                printf("\xF0\x9F\x92\xA3  ");
            }else {
                printf("\xF0\x9F\x94\xB2  ");
            }
        }
        printf("\n");
    }
}

void verifyWinCrab(Attacker** crab, int size_c, int sizeMap, int** map) {
    for(int i = 0; i < size_c; i++) {
        if(crab[i] != NULL && crab[i]->pos.x == sizeMap-1) {
            printf("Game Over - Crab reached the end!\n");
            map[crab[i]->pos.y][crab[i]->pos.x] = 100; // Mark the end
            crab[i] = NULL; // Set pointer to NULL
            for (int j = i; j < size_c - 1; j++) {
                crab[j] = crab[j + 1]; // Shift the array to remove the crab
            }
            showPath(map, sizeMap); // Show the map
            exit(1);
        }
    }
}
int main()
{
    srand(time(NULL));  // Initialize random seed
    int size;
    //SetConsoleOutputCP(65001);
    
    int banana = 4;
    int size_c = 0;  // Size of crab array
    int size_m = 0;      // Size of monkey array
	
	Position* path;


    int** t = generatePath(&size, path);
    if (t == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    const int MAX_UNITS = 1000;

    Attacker** crab = malloc(sizeof(Attacker*) * MAX_UNITS);
    if (!crab) { printf("Erreur allocation crab\n"); return 1; }

    Defender** monkey = malloc(sizeof(Defender*) * MAX_UNITS);
    if (!monkey) { printf("Erreur allocation monkey\n"); return 1; }


        for( int i = 0; i < MAX_UNITS && i < 100; i++){  // Limit to 100 iterations for safety

            if( i%3 == 0){ 
                crab[size_c] = create_attacker();
                posInitCrabs(t, path, crab[size_c]);
                size_c += 1;
            }

            showPath(t, size);
            if (size_c > 0) {  // Simplified condition
               money(crab, monkey, &size_c, &size_m, &banana, t);
            }
            printf("Problem ?\n");
            tree(&banana, &size_m, t, size, monkey);
            printf("Problem ?\n");
            //printf("Jusqu'ici tout va bien 1\n");
            for(int j = 0; j < size_c; j++){
                if (crab[j] != NULL) {
                    mooveCrabs(t, path, crab[j], crab[j]->pos.x);
                    verifyWinCrab(crab,j, size, t);
                }
            }
            

            if (i >= MAX_UNITS) {
                printf("Limite atteinte (%d crabs)\n", MAX_UNITS);
                break;
            }
        }


    // Free the crabs
    for (int i = 0; i < size_c; i++) {
        if (crab[i] != NULL) {
            free(crab[i]);
        }
    }
    free(crab);

    // Free the monkeys
    for (int i = 0; i < size_m; i++) {
        if (monkey[i] != NULL) {
            free(monkey[i]);
        }
    }
    free(monkey);

    // Free the map
    for (int i = 0; i < size; i++) {
        free(t[i]);
    }
    free(t);
    return 0;
}
