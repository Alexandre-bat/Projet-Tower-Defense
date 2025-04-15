#include "all.h"

typedef struct {
    int x;
    int y;
    int isActive;
    int pathIndex;
} Crab;

#define MAX_CRABS 10
#define MAX_PATH 100

// Global variables
Crab crabs[MAX_CRABS];
int pathX[MAX_PATH];
int pathY[MAX_PATH];
int pathLength = 0;
int activeCrabs = 0;

// Initialize a new crab
void spawnCrab() {
    if (activeCrabs >= MAX_CRABS || pathLength == 0) return;
    
    for (int i = 0; i < MAX_CRABS; i++) {
        if (!crabs[i].isActive) {
            crabs[i].x = pathX[0];
            crabs[i].y = pathY[0];
            crabs[i].isActive = 1;
            crabs[i].pathIndex = 0;
            activeCrabs++;
            break;
        }
    }
}

// Move all active crabs along the path
void movecrabs() {
    for (int i = 0; i < MAX_CRABS; i++) {
        if (crabs[i].isActive) {
            crabs[i].pathIndex++;
            
            if (crabs[i].pathIndex >= pathLength) {
                crabs[i].isActive = 0;
                activeCrabs--;
                continue;
            }
            
            crabs[i].x = pathX[crabs[i].pathIndex];
            crabs[i].y = pathY[crabs[i].pathIndex];
        }
    }
}

// Initialize path coordinates
void initializePath(int* x, int* y, int length) {
    for (int i = 0; i < length && i < MAX_PATH; i++) {
        pathX[i] = x[i];
        pathY[i] = y[i];
    }
    pathLength = length;
}