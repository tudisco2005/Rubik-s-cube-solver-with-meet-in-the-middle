#include <stdio.h>
#include <stdlib.h>

#include "cube.h"
#include "graphic.h"

int main() {
    Cube *cube = initCube();
    
    drawCube(cube);

    // Rotate the cube
    // rotateDOWN(cube);
    // drawCube(cube);
    // rotateR_DOWN(cube);
    // drawCube(cube);
    // rotateUP(cube);
    // drawCube(cube);
    // rotateR_UP(cube);
    // drawCube(cube);
    // rotateLEFT(cube);
    // drawCube(cube);
    // rotateR_LEFT(cube);
    // drawCube(cube);
    // rotateRIGHT(cube);
    // drawCube(cube);
    // rotateR_RIGHT(cube);
    // drawCube(cube);
    // rotateFRONT(cube);
    // drawCube(cube);
    // rotateR_FRONT(cube);
    // drawCube(cube);
    // rotateBACK(cube);
    // drawCube(cube);
    // rotateR_BACK(cube);
    // drawCube(cube);

    freeCube(cube);

    return 0;
}