#include "Biblio.h"


void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Clear the input buffer
    // This will consume all characters until a newline or end of file (EOF) is found
}


int King_HP() {
    char input[50];
    int hp;
    const int MIN_HP = 1;    // Minimum acceptable HP
    const int MAX_HP = 10;  // Maximum acceptable HP

    printf("How many HP should the king have? (%d-%d)\n", MIN_HP, MAX_HP);

    if (fgets(input, sizeof(input), stdin)) { // Read input from the user
        if (sscanf(input, "%d", &hp) == 1) { // Try to parse the input as an integer
            if (hp >= MIN_HP && hp <= MAX_HP) { // Check if the input is within the acceptable range
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

    printf("Error reading input.\n Back to menu...\n");
    sleep(3);
    system("make");
    return 0;
}


int choose() {
    char input[50];
    int c;

    printf("\n  ╔════════════════════════╗\n");
    printf("  ║      GAME MENU         ║\n");
    printf("  ╠════════════════════════╣\n");
    printf("  ║  0. Continue           ║\n");
    printf("  ║  1. Save               ║\n");
    printf("  ╚════════════════════════╝\n");
    printf("Enter your choice: ");

    if (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &c) == 1) {
            switch (c) {
                case 0:
                    return 0;
                case 1:
                    printf("\n✓ Game saved successfully.\n Back to the menu\n");
             	    sleep(3);
                    return 1;
                default:
                    printf("\n✗ Invalid choice. Please try again.\n");
                    return choose();
            }
        } else {
            printf("\n✗ Invalid input. Please enter a number.\n");
            return choose();
        }
    }

    printf("\n✗ Error reading input\n");
    return 2;
}



int menu() {
    char input[50];
    int choice;

    printf("\n  ╔═══════════════════════╗\n");
    printf("  ║      MAIN MENU        ║\n");
    printf("  ╠═══════════════════════╣\n");
    printf("  ║  1. Start Game        ║\n");
    printf("  ║  2. Save              ║\n");
    printf("  ║  3. Exit              ║\n");
    printf("  ╚═══════════════════════╝\n");
    printf("Enter your choice: ");

    if (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%d", &choice) == 1) {
            switch (choice) {
                case 1:
                    printf("\n➤ Let the show begin!\n");
                    return 1;
                case 2:
                    return 2;
                case 3:
                    printf("\n➤ Au revoir\n");
                    return 3;
                default:
                    printf("\n❌ Invalid choice. Please try again.\n");
                    return menu();
            }
        } else {
            printf("\n❌ Invalid input. Please enter a number.\n");
            return menu();
        }
    }

    printf("\n❌ Error reading input\n");
    return 4;
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
    new_attacker->hp = 4;
    new_attacker->level = 0;
    return new_attacker;
}



Defender* posTulip(int** map, int size) {
    Defender* monkey = create_defender();
    if (monkey == NULL) return NULL;
    int x, y;

    while (1) {
        printf("Enter the position of the tulip (x): ");
        scanf("%d", &x); 
        x -= 1;
        // Validate the input for x
        if (x < 0 || x > size - 1) { 
            printf("Position must be between 1 and %d.\n", size);
            free(monkey);
            exit(11);
        }
        
        clear_input_buffer();
        
        printf("Enter the position of the tulip (y): ");
        scanf("%d", &y); 
        y -= 1;
        // Validate the input for y
        if (y < 0 || y > size - 1) { 
            printf("Position must be between 1 and %d.\n", size);
            exit(12);
        }
        clear_input_buffer();
        // Check if the position is valid
        if (map[y][x] == 1 || map[y][x] == 2 || map[y][y] == -1) {
            printf("Can't put a tulip here.\n");
            exit(13);
        }

        // Check if the position is too close to the crab spawn point
        if (x >= 0 && y >= 0 && x < size && y < size) {
            // Check if position is near spawn point (x=0)
            int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};  // Vertical offsets
            int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};  // Horizontal offsets
            
            // Check current position
            if (map[y][x] == 100 || map[y][x] == 10) {
                printf("Cannot place tulip on spawn point.\n");
                exit(14);
            }
            
            // Check all adjacent positions
            for (int i = 0; i < 8; i++) {
                int newY = y + dy[i];
                int newX = x + dx[i];
                
                if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
                    if (newX == 0 && (map[newY][newX] == 100 || map[newY][newX] == 10)) {
                        printf("Cannot place tulip adjacent to spawn point.\n");
                        exit(15);
                    }
                }
            }
        }

        // Check if the position is adjacent to another monkey or crab
        if ((y > 0 && map[y-1][x] == 1) ||                    // North
            (y < size-1 && map[y+1][x] == 1) ||               // South
            (x > 0 && map[y][x-1] == 1) ||                    // West
            (x < size-1 && map[y][x+1] == 1) ||               // East
            (y > 0 && x > 0 && map[y-1][x-1] == 1) ||        // Northwest
            (y > 0 && x < size-1 && map[y-1][x+1] == 1) ||   // Northeast
            (y < size-1 && x > 0 && map[y+1][x-1] == 1) ||   // Southwest
            (y < size-1 && x < size-1 && map[y+1][x+1] == 1)) {
            map[y][x] = 2;
            monkey->pos.x = x;
            monkey->pos.y = y;
            printf("Tulip placed at (%d, %d)\n", x+1, y+1);
            return monkey;
        }

        // If the position is not valid, free the memory and exit
        printf("Tulip cannot be placed here.\n");
        exit(16);
    }
}



