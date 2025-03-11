#ifndef SOLVER_H
#define SOLVER_H

#include "cube.h"

#define MAX_DEPTH 20 // Maximum depth of the search tree (god numbers)

int evalCube(Cube* cube);
Cube* copyCube(Cube* cube);
char* bruteforce(Cube* starting, Cube* end, int max_depth);

#endif