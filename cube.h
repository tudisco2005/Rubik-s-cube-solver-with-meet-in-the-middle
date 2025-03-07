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
    COLOR_YELLOW = 0,
    COLOR_WHITE,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_ORANGE,
    COLOR_RED
} ColorFace;


typedef enum {
    MOVE_UP,
    MOVE_R_UP,
    MOVE_DOWN,
    MOVE_R_DOWN,
    MOVE_RIGHT,
    MOVE_R_RIGHT,
    MOVE_LEFT,
    MOVE_R_LEFT,
    MOVE_FRONT,
    MOVE_R_FRONT,
    MOVE_BACK,
    MOVE_R_BACK
} Move;

typedef struct {
    int color[NUM_FACES][SIZE][SIZE];
} Cube;

Cube* initCube();
void printCube();
static void rotateFaceClockwise(Cube* cube, Face face);
static void rotateFaceCounterClockwise(Cube* cube, Face face);
void rotateDOWN(Cube* cube);
void rotateR_DOWN(Cube* cube);
void rotateUP(Cube* cube);
void rotateR_UP(Cube* cube);
void rotateLEFT(Cube* cube);
void rotateR_LEFT(Cube* cube);
void rotateRIGHT(Cube* cube);
void rotateR_RIGHT(Cube* cube);
void rotateFRONT(Cube* cube);
void rotateR_FRONT(Cube* cube);
void rotateBACK(Cube* cube);
void rotateR_BACK(Cube* cube);
void rotate(Cube* cube, Move move);
void freeCube(Cube* cube);

#endif // CUBE_H