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
    int range;
    int level;
  }Defender;
  
typedef struct{
    Position pos;
    int dmg;
    int hp;
    int level;
  }Attacker;

void clear_input_buffer();
int King_HP();
int choose();
int menu();
int** generatePath(int* s, Position** pos, int* sizeofpos);
void showPath(int** grid, int size);
void verifyWinCrab(Attacker** crab, int size_c, int sizeMap, int** map, int* PV);
void verifyWinDefender(Attacker** crab, int size_c);
void save_in_file(int*** t,int* size,int* size_c,int* size_m,int* banana, Attacker*** crab, Defender*** monkey,int* size_pos,int* king_hp,char* output_file);
void load_from_file( int*** t,  int* size, int* size_c, int* size_m, int* banana, Attacker*** crab, Defender*** monkey, int* size_pos,int* king_hp,char* input_file);
void game(int** t, int size, int* size_c, int* size_m, int banana, Attacker** crab, Defender** monkey, int size_pos, Position** p, int King_Monkey_Pv);
Defender* create_defender();
Attacker* create_attacker();
Defender* posMonkey(int** map, int size);
void posInitCrabs(int** map, int size, Attacker* crab);
void mooveCrabs( int** map, int size, Attacker* crab, Position* p, int size_pos);
void tree(int* banana, int* m, int** t, int size, Defender** monkey);
void money(Attacker** c, Defender** p, int* size_c, int* size_m, int* banana, int** map);
void Let_s_the_show_beggin();