void posInitBee(int** map, int size, Attacker* crab) {
    // Check if the crab is valid
    if (crab == NULL) {
        printf("Crab is NULL. Cannot initialize.\n");
        exit(6); 
    }
    for (int i = 0; i < size; i++) {
        if (map[i][0] == 100 || map[i][0] == 1) {
        if(map[i][1] == 10){
            printf("Can't put a crab here.\n");
            exit(5); 
        }
            map[i][0] = 10;
            crab->pos.x = 0;
            crab->pos.y = i;
            crab->level++;
            return;
        }
    }
    printf("No valid starting point for crab. Releasing memory.\n");
    exit(4); 
}


void mooveBee( int** map, int size, Attacker* crab, Position* p, int size_pos) {
    if (crab == NULL) return;  // Check if crab is valid
    if(p == NULL) return;  // Check if position array is valid 
    if(size_pos <= 0) return;  // Check if position array size is valid
    int l = crab->level;

    // Check current crab position (ensure it's not out of bounds)
    if (map[crab->pos.y][crab->pos.x] == 10) {
        
        // If position is valid, make the change
        map[crab->pos.y][crab->pos.x] = 1;  // Remove crab from current position
        if (crab->pos.x == 0) {
            map[crab->pos.y][crab->pos.x] = 100;  // Restore starting point
        }
    }
    
    // Check if next position is within bounds
    if (l < size_pos && p[l].x >= 0 && p[l].y >= 0 && p[l].x < size && p[l].y < size) {
        printf("Bee moving to x: %d, y: %d\n", p[l].x, p[l].y+1);
        crab->pos.x = p[l].x;  // Update crab position
        crab->pos.y = p[l].y;
        crab->level++;  // Increment crab level

    // Update new crab position on map
    if (map[crab->pos.y][crab->pos.x] != 10) {
          map[crab->pos.y][crab->pos.x] = 10;  // Mark current position with "10" for crab
      }
        
    } else {
        printf("Moving conditions: level %d < size %d, pos(%d,%d) within [0,%d]\n", 
               l, size, p[l].x, p[l].y, size-1);
        printf("Invalid move for crab at level %d.\n", l);
    }
}


void Dollars(Attacker** c, Defender** p, int* size_c, int* size_m, int* money, int** map, int* score) {
    if (*size_c == 0 || *size_m == 0) return;
    for (int i = 0; i < *size_m; i++) {
        if (p[i] == NULL) continue;  // ⚠️ Crash protection

        int e = p[i]->pos.x;
        int f = p[i]->pos.y;
        
        int r = p[i]->range;

        int j = 0;
        while (j < *size_c) {
            if (c[j] == NULL) { j++; continue; }  // ⚠️ Crash protection

            int o = c[j]->pos.x;
            int n = c[j]->pos.y;
            int dx = abs(e - o);
            int dy = abs(f - n);
            if (dx <= r && dy <= r) {
                c[j]->hp -= p[i]->dmg;
                printf("Bee %d is attacked by tulip %d; HP: %d\n", j, i, c[j]->hp);
                if (c[j]->hp <= 0) {
                  (*score)++;
                  map[n][o] = 1;
                  if( o == 1 ){
                    map[n][o] = 101;
                  }
                  (*money) ++;
                  free(c[j]);
                  for (int k = j; k < *size_c - 1; k++) {
                      c[k] = c[k + 1];
                  }
                  c[*size_c - 1] = NULL; // Nullify the last element
                  (*size_c)--;
                  continue;
                }
            }
            j++;
        }
    }
}

