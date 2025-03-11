#include "cube.h"
#include "utils.h"
#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cube* initCube() {
    Cube* cube = NULL;

    if((cube = (Cube*)malloc(sizeof(Cube))) == NULL) {
        perror("Error allocating memory for cube");
        return NULL;
    }

    // Standard color scheme mapping:
    // UP (top) = WHITE
    // DOWN (bottom) = YELLOW
    // LEFT = ORANGE
    // RIGHT = RED
    // FRONT = GREEN
    // BACK = BLUE

    // Initialize each face with its color
    for (int j = 0; j < SIZE; j++) {
        for (int k = 0; k < SIZE; k++) {
            cube->color[FACE_UP][j][k] = COLOR_WHITE;     // Top face is white
            cube->color[FACE_DOWN][j][k] = COLOR_YELLOW;  // Bottom face is yellow
            cube->color[FACE_LEFT][j][k] = COLOR_ORANGE;  // Left face is orange
            cube->color[FACE_RIGHT][j][k] = COLOR_RED;    // Right face is red
            cube->color[FACE_FRONT][j][k] = COLOR_GREEN;  // Front face is green
            cube->color[FACE_BACK][j][k] = COLOR_BLUE;    // Back face is blue
        }
    }

    return cube;
}
// Helper function to rotate a single face clockwise
static void rotateFaceClockwise(Cube* cube, Face face) {
    int temp[SIZE][SIZE];
    
    // Copy the current state to a temporary array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = cube->color[face][i][j];
        }
    }
    
    // Perform clockwise rotation
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cube->color[face][j][SIZE-1-i] = temp[i][j];
        }
    }
}

// Helper function to rotate a single face counter-clockwise
static void rotateFaceCounterClockwise(Cube* cube, Face face) {
    int temp[SIZE][SIZE];
    
    // Copy the current state to a temporary array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = cube->color[face][i][j];
        }
    }
    
    // Perform counter-clockwise rotation
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cube->color[face][SIZE-1-j][i] = temp[i][j];
        }
    }
}

// Rotate DOWN face clockwise
void rotateDOWN(Cube* cube) {
    int temp[SIZE];
    
    // Store the front row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][SIZE-1][i];
    }
    
    // FRONT -> RIGHT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][SIZE-1][i] = cube->color[FACE_LEFT][SIZE-1][i];
    }
    
    // LEFT -> BACK
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][SIZE-1][i] = cube->color[FACE_BACK][SIZE-1][i];
    }
    
    // BACK -> RIGHT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][SIZE-1][i] = cube->color[FACE_RIGHT][SIZE-1][i];
    }
    
    // RIGHT -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][SIZE-1][i] = temp[i];
    }
    
    // Rotate the DOWN face clockwise
    rotateFaceClockwise(cube, FACE_DOWN);
}

// Rotate DOWN face counter-clockwise
void rotateR_DOWN(Cube* cube) {
    int temp[SIZE];
    
    // Store the front row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][SIZE-1][i];
    }
    
    // FRONT -> LEFT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][SIZE-1][i] = cube->color[FACE_RIGHT][SIZE-1][i];
    }
    
    // RIGHT -> BACK
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][SIZE-1][i] = cube->color[FACE_BACK][SIZE-1][i];
    }
    
    // BACK -> LEFT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][SIZE-1][i] = cube->color[FACE_LEFT][SIZE-1][i];
    }
    
    // LEFT -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][SIZE-1][i] = temp[i];
    }
    
    // Rotate the DOWN face counter-clockwise
    rotateFaceCounterClockwise(cube, FACE_DOWN);
}

// Rotate UP face clockwise
void rotateR_UP(Cube* cube) {
    int temp[SIZE];
    
    // Store the front row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][0][i];
    }
    
    // FRONT -> RIGHT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][0][i] = cube->color[FACE_LEFT][0][i];
    }
    
    // LEFT -> BACK
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][0][i] = cube->color[FACE_BACK][0][i];
    }
    
    // BACK -> RIGHT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][0][i] = cube->color[FACE_RIGHT][0][i];
    }
    
    // RIGHT -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][0][i] = temp[i];
    }
    
    rotateFaceCounterClockwise(cube, FACE_UP);
}

// Rotate UP face clockwise
void rotateUP(Cube* cube) {
    int temp[SIZE];
    
    // Store the front row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][0][i];
    }
    
    // FRONT -> LEFT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][0][i] = cube->color[FACE_RIGHT][0][i];
    }
    
    // RIGHT -> BACK
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][0][i] = cube->color[FACE_BACK][0][i];
    }
    
    // BACK -> LEFT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][0][i] = cube->color[FACE_LEFT][0][i];
    }
    
    // LEFT -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][0][i] = temp[i];
    }
    
    rotateFaceClockwise(cube, FACE_UP);
}

