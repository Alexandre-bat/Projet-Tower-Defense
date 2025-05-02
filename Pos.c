#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <windows.h>
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
    new_attacker->hp = 1;
    new_attacker->level = 1;
    return new_attacker;
}

Defender* posMonkey(int** map, int size) {
    Defender* monkey = create_defender();
	int x, y;
	printf("Enter the position of the monkey (x): ");
	scanf("%d", &x);
	x-=1;
	if (x < 1 || x > size-1) {
		printf("Position must be between 2 and %d.\n", size-1);
		posMonkey(map, size);
		exit(1);
	}
	printf("Enter the position of the monkey (y): ");
	scanf("%d",&y);
	y-=1;
	if (y < 0 || y > size) {
		printf("Position must be between 1 and %d.\n", size);
		posMonkey(map, size);
		exit(1);
	}
	if (map[y][x] == 1 || map[y][x] == 2) {
		printf("Can't put a monkey here\n");
		posMonkey(map, size);
		exit(1);
	}

	// check if y-1 or y+1 are out of the memory allocation
	if (y-1 < 0) {
		if (map[y+1][x] == 1 || map[y][x-1] == 1 || map[y][x+1] == 1) {
			map[y][x] = 2; // 2 represents the monkey
			printf("Monkey placed at (%d, %d)\n", x, y);
		}
	else if (y+1 > size-1) {
		if (map[y-1][x] == 1 || map[y][x-1] == 1 || map[y][x+1] == 1) {
			map[y][x] = 2; // 2 represents the monkey
			printf("Monkey placed at (%d, %d)\n", x, y);
		}
	}
	} else {

		if (map[y-1][x] == 1 || map[y+1][x] == 1 || map[y][x-1] == 1 || map[y][x+1] == 1) {
			map[y][x] = 2; // 2 represents the monkey
			printf("Monkey placed at (%d, %d)\n", x, y);
		} else {
			printf("Monkey cannot be placed here.\n");
			posMonkey(map, size);
			exit(1);
		}
	}
    monkey->pos.x = x;
    monkey->pos.y = y;
    return monkey;
}

void posInitCrabs(int** map, int size, Attacker* crab) {
    for (int i = 0; i < size; i++) {
        if (map[i][0] == 101 || map[i][0] == 1 ) {  // Check for starting point (101)
            map[i][0] = 10;      // Place the crab (10)
            crab->pos.x = 0;
            crab->pos.y = i;
            printf("Crab placed at (%d, %d)\n", crab->pos.x, crab->pos.y);
            return;
        } else if (map[i][0] == 10) {  // If position already has a crab
            continue;
        }
    }
    printf("No valid starting point for crab.\n");
}

void mooveCrabs(int** map, int size, Attacker* crab) {
    int x = crab->pos.x;
    int y = crab->pos.y;
    // Initialize ANSI color sequence (can be used if your terminal supports it)
    printf("\033[0m"); // Reset color
    // Check right
    if (x + 1 < size && map[y][x + 1] == 1) {
        map[y][x] = 1;
        crab->pos.x += 1;
    }
    // Check down
    else if (y + 1 < size && map[y + 1][x] == 1) {
        map[y][x] = 1;
        crab->pos.y += 1;
    }
    // Check up
    else if (y - 1 >= 0 && map[y - 1][x] == 1) {
        map[y][x] = 1;
        crab->pos.y -= 1;
    }
    // Check left (if somehow needed)
    else if (x - 1 >= 0 && map[y][x - 1] == 1) {
        map[y][x] = 1;
        crab->pos.x -= 1;
    }

    // If previous position was a starting point (101), restore it
    if (map[y][x] == 1 && x == 0) {
        map[y][x] = 101;
    }
    // Update crab position on map
    if (map[crab->pos.y][crab->pos.x] != 10) {
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

void money(Attacker** c, Defender** p, int* size_c, int* size_m, int* banana, int** map) {
    printf("Crabs size: %d\n", *size_c);
    int e, f;
    int o, n;

    for (int i = 0; i < *size_m; i++) {
        e = p[i]->pos.x;
        f = p[i]->pos.y;

        for (int j = 0; j < *size_c; ) {
            o = c[j]->pos.x;
            n = c[j]->pos.y;
            int dx = abs(e - o); // Calculate the distance in x direction
            int dy = abs(f - n); // Calculate the distance in y direction
            // A REVOIR
            printf("Monkey %d is at (%d, %d) and crab %d is at (%d, %d)\n", i, e, f, j, o, n);

            if (dx <= 1 && dy <= 1) {
                c[j]->hp -= p[i]->dmg;
                printf("Crab %d is attacked by monkey; HP: %d\n", j, c[j]->hp);

                if (c[j]->hp <= 0) {
                    map[n][o] = 1;
                    (*banana)++;
                    // free(c[j]); // Uncomment if memory was allocated for each crab
                    for (int k = j; k < *size_c - 1; k++) {
                        c[k] = c[k + 1];
                    }
                    (*size_c)--;
                    continue; // re-check new c[j]
                }
            }
            j++;
        }
    }
}

void tree(int* banana, int* m, int** t, int size, Defender** monkey, int i) {
    if(*banana >= 2){
        int size_m;
        printf("You have %d bananas\n", *banana);
        printf("Do you want to buy a monkey? (1 for yes, 0 for no): ");
        scanf("%d", &size_m);
        if(size_m == 1){
            monkey[i] = posMonkey(t, size);
            *banana -= 2;
            (*m)++;
            }
    }
}


int main()
{
    srand(time(NULL));  // Initialize random seed
    int size;
    SetConsoleOutputCP(65001);
    
    int banana = 4;
    int size_c = 0;  // Size of crab array
    int size_m = 0;      // Size of monkey array

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
        
    Defender** monkey = malloc(sizeof(Defender*) * size);
        if (monkey == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

    for( int i = 0; i < 10; i++){
        size_c = i + 1;  // Size of crab array
        size_m = i;      // Size of monkey array
        showPath(t, size);
        tree(&banana, &size_m, t, size, monkey, i);
        crab[i] = create_attacker();
        
        for(int j = 0; j < i; j++){
            	mooveCrabs(t, size, crab[j]);
        }
        
        posInitCrabs(t, size, crab[i]);
        mooveCrabs(t, size, crab[i]);

        money(crab,monkey,&size_c, &size_m,&banana, t);
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