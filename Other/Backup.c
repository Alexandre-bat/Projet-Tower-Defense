#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>



typedef struct {
    int x;
    int y;
  } Position;
  
typedef struct{
    Position pos;
    int dmg;
    int range;
    int level;
  }Defender;
  
typedef struct{
    Position pos;
    int dmg;
    int hp;
    int level;
  }Attacker;

  void displayPositions(Position* positions, int size) {
    if (positions == NULL || size <= 0) return;
    
    for (int i = 0; i < size; i++) {
        printf("Position %d: (%d, %d)\n", i, positions[i].x, positions[i].y);
    }
}

void clear_input_buffer();
int King_HP();
int choose();
int menu();
int** generatePath(int* s, Position** pos, int* sizeofpos);
void showPath(int** grid, int size);
void verifyWinCrab(Attacker** crab, int size_c, int sizeMap, int** map, int* PV);
void verifyWinDefender(Attacker** crab, int size_c);
void save_in_file(int*** t,int* size,int* size_c,int* size_m,int* banana, Attacker*** crab, Defender*** monkey,int* size_pos,int* king_hp,char* output_file);
void load_from_file( int*** t,  int* size, int* size_c, int* size_m, int* banana, Attacker*** crab, Defender*** monkey, int* size_pos,int* king_hp,char* input_file);
void game(int** t, int size, int* size_c, int* size_m, int banana, Attacker** crab, Defender** monkey, int size_pos, Position** p, int King_Monkey_Pv);
Defender* create_defender();
Attacker* create_attacker();
Defender* posMonkey(int** map, int size);
void posInitCrabs(int** map, int size, Attacker* crab);
void mooveCrabs( int** map, int size, Attacker* crab, Position* p, int size_pos);
void tree(int* banana, int* m, int** t, int size, Defender** monkey);
void money(Attacker** c, Defender** p, int* size_c, int* size_m, int* banana, int** map);
void Let_s_the_show_beggin();



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
    int all_crabs_dead = 1;  // Assume all crabs are dead until we find one alive
    
    for(int i = 0; i < size_c; i++) {
        if(crab[i] != NULL) {
            all_crabs_dead = 0;  // Found a living crab
            break;
        }
    }
    
    if(all_crabs_dead && size_c > 0) {
        printf("Victory! All bee have been defeated!\n");
        exit(12);  // Exit the game with success
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
    const int MAX_UNITS = 1000;
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

        if(i%3 == 0){ 
            if (*size_c < MAX_UNITS - 1) {  // Check if there's room for more crabs
                crab[*size_c] = create_attacker();
                if (crab[*size_c] != NULL) {
                    posInitCrabs(t, size, crab[*size_c]);
                    (*size_c)++;
                    i = 0; // Reset i to 0 after adding a crab
                }
            }
        }

        showPath(t, size);
        
        tree(&banana,size_m,t,size,monkey);

        displayPositions(*p,size_pos);
        
        for(int j = 0; j < *size_c; j++){
            if (crab[j] != NULL) {
                mooveCrabs(t, size, crab[j],*p, size_pos);
                verifyWinCrab(crab,j, size, t,&King_Monkey_Pv);
            }
        }
        
        if (*size_c > 0) {
            money(crab, monkey, size_c, size_m, &banana, t);
        }
        
        verifyWinDefender(crab,*size_c);
    }
}


void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int King_HP() {
    char input[50];
    int hp;
    const int MIN_HP = 1;    // Minimum acceptable HP
    const int MAX_HP = 10;  // Maximum acceptable HP

    printf("How many HP should the king have? (%d-%d)\n", MIN_HP, MAX_HP);

    if (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &hp) == 1) {
            if (hp >= MIN_HP && hp <= MAX_HP) {
                return hp;
            } else {
                printf("HP must be between %d and %d. Please try again.\n", MIN_HP, MAX_HP);
                return King_HP();
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            return King_HP();
        }
    }

    printf("Error reading input.\n");
    exit(15);
}

int choose() {
    char input[50];
    int c;

    printf("Choose an option:\n");
    printf("    0. Continue\n");
    printf("    1. Save\n");
    printf("Enter your choice: ");

    if (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &c) == 1) {
            switch (c) {
                case 0:
                    return 0;
                case 1:
                    printf("Game saved.\n"); // À remplacer par l'appel à la vraie fonction de sauvegarde
                    return 1;
                default:
                    printf("Invalid choice. Please try again.\n");
                    return choose();
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            return choose();
        }
    }

    //Rare case: fgets fails (EOF or error)
    printf("fgets doesn't work");
    return 2;
}