// Rotate LEFT face clockwise
void rotateLEFT(Cube* cube) {
    int temp[SIZE];
    
    // Store the front column temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][i][0];
    }
    
    // FRONT -> DOWN
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][i][0] = cube->color[FACE_UP][i][0];
    }
    
    // UP -> BACK (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][i][0] = cube->color[FACE_BACK][SIZE-1-i][SIZE-1];
    }
    
    // BACK -> DOWN (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][SIZE-1-i][SIZE-1] = cube->color[FACE_DOWN][i][0];
    }
    
    // DOWN -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][i][0] = temp[i];
    }
    
    // Rotate the LEFT face clockwise
    rotateFaceClockwise(cube, FACE_LEFT);
}

// Rotate LEFT face counter-clockwise
void rotateR_LEFT(Cube* cube) {
    int temp[SIZE];
    
    // Store the front column temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][i][0];
    }
    
    // FRONT -> UP
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][i][0] = cube->color[FACE_DOWN][i][0];
    }
    
    // DOWN -> BACK (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][i][0] = cube->color[FACE_BACK][SIZE-1-i][SIZE-1];
    }
    
    // BACK -> UP (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][SIZE-1-i][SIZE-1] = cube->color[FACE_UP][i][0];
    }
    
    // UP -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][i][0] = temp[i];
    }
    
    // Rotate the LEFT face counter-clockwise
    rotateFaceCounterClockwise(cube, FACE_LEFT);
}

// Rotate RIGHT face clockwise
void rotateRIGHT(Cube* cube) {
    int temp[SIZE];
    
    // Store the front column temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][i][SIZE-1];
    }
    
    // FRONT -> UP
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][i][SIZE-1] = cube->color[FACE_DOWN][i][SIZE-1];
    }
    
    // DOWN -> BACK (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][i][SIZE-1] = cube->color[FACE_BACK][SIZE-1-i][0];
    }
    
    // BACK -> UP (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][SIZE-1-i][0] = cube->color[FACE_UP][i][SIZE-1];
    }
    
    // UP -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][i][SIZE-1] = temp[i];
    }
    
    // Rotate the RIGHT face clockwise
    rotateFaceClockwise(cube, FACE_RIGHT);
}

// Rotate RIGHT face counter-clockwise
void rotateR_RIGHT(Cube* cube) {
    int temp[SIZE];
    
    // Store the front column temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_FRONT][i][SIZE-1];
    }
    
    // FRONT -> DOWN
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_FRONT][i][SIZE-1] = cube->color[FACE_UP][i][SIZE-1];
    }
    
    // UP -> BACK (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][i][SIZE-1] = cube->color[FACE_BACK][SIZE-1-i][0];
    }
    
    // BACK -> DOWN (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_BACK][SIZE-1-i][0] = cube->color[FACE_DOWN][i][SIZE-1];
    }
    
    // DOWN -> FRONT (from temp)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][i][SIZE-1] = temp[i];
    }
    
    // Rotate the RIGHT face counter-clockwise
    rotateFaceCounterClockwise(cube, FACE_RIGHT);
}

// Rotate FRONT face clockwise
void rotateFRONT(Cube* cube) {
    int temp[SIZE];
    
    // Store the up row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_UP][SIZE-1][i];
    }
    
    // UP -> RIGHT (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][SIZE-1][i] = cube->color[FACE_LEFT][SIZE-1-i][SIZE-1];
    }
    
    // LEFT -> DOWN
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][i][SIZE-1] = cube->color[FACE_DOWN][0][i];
    }
    
    // DOWN -> RIGHT(with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][0][i] = cube->color[FACE_RIGHT][SIZE-i-1][0];
    }
    
    // RIGHT -> UP
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][i][0] = temp[i];
    }
    
    // Rotate the FRONT face clockwise
    rotateFaceClockwise(cube, FACE_FRONT);
}

// Rotate FRONT face counter-clockwise
void rotateR_FRONT(Cube* cube) {
    int temp[SIZE];
    
    // Store the up row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_UP][SIZE-1][i];
    }
    
    // UP -> LEFT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][SIZE-1][i] = cube->color[FACE_RIGHT][i][0];
    }
    
    // RIGHT -> DOWN (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][i][0] = cube->color[FACE_DOWN][0][SIZE-1-i];
    }
    
    // DOWN -> LEFT 
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][0][i] = cube->color[FACE_LEFT][i][SIZE-1];
    }
    
    // LEFT -> UP
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][i][SIZE-1] = temp[i];
    }
    
    // Rotate the FRONT face counter-clockwise
    rotateFaceCounterClockwise(cube, FACE_FRONT);
}

// Rotate BACK face clockwise
void rotateBACK(Cube* cube) {
    int temp[SIZE];
    
    // Store the up row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_UP][0][i];
    }
    
    // UP -> LEFT
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][0][i] = cube->color[FACE_RIGHT][i][SIZE-1];
    }
    
    // RIGHT -> DOWN (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][i][SIZE-1] = cube->color[FACE_DOWN][SIZE-1][SIZE-1-i];
    }
    
    // DOWN -> LEFT ()
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][SIZE-1][i] = cube->color[FACE_LEFT][i][0];
    }
    
    // LEFT -> UP
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][i][0] = temp[i];
    }
    
    // Rotate the BACK face clockwise
    rotateFaceClockwise(cube, FACE_BACK);
}

