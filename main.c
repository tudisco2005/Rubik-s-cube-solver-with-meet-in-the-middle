#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "graphic.h"
#include "solver.h"

int main() {
    Cube *cube = initCube();
    //char scramble_config[] = "LRuFBR";
    char scramble_config[] = "lrUfbr";

    drawCube(cube);
    printCube(cube);
    
    // Scramble the cube
    scrambleCube(cube, scramble_config);
    drawCube(cube);
    printCube(cube);

    printf("memory size: %ld\n", sizeof(*cube));
    // Solve the cube
    Cube *end = initCube();

    freeCube(cube);
    freeCube(end);
    return 0;
}