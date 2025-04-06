#include<stdio.h>
#include<stdlib.h>
#include<string.h> // For strcpy
#include <locale.h> // For UTF-8 support
#include<math.h>
#include<time.h>

//Define icones
typedef struct{
  char skin[50];
  int dmg;
  int mana;
  int speed;
  int crit;
  int level;
  int exp;
  int type;
  int carry;
}Defender;

//Define icones
typedef struct{
  char skin[50];
  int dmg;
  int hp;
  int speed;
  int dodge;
  int level;
}Attacker;

typedef struct{
  //Skins for the attacker
  char skin1[50];
  char skin2[50];
  char skin3[50];
  char skin4[50];
  //Skins for the defender
  char skin5[50];
  char skin6[50];
  char skin7[50];
}Visualisation;

// Function to create a new defender
//Define icones for the defender 
Defender* create_defender() {

    Defender* new_defender = (Defender*)malloc(sizeof(Defender));

    if (new_defender == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strcpy(new_defender->skin, "\xF0\x9F\x9A\xB9"); // Example skin, you can change it to any other skin you want
    new_defender->dmg = rand()%10 + 1;
    new_defender->mana = 0;
    new_defender->speed = rand()%10 + 1;
    new_defender->crit = rand()%10 + 1;
    new_defender->level = 1;
    new_defender->exp = 0;

    printf("Select type of defender?\n");
    printf("Choissisez le type de defenseur de type \n");
    printf("0. Type of defender is melee\n");
    printf("1. Type of defender is range\n");

    while (1) {
      if (scanf("%d", &new_defender->type) != 1) {
          printf("Invalid input. Please enter a number.\n");
          while(getchar() != '\n'); // Clear the input buffer
          new_defender->type = -1; // Set an invalid value to ensure the loop continues
          continue;
      }
      if (new_defender->type == 0) {
          printf("You chose Melee defender.\n");
          new_defender->carry = 1;
          break;
      } else if (new_defender->type == 1) {
          printf("You chose Range defender.\n");
          new_defender->carry = rand() % 5 + 3;
          break;
      } else {
          printf("Invalid defender type. Try again.\n");
      }
  }
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

    strcpy(new_attacker->skin,"\xF0\x9F\x9A\xBA");
    new_attacker->dmg = rand()%10 + 1;
    new_attacker->hp = rand()%10 + 10;
    new_attacker->speed = rand()%10 + 1;
    new_attacker->dodge = rand()%2;
    new_attacker->level = 1;
    return new_attacker;
}

void show_defender(Defender* defender){
    printf("Defender stats:\n");
    printf("  Skin: %s\n", defender->skin);
    printf("  Damage: %d\n", defender->dmg);
    printf("  Mana: %d\n", defender->mana);
    printf("  Speed: %d\n", defender->speed);
    printf("  Critical Hit Chance: %d\n", defender->crit);
    printf("  Level: %d\n", defender->level);
    printf("  Experience: %d\n", defender->exp);
    printf("  Type: %s\n", (defender->type == 0) ? "Melee" : "Range");
    printf("  Carry: %d\n", defender->carry);
}

void show_attacker(Attacker* attacker){
    printf("Attacker stats:\n");
    printf("  Skin: %s\n", attacker->skin);
    printf("  Damage: %d\n", attacker->dmg);
    printf("  HP: %d\n", attacker->hp);
    printf("  Speed: %d\n", attacker->speed);
    printf("  Dodge Chance: %d\n", attacker->dodge);
    printf("  Level: %d\n", attacker->level);
}






int main(){
  setlocale(LC_ALL, ""); // Set the locale to support UTF-8 characters
  srand(time(NULL));

  Defender* defender = create_defender();
  show_defender(defender);
  Attacker* attacker = create_attacker();
  show_attacker(attacker);

  free(defender);
  free(attacker);
  return 0;
}