int menu() {
    char input[50];  // buffer for read the line
    int choice;

    printf("Choose an option:\n");
    printf("    1. Start Game\n");
    printf("    2. Save\n");
    printf("    3. Exit\n");
    printf("Enter your choice: ");

    if (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &choice) == 1) {
            switch (choice) {
                case 1:
                    printf("Let the show begin!\n");
                    return 1;
                case 2:
                    printf("Game saved.\n");
                    return 2;
                case 3:
                    printf("Au revoir");
                    return 3;
                default:
                    printf("Invalid choice. Please try again.\n");
                    return menu();
            }
        } else {
            printf("Invalid input. Please enter a number.\n");
            return menu();
        }
    }

    //Rare case: fgets fails (EOF or error)
    printf("fgets doesn't work");
    return 3;
}

// Function to create a new defender
Defender* create_defender() {

    Defender* new_defender = (Defender*)malloc(sizeof(Defender));

    if (new_defender == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    new_defender->range = 1;
    new_defender->level = 1;
    new_defender->dmg = 1;

  return new_defender;
}

// Function to create a new attacker
Attacker* create_attacker(){

    Attacker* new_attacker = (Attacker*)malloc(sizeof(Attacker));

    if (new_attacker == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    new_attacker->dmg = 1;
    new_attacker->hp = 3;
    new_attacker->level = 0;
    return new_attacker;
}

Defender* posMonkey(int** map, int size) {
    Defender* monkey = create_defender();
    if (monkey == NULL) return NULL;
    int x, y;
    int valid = 0;

    while (!valid) {
        printf("Enter the position of the monkey (x): ");
        scanf("%d", &x); 
        x -= 1;
        if (x <= 0 || x > size - 1) {
            printf("Position must be between 2 and %d.\n", size);
            clear_input_buffer();
            continue;
        }
        
        clear_input_buffer();
        
        printf("Enter the position of the monkey (y): ");
        scanf("%d", &y); 
        y -= 1;
        if (y < 0 || y > size - 1) {
            printf("Position must be between 1 and %d.\n", size);
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        if (map[y][x] == 1 || map[y][x] == 2 || map[y][y] == -1) {
            printf("Can't put a monkey here.\n");
            continue;
        }
        
        if (x <= monkey->range) {
            printf("Cannot place monkey too close to crab spawn point.\n");
            continue;
        }

        if ((y > 0 && map[y-1][x] == 1) || (y < size-1 && map[y+1][x] == 1) || 
            (x > 0 && map[y][x-1] == 1) || (x < size-1 && map[y][x+1] == 1)) {
            map[y][x] = 2;
            monkey->pos.x = x;
            monkey->pos.y = y;
            printf("Monkey placed at (%d, %d)\n", x+1, y+1);
            valid = 1;
        } else {
            printf("Monkey must be placed next to the path.\n");
        }
    }
    return monkey;
}

void posInitCrabs(int** map, int size, Attacker* crab) {
    for (int i = 0; i < size; i++) {
        if (map[i][0] == 101 || map[i][0] == 1) {
        if(map[i][1] == 10){
            printf("Can't put a crab here.\n");
            return;
        }
            map[i][0] = 10;
            crab->pos.x = 0;
            crab->pos.y = i;
            crab->level++;
            return;
        }
    }
    printf("No valid starting point for crab. Releasing memory.\n");
    free(crab);
}


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

void money(Attacker** c, Defender** p, int* size_c, int* size_m, int* banana, int** map) {
    if (*size_c == 0 || *size_m == 0) return;
    for (int i = 0; i < *size_m; i++) {
        if (p[i] == NULL) continue;  // ⚠️ Sécurité anti-crash

        int e = p[i]->pos.x;
        int f = p[i]->pos.y;
        
        int r = p[i]->range;

        int j = 0;
        while (j < *size_c) {
            if (c[j] == NULL) { j++; continue; }  // ⚠️ Sécurité anti-crash

            int o = c[j]->pos.x;
            int n = c[j]->pos.y;
            int dx = abs(e - o);
            int dy = abs(f - n);
            if (dx <= r && dy <= r) {
                c[j]->hp -= p[i]->dmg;
                printf("Crab %d is attacked by monkey %d; HP: %d\n", j, i, c[j]->hp);
                if (c[j]->hp <= 0) {
                    map[n][o] = 1;
                    (*banana) += 2;
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

void tree(int* banana, int* m, int** t, int size, Defender** monkey) {
    int choice;
    if(*banana <= 0 && *m == 0) {
        printf("You have no bananas or no defender!\n");
    }
    printf("You have %d bananas\n", *banana);
    printf("What would you like to do?\n");
    printf("1. Buy new monkey (2 bananas)\n");
    printf("2. Upgrade existing monkey (3 bananas)\n");
    printf("0. Skip\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clear_input_buffer();
    switch(choice) {
        case 1:
            if((*banana) >= 2) {
                monkey[*m] = posMonkey(t, size);
                if(monkey[*m] != NULL) {
                    *banana -= 2;
                    (*m)++;
                }
            } else {
                printf("Not enough bananas!\n"); 
            }
            break;

        case 2:
            if(*banana >= 3 && *m > 0) {
                int monkey_id;
                printf("Which monkey do you want to upgrade? (1-%d): ", *m);
                scanf("%d", &monkey_id);
                monkey_id--; // Convert to 0-based index
                clear_input_buffer();
                if(monkey_id >= 0 && monkey_id < *m && monkey[monkey_id] != NULL) {
                    printf("What do you want to upgrade?\n");
                    printf("1. Range (current: %d)\n", monkey[monkey_id]->range);
                    printf("2. Damage (current: %d)\n", monkey[monkey_id]->dmg);
                    printf("Enter your choice: ");
                    int upgrade_choice;
                    scanf("%d",&upgrade_choice);
                    clear_input_buffer();
                    switch(upgrade_choice) {
                        case 1:
                            monkey[monkey_id]->range++;
                            *banana -= 3;
                            printf("Range increased to %d\n", monkey[monkey_id]->range);
                            break;
                        case 2:
                            monkey[monkey_id]->dmg++;
                            *banana -= 3;
                            break;
                        default:
                            printf("Invalid upgrade choice\n");
                    }
                } else {
                    printf("Invalid monkey ID\n");
                }
            } else {
                printf("Not enough bananas or no monkeys to upgrade!\n");
            }
            break;

        case 0:
            break;

        default:
            printf("Invalid choice\n");
            break;
    }
}



void Let_s_the_show_beggin(){
    srand(time(NULL));  // Initialize random seed

    int size = 0;
    int banana = 4;
    int size_c = 0;  // Size of crab array
    int size_m = 0;  // Size of monkey array
    Position* pos = NULL;
    int size_pos = 0; // Size of the position array
    int** t = NULL;
    int k_hp;
    Attacker** crab = NULL;
    Defender** monkey = NULL;

    int what_a_choise = menu();
    switch (what_a_choise) {
        case 1:        
            size_pos = 0; // Size of the position array
        
            t = generatePath(&size,&pos, &size_pos);
            if (t == NULL) { printf("Memory allocation failed\n"); exit(6);}
        
            const int MAX_UNITS = 1000;
        
            crab = malloc(sizeof(Attacker*) * MAX_UNITS);
            if (crab == NULL ) { printf("Erreur allocation crab\n"); exit(7); }
        
            monkey = malloc(sizeof(Defender*) * MAX_UNITS);
            if (monkey == NULL ) { printf("Erreur allocation monkey\n"); exit(8); }
        	
            k_hp = King_HP();
            game(t, size, &size_c, &size_m, banana, crab, monkey, size_pos, &pos, k_hp);

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
            break;
        case 2:
            // Call the save function here
            printf("Game saved.\n"); // To do
            char* output_file = "test_output.txt";
            FILE* test = fopen(output_file, "r");
            if (test == NULL || fgetc(test) == EOF) {
                printf("Save file is empty or doesn't exist. Starting new game...\n");
                fclose(test);
                exit(9);
            } else {
                fclose(test);
            }
            int banana;
            load_from_file(&t, &size, &size_c, &size_m, &banana, &crab, &monkey, &size_pos, &k_hp , output_file);
            game(t, size, &size_c, &size_m, banana, crab, monkey, size_pos, &pos, k_hp );
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
            break;
        case 3:
            exit(10);
        default:
            printf("Invalid choice. Please try again.\n");
            menu();
    }
}

int main() {
    Let_s_the_show_beggin();
    return 0;
}

