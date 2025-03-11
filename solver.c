#include "solver.h"
#include "cube.h"
#include "graphic.h"
#include <stdlib.h>
#include <stdio.h>

int evalCube(Cube* cube) {
    int score = 0;
    int expected[NUM_FACES] = {COLOR_WHITE, COLOR_YELLOW, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_ORANGE};
    for (int i = 0; i < NUM_FACES; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (cube->color[i][j][k] == expected[i]) {
                    score++;
                }
            }
        }
    }
    return score;
}

Cube* copyCube(Cube* cube) {
    Cube* new_cube = NULL;
    if ((new_cube = (Cube*)malloc(sizeof(Cube))) == NULL) {
        perror("Error allocating memory for cube");
        return NULL;
    }

    for (int i = 0; i < NUM_FACES; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                new_cube->color[i][j][k] = cube->color[i][j][k];
            }
        }
    }

    return new_cube;
}

char* bruteforce(Cube* starting, Cube* end, int max_depth) {
    if (max_depth == 0 || !starting || !end) return NULL;

    // Base case
    if (evalCube(starting) == evalCube(end)) {
        return "0";
    }

    return NULL;
}