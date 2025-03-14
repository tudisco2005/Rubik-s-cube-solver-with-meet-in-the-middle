#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cube.h"
#include "solver.h"

int main() {
    Cube *cube = initCube();
    // char scramble_config[] = "L R u F B R"; // 6 moves
    // char scramble_config[] = "l r U f b r"; // 14 moves - 6 moves
    // char scramble_config[] = "R L F u D F2 R L"; // 15 moves - 8 moves
    char scramble_config[] = "L R F B U D l r f b u d"; // 16 moves
    // char scramble_config[] = "R L U2 F u D F2 R2 B2 L U2 f b U R2 D F2 U R2 U"; // 20 moves

    // Scramble the cube
    scrambleCube(cube, scramble_config);
    printCube(cube);

    // Solve the cube
    Cube *end = initCube();

    printf("scramble_config: %s\n", scramble_config);
    char* solution = meetInTheMiddle(cube, end, 7);
    printf("\nSolution: %s\n", solution);

    scrambleCube(cube, solution);
    printCube(cube);

    free(solution);
    freeCube(cube);
    freeCube(end);
    return 0;
}