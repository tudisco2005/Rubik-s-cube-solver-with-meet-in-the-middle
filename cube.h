#ifndef CUBE_H
#define CUBE_H

#include "raylib.h"

// size of cube
#define SIZE 3
#define NUM_FACES 6

typedef enum {
    FACE_UP = 0,
    FACE_DOWN = 1,
    FACE_LEFT = 2,
    FACE_RIGHT = 3,
    FACE_FRONT = 4,
    FACE_BACK = 5
} Face;

typedef enum {
    COLOR_WHITE = 0,
    COLOR_YELLOW,
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_GREEN,
    COLOR_BLUE
} ColorFace;

typedef struct {
    int color[6][SIZE][SIZE];
} Cube;

Cube* initCube();
void printCube();
void rotateDOWN(Cube* cube);
void rotateR_DOWN(Cube* cube);
void freeCube(Cube* cube);

#endif // CUBE_H