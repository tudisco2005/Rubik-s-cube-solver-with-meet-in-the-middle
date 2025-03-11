#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "graphic.h"
#include "solver.h"

int main() {
    Cube *cube = initCube();
    char* scramble_config;

    drawCube(cube);
    scramble_config = scrambleCube(cube, 20);
    printf("Scramble: %s\n", scramble_config);
    drawCube(cube);

    // Solve the cube
    Cube *end = initCube();
    char* result = bruteforce(cube, end, MAX_DEPTH);
    if (!result) {
        printf("Failed to solve the cube\n");
    } else {
        printf("Solved the cube in %d moves: %s\n", strlen(result), result);
    }

    freeCube(cube);
    freeCube(end);
    free(scramble_config);
    return 0;
}