#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>
#include<time.h>
#include <windows.h> // For Windows console color

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
    new_defender->dmg = 3;

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
    new_attacker->hp = 6;
    new_attacker->level = 1;
    return new_attacker;
}

void posMonkey(int** map, int size) {
    int x,y;
    printf("Enter the position of the monkey (x): ");
    scanf("%d", &x);
    x-=1;
    if (x <= 0 || x >= size) {
        printf("Position must be between 0 and %d.\n", size-1);
        return;
    }
    printf("Enter the position of the monkey (y): ");
    scanf("%d",&y);
    y-=1;
    if (y <= 0 || y >= size) {
        printf("Position must be between 0 and %d.\n", size-1);
        exit(1);
    }
    if (map[y][x] == 1 || map[y][x] == 2) {
        printf("Position must be empty.\n");
        exit(1);
    }
    if (map[y-1][x] == 1 || map[y+1][x] == 1 || map[y][x-1] == 1 || map[y][x+1] == 1) {
        map[y][x] = 2; // 2 represents the monkey
        printf("Monkey placed at (%d, %d)\n", x, y);
    }
    else {
        printf("Monkey cannot be placed here.\n");
        exit(1);
    }
}

void posInitCrabs(int** map, int size, Attacker* crab) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(map[i][j] == 101){
                map[i][j] = 10;
                crab->pos.x = j;
                crab->pos.y = i;
                printf("Crab placed at (%d, %d)\n", crab->pos.x, crab->pos.y);
                // Check if crab is placed on the path
            }
        }
    }
}

void mooveCrabs(int** map, int size, Attacker* crab) {
    if(crab->pos.x+1 == 1 && crab->pos.y+1 == 0 && crab->pos.y-1 == 0){
        map[crab->pos.y][crab->pos.x] = 1;
        crab->pos.x += 1;
        map[crab->pos.y][crab->pos.x] = 10;
    }else if(crab->pos.x+1 == 0 && crab->pos.y+1 == 1 && crab->pos.y-1 == 0){
        map[crab->pos.y][crab->pos.x] = 1;
        crab->pos.y += 1;
        map[crab->pos.y][crab->pos.x] = 10;
    }else if(crab->pos.y+1 == 0 && crab->pos.x+1 == 0 && crab->pos.x-1 == 1){
        map[crab->pos.y][crab->pos.x] = 1;
        crab->pos.y -= 1;
        map[crab->pos.y][crab->pos.x] = 10;
    }
}



int** generatePath(int* nbsp) {
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

    *nbsp = size; // Allocation de la mémoire pour la grille

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

    SetConsoleOutputCP(65001);
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

int main()
{
    srand(time(NULL));  // Initialize random seed
    int size;

    int** t = generatePath(&size);
    if (t == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    Attacker** crab = malloc(sizeof(Attacker*) * size);
        if (crab == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

    for( int i = 0; i < 3; i++){
        
        showPath(t, size);
        posMonkey(t, size);
        crab[i] = create_attacker();
        for(int j = 0; j < i; j++){
            mooveCrabs(t, size, crab[j]);
        }
        posInitCrabs(t, size, crab[i]);
        mooveCrabs(t, size, crab[i]);
        //system("cls"); for clearing the console
    }


    for (int i = 0; i < size; i++) {
        free(t[i]);
    }
    free(t);
    return 0;
}
