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
