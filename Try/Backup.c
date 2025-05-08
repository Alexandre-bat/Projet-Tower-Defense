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
    new_attacker->level = 0;
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
    if (crab == NULL) return;  // Vérifier si le crabe est valide
    if(p == NULL) return;  // Vérifier si le tableau de positions est valide
    if(size_pos <= 0) return;  // Vérifier si la taille du tableau de positions est valide
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

int choose(){
    int choice;
    printf("Choose an option:\n");
    printf("    1. Continue\n");
    printf("    2. Save\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            return 1; // Continue the game
        case 2:
            // Call the save function here
            printf("Game saved.\n"); // To do
            return 2; // Save the game
        default:
            printf("Invalid choice. Please try again.\n");
            choose();
    }
}


void save_in_file(int*** t,int* size,int* size_c,int* size_m,int* banana,Attacker*** crab,Defender*** monkey,int* size_pos,char* output_file) {
	FILE* file = fopen(output_file, "w");
	if (file == NULL) {
		perror("Erreur ouverture fichier");
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


void load_from_file(int*** t, int* size, int* size_c, int* size_m, int* banana, Attacker*** crab, Defender*** monkey, int* size_pos, char* input_file) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Lire 'size' de t
    fread(size, sizeof(int), 1, file);

    // Allouer de la mémoire pour t (tableau de pointeurs vers des tableaux d'entiers)
    *t = (int**)malloc(*size * sizeof(int*));
    for (int i = 0; i < *size; i++) {
        (*t)[i] = (int*)malloc(*size * sizeof(int));
    }

    // Lire les données de t (tableau de pointeurs vers des tableaux d'entiers)
    for (int i = 0; i < *size; i++) {
        int sub_size;
        fread(&sub_size, sizeof(int), 1, file);  // Taille du sous-tableau
        if (sub_size != *size) {
            perror("Incohérence dans la taille des sous-tableaux");
            return;
        }
        for (int j = 0; j < *size; j++) {
            fread(&(*t)[i][j], sizeof(int), 1, file);
        }
    }

    // Lire les entiers supplémentaires
    fread(size_c, sizeof(int), 1, file);
    fread(size_m, sizeof(int), 1, file);
    fread(banana, sizeof(int), 1, file);

    // Lire les tableaux crab (Attacker) et monkey (Defender)
    fread(size_pos, sizeof(int), 1, file);  // Taille des tableaux

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


void game(int** t, int size, int* size_c, int* size_m, int banana, Attacker** crab, Defender** monkey, int size_pos, Position** p) {
    // Game logic goes here
    int i = -1;
    int KingMonkeyPv = rand()%5 + 1; // Random HP for the King Monkey
    printf("King Monkey HP: %d\n", KingMonkeyPv);
        while(1){  // Limit to 100 iterations for safety
            i++;
            /*int choice = choose(); // Call the choose function
            if (choice == 2) {
                char* output_file = "test_output.txt";
                save_in_file(&t, &size, size_c, size_m, &banana, &crab, &monkey, &size_pos, output_file);
                break; // Exit the game loop if the user chooses to save
            }*/
            if( i%3 == 0){ 
                crab[*size_c] = create_attacker(size_pos);
                posInitCrabs(t, size, crab[*size_c]);
                (*size_c)++;
                i = 0; // Reset i to 0 after adding a crab
            }

            showPath(t, size);
            if (size_c > 0) {  // Simplified condition

               money(crab, monkey, size_c, size_m, &banana, t);
              
            }

            tree(&banana, size_m, t, size, monkey);
            for(int j = 0; j < *size_c; j++){
                if (crab[j] != NULL) {
                    mooveCrabs(t, size, crab[j],*p, size_pos);
                    verifyWinCrab(crab,j, size, t,&KingMonkeyPv);
                }
            }

    }
}

int menu() {
    printf("Choose an option:\n");
    printf("    1. Start Game\n");
    printf("    2. Save\n");
    printf("    3. Exit\n");
    printf("Enter your choice: ");
    
    int choice;
    scanf("%d", &choice);
    return choice;
}

int main()
{
    SetConsoleOutputCP(65001);
    srand(time(NULL));  // Initialize random seed

    int size = 0;
    int banana = 4;
    int size_c = 0;  // Size of crab array
    int size_m = 0;  // Size of monkey array
    Position* pos = NULL;
    int size_pos = 0; // Size of the position array
    int** t = NULL;
    Attacker** crab = NULL;
    Defender** monkey = NULL;

    int rand = menu();
    switch (rand) {
        case 1:
                        
                            size_pos = 0; // Size of the position array
                        
                            t = generatePath(&size,&pos, &size_pos);
                            if (t == NULL) { printf("Memory allocation failed\n"); return 1;}
                        
                            const int MAX_UNITS = 1000;
                        
                            Attacker** crab = malloc(sizeof(Attacker*) * MAX_UNITS);
                            if (crab == NULL ) { printf("Erreur allocation crab\n"); return 1; }
                        
                            Defender** monkey = malloc(sizeof(Defender*) * MAX_UNITS);
                            if (monkey == NULL ) { printf("Erreur allocation monkey\n"); return 1; }
                        
                            game(t, size, &size_c, &size_m, banana, crab, monkey, size_pos, &pos);

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
                exit(1);
            } else {
                fclose(test);
            }
            int banana;
            load_from_file(&t, &size, &size_c, &size_m, &banana, &crab, &monkey, &size_pos, output_file);
            game(t, size, &size_c, &size_m, banana, crab, monkey, size_pos, &pos);
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            menu();
    }

    return 0;
}
