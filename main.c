#include <stdio.h>
#include <stdlib.h>

#include "cube.h"
#include "graphic.h"

int main() {
    Cube *cube = initCube();
    
    rotateDOWN(cube);
    rotateR_DOWN(cube);
    drawCube(cube);

    freeCube(cube);

    return 0;
}