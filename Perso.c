#include<stdio.h>
#include<stdlib.h>
#include<string.h> // For strcpy
#include<math.h>
#include<time.h>

//Define icones
typedef struct{
  char skin[50];
  int dmg;
  int mana;
  int level;
  int type;
  int carry;
}Defender;

//Define icones
typedef struct{
  char skin[50];
  int dmg;
  int hp;
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

    strcpy(new_defender->skin, "\xE2\x9D\x95"); // Example skin, you can change it to any other skin you want
    new_defender->mana = 0;
    new_defender->level = 1;

    printf("Select type of defender?\n");
    printf("Choissisez le type de defenseur de type \n");
    printf("0. Type of defender is melee\n");
    printf("1. Type of defender is range\n");

    while (1) {
    //Char input
      if (scanf("%d", &new_defender->type) != 1) {
          printf("Invalid input. Please enter a number.\n");
          while(getchar() != '\n'); // Clear the input buffer
          new_defender->type = -1; // Set an invalid value to ensure the loop continues
          continue;
      }
      //Int input
      if (new_defender->type == 0) {
          printf("You chose Melee defender.\n");
          new_defender->carry = 1;
          new_defender->dmg = 5;
          break;
      } else if (new_defender->type == 1) {
          printf("You chose Range defender.\n");
          new_defender->dmg = 2;
          break;
      } else {
          printf("Invalid defender type. Try again.\n");
          while(getchar() != '\n');
          continue;
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

    strcpy(new_attacker->skin,"\xE2\x9D\x8C");
    new_attacker->dmg = 1;
    new_attacker->hp = 10;
    new_attacker->level = 1;
    return new_attacker;
}

void MakeWave(int wave, int Size, Attacker* t, int x){
	int coef = Size*wave;
	Attacker* tab =(Attacker*)malloc(coef*sizeof(Attacker));
	
	for(int i = 0; i<coef; i++){
		*(tab+i) = *(create_attacker());
	}
	t = tab;
}

void MakeMoney(int* money, Attacker* t, int coef){
	
	for(int i = 0; i<coef; i++){
		if((t+i)->hp <= 0){
			money = money + t[i].level;
			//Free the space when the Attacker is dead
		}
	}
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
