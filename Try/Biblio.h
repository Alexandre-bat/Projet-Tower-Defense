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
