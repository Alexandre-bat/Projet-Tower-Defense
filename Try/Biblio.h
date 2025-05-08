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




int** generatePath(int* nbsp, Position** pos, int* sizeofpos);
void showPath(int** grid, int size);
void verifyWinCrab(Attacker** crab, int size_c, int sizeMap, int** map, int* PV);
void save_in_file(int*** t,int* size,int* size_c,int* size_m,int* banana,Attacker*** crab,Defender*** monkey,int* size_pos,char* output_file);
void load_from_file(int*** t, int* size, int* size_c, int* size_m, int* banana, Attacker*** crab, Defender*** monkey, int* size_pos, char* input_file);
void game(int** t, int size, int* size_c, int* size_m, int banana, Attacker** crab, Defender** monkey, int size_pos, Position** p);

Defender* create_defender();
Attacker* create_attacker();
Defender* posMonkey(int** map, int size);
void posInitCrabs(int** map, int size, Attacker* crab);
void mooveCrabs( int** map, int size, Attacker* crab, Position* p, int size_pos);
void tree(int* banana, int* m, int** t, int size, Defender** monkey);
void money(Attacker** c, Defender** p, int* size_c, int* size_m, int* banana, int** map);
void Let_s_the_show_beggin();