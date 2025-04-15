#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>
#include<time.h>

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



int main(){
  srand(time(NULL));
  int money = 0;
  int wave = 0;
  Attacker* TabAtt;
  int coef;
  int SizeMap;
  printf("What is the size of the map?\n");
  scanf("%d",&SizeMap);

  Defender* defender = create_defender();
  //create a new visualisation for each lvl with money

  printf("\n\n");

  Attacker* attacker = create_attacker();
  //create a new visualisation for each lvl with money
  
  MakeWave(wave,SizeMap, TabAtt, coef);
  MakeMoney(&money,TabAtt,coef);
  free(TabAtt);	
  free(defender);
  free(attacker);
  return 0;
}