// Rotate BACK face counter-clockwise
void rotateR_BACK(Cube* cube) {
    int temp[SIZE];
    
    // Store the up row temporarily
    for (int i = 0; i < SIZE; i++) {
        temp[i] = cube->color[FACE_UP][0][i];
    }
    
    // UP -> RIGHT (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_UP][0][i] = cube->color[FACE_LEFT][SIZE-1-i][0];
    }
    
    // LEFT -> DOWN
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][i][0] = cube->color[FACE_DOWN][SIZE-1][i];
    }
    
    // DOWN -> RIGHT (with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_DOWN][SIZE-1][i] = cube->color[FACE_RIGHT][SIZE-1-i][SIZE-1];
    }
    
    // RIGHT -> UP
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][i][SIZE-1] = temp[i];
    }
    
    // Rotate the BACK face counter-clockwise
    rotateFaceCounterClockwise(cube, FACE_BACK);
}
// General rotation function that calls the appropriate specific function
char rotate(Cube* cube, Move move) {
    switch (move) {
        case MOVE_UP:
            rotateUP(cube);
            return 'U';
        case MOVE_R_UP:
            rotateR_UP(cube);
            return 'u';
        case MOVE_DOWN:
            rotateDOWN(cube);
            return 'D';
        case MOVE_R_DOWN:
            rotateR_DOWN(cube);
            return 'd';
        case MOVE_LEFT:
            rotateLEFT(cube);
            return 'L';
        case MOVE_R_LEFT:
            rotateR_LEFT(cube);
            return 'l';
        case MOVE_RIGHT:
            rotateRIGHT(cube);
            return 'R';
        case MOVE_R_RIGHT:
            rotateR_RIGHT(cube);
            return 'r';
        case MOVE_FRONT:
            rotateFRONT(cube);
            return 'F';
        case MOVE_R_FRONT:
            rotateR_FRONT(cube);
            return 'f';
        case MOVE_BACK:
            rotateBACK(cube);
            return 'B';
        case MOVE_R_BACK:
            rotateR_BACK(cube);
            return 'b';
    }
}

void printCube(Cube* cube) {
    for(int i = 0; i < NUM_FACES; i++) {
        switch(i) {
            case FACE_UP:
                printf("Face up:\n");
                break;
            case FACE_DOWN:
                printf("Face down:\n");
                break;
            case FACE_LEFT:
                printf("Face left:\n");
                break;
            case FACE_RIGHT:
                printf("Face right:\n");
                break;
            case FACE_FRONT:
                printf("Face front:\n");
                break;
            case FACE_BACK:
                printf("Face back:\n");
                break;
        }

        for(int j = 0; j < SIZE; j++) {
            for(int k = 0; k < SIZE; k++) {
                switch(cube->color[i][j][k]) {
                    case COLOR_WHITE:
                        PRINT_WHITE("W");
                        break;
                    case COLOR_YELLOW:
                        PRINT_YELLOW("Y");
                        break;
                    case COLOR_ORANGE:
                        PRINT_MAGENTA("O");
                        break;
                    case COLOR_RED:
                        PRINT_RED("R");
                        break;
                    case COLOR_GREEN:
                        PRINT_GREEN("G");
                        break;
                    case COLOR_BLUE:
                        PRINT_BLUE("B");
                        break;
                }
            }
            printf("\n");
        }
    }
}

char* scrambleCubeRandom(Cube* cube, int num_moves) {
    char* moves = (char*)malloc(num_moves * sizeof(char) + 1);
    if (!moves) {
        perror("Error allocating memory for moves");
        return NULL;
    }

    char a;
    for (int i = 0; i < num_moves; i++) {
        a = rotate(cube, rand() % (NUM_FACES * 2));
        moves[i] = a;
    }

    moves[num_moves] = '\0';
    return moves;
}

char* scrambleCube(Cube* cube, char* moves) {
    if (!moves) {
        perror("Error allocating memory for moves");
        return NULL;
    }

    if (strlen(moves) == 0) {
        return NULL;
    }

    int num_moves = strlen(moves);
    for (int i = 0; i < num_moves; i++) {
        switch (moves[i]) {
            case 'U':
                rotateUP(cube);
                break;
            case 'u':
                rotateR_UP(cube);
                break;
            case 'D':
                rotateDOWN(cube);
                break;
            case 'd':
                rotateR_DOWN(cube);
                break;
            case 'L':
                rotateLEFT(cube);
                break;
            case 'l':
                rotateR_LEFT(cube);
                break;
            case 'R':
                rotateRIGHT(cube);
                break;
            case 'r':
                rotateR_RIGHT(cube);
                break;
            case 'F':
                rotateFRONT(cube);
                break;
            case 'f':
                rotateR_FRONT(cube);
                break;
            case 'B':
                rotateBACK(cube);
                break;
            case 'b':
                rotateR_BACK(cube);
                break;
        }
    }
    return moves;
}

void freeCube(Cube* cube) {
    if (!cube) free(cube);
}