#include "Biblio.h"



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
            return choose();
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





// Function to create a new defender
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
 



void Let_s_the_show_beggin(){
    srand(time(NULL));  // Initialize random seed

    int size = 0;
    int banana = 4;
    int size_c = 0;  // Size of crab array
    int size_m = 0;  // Size of monkey array
    Position* pos = NULL;
    int size_pos = 0; // Size of the position array
    int** t = NULL;
    int king_hp;
    Attacker** crab = NULL;
    Defender** monkey = NULL;

    int what_a_choise = menu();
    switch (what_a_choise) {
        case 1:        
            size_pos = 0; // Size of the position array
        
            t = generatePath(&size,&pos, &size_pos);
            if (t == NULL) { printf("Memory allocation failed\n"); exit(1);}
        
            const int MAX_UNITS = 1000;
        
            crab = malloc(sizeof(Attacker*) * MAX_UNITS);
            if (crab == NULL ) { printf("Erreur allocation crab\n"); exit(1); }
        
            monkey = malloc(sizeof(Defender*) * MAX_UNITS);
            if (monkey == NULL ) { printf("Erreur allocation monkey\n"); exit(1); }
        	
            king_hp = rand()%5+1;	
            game(t, size, &size_c, &size_m, banana, crab, monkey, size_pos, &pos, king_hp);

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
            load_from_file(&t, &size, &size_c, &size_m, &banana, &crab, &monkey, &size_pos, &king_hp, output_file);
            game(t, size, &size_c, &size_m, banana, crab, monkey, size_pos, &pos, king_hp);
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
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            menu();
    }
}