void tree(int* money, int* m, int** t, int size, Defender** tulip) {
    int choice;
    printf("\n========== TULIP SHOP ==========\n");
    
    if(*money < 2) {
        printf("\n⚠️  You have no money or no tulip!\n");
        sleep(2);
        return;
    }
    
    printf("\n Current money: %d\n", *money);
    printf("\nAvailable actions:\n");
    printf("---------------------------\n");
    printf("1. 🌷 Buy new tulip    (2 dollars)\n");
    printf("2. ⭐ Upgrade tulip    (3 dollars)\n");
    printf("0. ➡️  Skip\n");
    printf("---------------------------\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);
    clear_input_buffer();
    
    switch(choice) {
        case 1: 
            if((*money) >= 2) {
                printf("\n=== BUYING NEW TULIP ===\n");
                tulip[*m] = posTulip(t, size);
                if(tulip[*m] != NULL) {
                    *money -= 2;
                    (*m)++;
                    printf("✅ New tulip successfully added!\n");
                }
            } else {
                printf("\n❌ Not enough money!\n"); 
                sleep(2);
            }
            break;

        case 2:
            if(*money >= 3 && *m > 0) {
                printf("\n=== UPGRADE TULIP ===\n");
                int tulip_id;
                printf("Which tulip to upgrade? (1-%d): ", *m);
                scanf("%d", &tulip_id);
                tulip_id--;
                clear_input_buffer();
                
                if(tulip_id >= 0 && tulip_id < *m && tulip[tulip_id] != NULL) {
                    printf("\nUpgrade options:\n");
                    printf("---------------------------\n");
                    printf("1. 🎯 Range (current: %d)\n", tulip[tulip_id]->range);
                    printf("2. 💪 Damage (current: %d)\n", tulip[tulip_id]->dmg);
                    printf("---------------------------\n");
                    printf("Enter your choice: ");
                    
                    int upgrade_choice;
                    scanf("%d",&upgrade_choice);
                    clear_input_buffer();
                    
                    switch(upgrade_choice) {
                        case 1:
                            if( tulip[tulip_id]->range++ > 3){
                              printf("This tulip is already very strong");
                              break;
                            }
                            tulip[tulip_id]->range++;
                            *money -= 3;
                            printf("✅ Range increased to %d\n", tulip[tulip_id]->range);
                            sleep(1);
                            break;
                        case 2:
                        if( tulip[tulip_id]->dmg++ > 4){
                              printf("This tulip is already very strong");
                              break;
                            }
                        tulip[tulip_id]->dmg++;
                        *money -= 3;
                        printf("✅ Damage increased to %d\n", tulip[tulip_id]->dmg);
                        sleep(1);
                        break;
                        default:
                            printf("❌ Invalid upgrade choice\n");
                            sleep(2);
                    }
                } else {
                    printf("❌ Invalid tulip ID\n");
                    sleep(2);
                }
            } else {
                printf("\n❌ Not enough money or no tulips to upgrade!\n");
                sleep(2);
            }
            break;

        case 0:
            printf("\n➡️ Skipping shop...\n");
            break;

        default:
            printf("\n❌ Invalid choice\n");
            break;
    }
    printf("\n================================\n");
}


void Let_s_the_show_beggin(){
    srand(time(NULL));  // Initialize random seed

    int size = 0;
    int money = 3;
    int size_c = 0;  // Size of crab array
    int size_m = 0;  // Size of monkey array
    Position* pos = NULL;
    int size_pos = 0; // Size of the position array
    int** t = NULL;
    int k_hp;
    Attacker** crab = NULL;
    Defender** monkey = NULL;
    int score = 0;

    // Call the save function here
    char* output_file = "test_output.txt";
    FILE* test = fopen(output_file, "r");

    int what_a_choise = menu();
    switch (what_a_choise) {
        case 1:        
            size_pos = 0; // Size of the position array
        
            t = generatePath(&size,&pos, &size_pos);
            if (t == NULL) { printf("Memory allocation failed\n"); exit(1);}
            
            showPath(t,size);
        
        
            const int MAX_UNITS = 1000;
        
            crab = malloc(sizeof(Attacker*) * MAX_UNITS);
            if (crab == NULL ) { printf("Erreur allocation crab\n"); exit(2); }
        
            monkey = malloc(sizeof(Defender*) * MAX_UNITS);
            if (monkey == NULL ) { printf("Erreur allocation monkey\n"); exit(3); }
        	
            k_hp = King_HP();
            game(t, size, &size_c, &size_m, money, crab, monkey, size_pos, &pos, k_hp, score);
            // Free position array
            free(pos);
            pos = NULL;

            // Free each crab and the crab array
            for (int i = 0; i < size_c; i++) {
                if (crab[i] != NULL) {
                    free(crab[i]);
                }
            }
            free(crab);
            crab = NULL;

            // Free each monkey and the monkey array
            for (int i = 0; i < size_m; i++) {
                if (monkey[i] != NULL) {
                    free(monkey[i]);
                }
            }
            free(monkey);
            monkey = NULL;

            // Free each row of the map and then the map itself
            for (int i = 0; i < size; i++) {
                free(t[i]);
            }
            free(t);
            t = NULL;
            system("make"); 
            break;
        case 2:
            if (test == NULL) {
                printf("Save file doesn't exist.\n Back to menu...\n");
                sleep(3);
                system("make");
            }
            fclose(test);
            int money;
            load_from_file(&t, &size, &size_c, &size_m, &money, &crab, &monkey, &size_pos, &k_hp , &score, output_file);
            showPath(t,size);
            game(t, size, &size_c, &size_m, money, crab, monkey, size_pos, &pos, k_hp, score);
            // Free position array
            free(pos);
            pos = NULL;

            // Free each crab and the crab array
            for (int i = 0; i < size_c; i++) {
                if (crab[i] != NULL) {
                    free(crab[i]);
                }
            }
            free(crab);
            crab = NULL;

            // Free each monkey and the monkey array
            for (int i = 0; i < size_m; i++) {
                if (monkey[i] != NULL) {
                    free(monkey[i]);
                }
            }
            free(monkey);
            monkey = NULL;

            // Free each row of the map and then the map itself
            for (int i = 0; i < size; i++) {
                free(t[i]);
            }
            free(t);
            t = NULL;
            system("make"); 
            break;
        case 3:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            menu();
    }
}
