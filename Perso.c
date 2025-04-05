#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

typedef struct{
  int dmg;
  int hp;
  int mana;
  int speed;
  int crit;
  int dodge;
  int heal;
  int level;
  int exp;
  int type;
  int carry;
}Defender;

typedef struct{
  int dmg;
  int hp;
  int mana;
  int speed;
  int crit;
  int dodge;
  int heal;
  int level;
  int exp;
  int carry;
}Attacker;

// Function to create a new defender
Defender* create_defender() {

    Defender* new_defender = (Defender*)malloc(sizeof(Defender));

    if (new_defender == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    new_defender->dmg = rand()%10 + 1;
    new_defender->hp = rand()%10 + 10;
    new_defender->mana = 0;
    new_defender->speed = rand()%10 + 1;
    new_defender->crit = rand()%10 + 1;
    new_defender->dodge = rand()%2;
    new_defender->heal = 100;
    new_defender->level = 1;
    new_defender->exp = 0;
    printf("Quel type de défenseur voulez-vous ?\n");
    printf("Choissisez le type de défenseur de type \n");
    printf("0. Défenseur de type càc\n");
    printf("1. Défenseur de type distance\n");
    while((scanf("%d", &new_defender->type) != 0 || "%d", &new_defender->type) != 1) {
    if(new_defender->type == 0) {
        printf("Vous avez choisi un défenseur de type càc\n");
        new_defender->carry = 1;

      } else if(new_defender->type == 1) {
          printf("Vous avez choisi un défenseur de type distance\n");
          new_defender->carry = rand()%5 + 3;
      }
      else{
          printf("Type de défenseur invalide. Veuillez réessayer.\n");
          continue; // Continue the loop if the input is invalid
      }
  }
    return new_defender;
}

// Function to create a new attacker
Attacker* create_attacker(){

    Attacker* new_attacker = (Attacker*)malloc(sizeof(Attacker));

    if (new_attacker == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    new_attacker->dmg = rand()%10 + 1;
    new_attacker->hp = rand()%10 + 10;
    new_attacker->mana = 0;
    new_attacker->speed = rand()%10 + 1;
    new_attacker->crit = rand()%10 + 1;
    new_attacker->dodge = rand()%2;
    new_attacker->heal = 100;
    new_attacker->level = 1;
    new_attacker->exp = 0;
    return new_attacker;
}






int main(){
  srand(time(NULL)); 
  Defender* defender = create_defender();
  Attacker* attacker = create_attacker();

  printf("hello world\n");
  // Test1
  //  Test2
  printf("bonjour\n");
}

