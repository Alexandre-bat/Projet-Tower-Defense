#include "all.h"

int main()
{
    
    menu();

    srand(time(NULL));  // Initialize random seed
    SetConsoleOutputCP(65001);
    
    int size;
    int banana = 4;
    int size_c = 0;  // Size of crab array
    int size_m = 0;      // Size of monkey array

    Position* pos;
    int size_pos = 0; // Size of the position array

    int** t = generatePath(&size,&pos, &size_pos);
    if (t == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    const int MAX_UNITS = 1000;

    Attacker** crab = malloc(sizeof(Attacker*) * MAX_UNITS);
    if (!crab) { printf("Erreur allocation crab\n"); return 1; }

    Defender** monkey = malloc(sizeof(Defender*) * MAX_UNITS);
    if (!monkey) { printf("Erreur allocation monkey\n"); return 1; }

    game(t, size, &size_c, &size_m, &banana, crab, monkey, size_pos, &pos);

    // Free the crabs
    for (int i = 0; i < size_c; i++) {
        if (crab[i] != NULL) {
            free(crab[i]);
        }
    }
    free(crab);

    // Free the monkeys
    for (int i = 0; i < size_m; i++) {
        if (monkey[i] != NULL) {
            free(monkey[i]);
        }
    }
    free(monkey);

    // Free the map
    for (int i = 0; i < size; i++) {
        free(t[i]);
    }
    free(t);
    return 0;
}


