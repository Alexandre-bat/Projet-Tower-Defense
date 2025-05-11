#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> // For sleep fonction


//Initialization of the structures
//For contact details of the various players
typedef struct {
    int x;
    int y;
  } Position;
  
  
//The defense player
typedef struct{
    Position pos;
    int dmg;
    int range;
    int level;
  }Defender;
  
//The actor attacks
typedef struct{
    Position pos;
    int dmg;
    int hp;
    int level;
  }Attacker;


// Function in Player.c
// Initialization of the functions used in the game 
// Function to clear the input buffer
void clear_input_buffer(); 

// Function to get the HP of the King Monkey
int King_HP(); 

// Function to choose an option in the game
int choose(); 

// Function to display the main menu
int menu(); 

// Function to create a new defender and new attacker 
Defender* create_defender();
Attacker* create_attacker();

// Function to initialize a new defender
Defender* posTulip(int** map, int size);

// Function to initialize a attacker and moove it
void posInitBee(int** map, int size, Attacker* crab);
void mooveBee( int** map, int size, Attacker* crab, Position* p, int size_pos);

// Function to make money
void Dollars(Attacker** c, Defender** p, int* size_c, int* size_m, int* money, int** map);

// Function to place a new a attacker on the map
void tree(int* money, int* m, int** t, int size, Defender** monkey);

// Function who play the game and free the memory of the game 
void Let_s_the_show_beggin();



//Function in MapFiles.c
// Function to generate the path for the game
int** generatePath(int* s, Position** pos, int* sizeofpos); 

// Function who show the path
void showPath(int** grid, int size); 

// Function to verify if the attacker win
void verifyWinCrab(Attacker** crab, int size_c, int sizeMap, int** map, int* PV, int* j); 

// Function to verify if the defender win
void verifyWinDefender(Attacker** crab, int size_c, int* j);

// Function to save the game in a file
void save_in_file(int*** t,int* size,int* size_c,int* size_m,int* money, Attacker*** crab, Defender*** monkey,int* size_pos,int* king_hp,char* output_file); 

// Function to load the game from a file
void load_from_file( int*** t,  int* size, int* size_c, int* size_m, int* money, Attacker*** crab, Defender*** monkey, int* size_pos,int* king_hp,char* input_file);

// Function to display the game
void game(int** t, int size, int* size_c, int* size_m, int money, Attacker** crab, Defender** monkey, int size_pos, Position** p, int King_Monkey_Pv);