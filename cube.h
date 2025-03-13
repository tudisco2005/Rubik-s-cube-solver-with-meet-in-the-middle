#ifndef CUBE_H
#define CUBE_H

#include "raylib.h"

// table
// depth	Number of possible positions
// 0	    1
// 1	    18
// 2	    243
// 3	    3,240
// 4	    43,239
// 5	    574,908
// 6	    7,618,438
// 7	    100,803,036
// 8	    1,332,343,288
// 9	    17,596,479,795
// 10	    232,248,063,316
// 11	    3,063,288,809,012
// 12	    40,374,425,656,248
// 13	    531,653,418,284,628
// 14	    6,989,320,578,825,358
// 15	    91,365,146,187,124,313
// 16	    about 1,100,000,000,000,000,000
// 17	    about 12,000,000,000,000,000,000
// 18	    about 29,000,000,000,000,000,000
// 19	    about 1,500,000,000,000,000,000
// 20	    about 490,000,000

// size of cube
#define SIZE 3
#define NUM_FACES 6
#define NUM_MOVES 18

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
    COLOR_YELLOW = 1,
    COLOR_ORANGE = 2,
    COLOR_RED = 3,
    COLOR_GREEN = 4,
    COLOR_BLUE = 5
} ColorFace;


typedef enum {
    MOVE_UP,
    MOVE_R_UP,
    MOVE_2_UP,
    MOVE_DOWN,
    MOVE_R_DOWN,
    MOVE_2_DOWN,
    MOVE_RIGHT,
    MOVE_R_RIGHT,
    MOVE_2_RIGHT,
    MOVE_LEFT,
    MOVE_R_LEFT,
    MOVE_2_LEFT,
    MOVE_FRONT,
    MOVE_R_FRONT,
    MOVE_2_FRONT,
    MOVE_BACK,
    MOVE_R_BACK,
    MOVE_2_BACK
} Move;

typedef struct {
    char color[NUM_FACES][SIZE][SIZE];
} Cube;

Cube* initCube();
void printCube();
void rotateFaceClockwise(Cube* cube, Face face);
void rotateFaceCounterClockwise(Cube* cube, Face face);
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

void rotateUP_2(Cube* cube);
void rotateDOWN_2(Cube* cube);
void rotateLEFT_2(Cube* cube);
void rotateRIGHT_2(Cube* cube);
void rotateFRONT_2(Cube* cube);
void rotateBACK_2(Cube* cube);

char* rotate(Cube* cube, Move move);

char* scrambleCubeRandom(Cube* cube, int num_moves);
char* scrambleCube(Cube* cube, char* moves);

void freeCube(Cube* cube);

#endif // CUBE_H