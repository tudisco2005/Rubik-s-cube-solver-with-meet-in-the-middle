#include "cube.h"
#include "utils.h"
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
void rotateFaceClockwise(Cube* cube, Face face) {
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
void rotateFaceCounterClockwise(Cube* cube, Face face) {
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

void rotateUP_2(Cube* cube) {
    rotateUP(cube);
    rotateUP(cube);
}

void rotateDOWN_2(Cube* cube) {
    rotateDOWN(cube);
    rotateDOWN(cube);
}

void rotateLEFT_2(Cube* cube) {
    rotateLEFT(cube);
    rotateLEFT(cube);
}

void rotateRIGHT_2(Cube* cube) {
    rotateRIGHT(cube);
    rotateRIGHT(cube);
}

void rotateFRONT_2(Cube* cube) {
    rotateFRONT(cube);
    rotateFRONT(cube);
}

void rotateBACK_2(Cube* cube) {
    rotateBACK(cube);
    rotateBACK(cube);
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
    
    // LEFT -> UP(with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][i][2] = temp[SIZE-i-1];
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
    
    // LEFT -> UP(with reversion)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_LEFT][i][0] = temp[SIZE-1-i];
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
char* rotate(Cube* cube, Move move) {
    char* a;
    a = (char*) malloc(3 * sizeof(char));
    if (!a) {
        perror("Error allocating memory for move");
        return NULL;
    }

    switch (move) {
        case MOVE_UP:
            rotateUP(cube);
            strcpy(a, "U");
            break;
        case MOVE_R_UP:
            rotateR_UP(cube);
            strcpy(a, "u");
            break;
        case MOVE_2_UP:
            rotateUP_2(cube);
            strcpy(a, "U2");
            break;
        case MOVE_DOWN:
            rotateDOWN(cube);
            strcpy(a, "D");
            break;
        case MOVE_R_DOWN:
            rotateR_DOWN(cube);
            strcpy(a, "d");
            break;
        case MOVE_2_DOWN:
            rotateDOWN_2(cube);
            strcpy(a, "D2");
            break;
        case MOVE_LEFT:
            rotateLEFT(cube);
            strcpy(a, "L");
            break;
        case MOVE_R_LEFT:
            rotateR_LEFT(cube);
            strcpy(a, "l");
            break;
        case MOVE_2_LEFT:
            rotateLEFT_2(cube);
            strcpy(a, "L2");
            break;
        case MOVE_RIGHT:
            rotateRIGHT(cube);
            strcpy(a, "R");
            break;
        case MOVE_R_RIGHT:
            rotateR_RIGHT(cube);
            strcpy(a, "r");
            break;
        case MOVE_2_RIGHT:
            rotateRIGHT_2(cube);
            strcpy(a, "R2");
            break;
        case MOVE_FRONT:
            rotateFRONT(cube);
            strcpy(a, "F");
            break;
        case MOVE_R_FRONT:
            rotateR_FRONT(cube);
            strcpy(a, "f");
            break;
        case MOVE_2_FRONT:
            rotateFRONT_2(cube);
            strcpy(a, "F2");
            break;
        case MOVE_BACK:
            rotateBACK(cube);
            strcpy(a, "B");
            break;
        case MOVE_R_BACK:
            rotateR_BACK(cube);
            strcpy(a, "b");
            break;
        case MOVE_2_BACK:
            rotateBACK_2(cube);
            strcpy(a, "B2");
            break;
        default:
            strcpy(a, "!");
            break;
    }

    return a;
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

    char* a;
    for (int i = 0; i < num_moves; i++) {
        a = rotate(cube, rand() % (NUM_MOVES));
        strcat(moves,a);
    }

    moves[num_moves] = '\0';
    return moves;
}

char* scrambleCube(Cube* cube, char* moves) {
    if (!moves || strlen(moves) == 0) {
        return NULL;
    }

    char *moves_copy = strdup(moves); // Duplicate string to avoid modifying original
    if (!moves_copy) {
        perror("Error allocating memory for move copy");
        return NULL;
    }

    char *tokens[1024];
    int index = 0;

    // Split the moves string into tokens
    char *token = strtok(moves_copy, " ");
    while (token && index < 1024) {
        tokens[index++] = token;
        token = strtok(NULL, " ");
    }

    // Process moves
    for (int i = 0; i < index; i++) {
        int move = -1;
        if (strcmp(tokens[i], "U") == 0) {
            move = MOVE_UP;
        } else if (strcmp(tokens[i], "u") == 0) {
            move = MOVE_R_UP;
        } else if (strcmp(tokens[i], "U2") == 0 || strcmp(tokens[i], "u2") == 0) {
            move = MOVE_2_UP;
        } else if (strcmp(tokens[i], "D") == 0) {
            move = MOVE_DOWN;
        } else if (strcmp(tokens[i], "d") == 0) {
            move = MOVE_R_DOWN;
        } else if (strcmp(tokens[i], "D2") == 0 || strcmp(tokens[i], "d2") == 0) {
            move = MOVE_2_DOWN;
        } else if (strcmp(tokens[i], "L") == 0) {
            move = MOVE_LEFT;
        } else if (strcmp(tokens[i], "l") == 0) {
            move = MOVE_R_LEFT;
        } else if (strcmp(tokens[i], "L2") == 0 || strcmp(tokens[i], "l2") == 0) {
            move = MOVE_2_LEFT;
        } else if (strcmp(tokens[i], "R") == 0) {
            move = MOVE_RIGHT;
        } else if (strcmp(tokens[i], "r") == 0) {
            move = MOVE_R_RIGHT;
        } else if (strcmp(tokens[i], "R2") == 0 || strcmp(tokens[i], "r2") == 0) {
            move = MOVE_2_RIGHT;
        } else if (strcmp(tokens[i], "F") == 0) {
            move = MOVE_FRONT;
        } else if (strcmp(tokens[i], "f") == 0) {
            move = MOVE_R_FRONT;
        } else if (strcmp(tokens[i], "F2") == 0 || strcmp(tokens[i], "f2") == 0) {
            move = MOVE_2_FRONT;
        } else if (strcmp(tokens[i], "B") == 0) {
            move = MOVE_BACK;
        } else if (strcmp(tokens[i], "b") == 0) {
            move = MOVE_R_BACK;
        } else if (strcmp(tokens[i], "B2") == 0 || strcmp(tokens[i], "b2") == 0) {
            move = MOVE_2_BACK;
        } else {
            fprintf(stderr, "Invalid move: %s\n", tokens[i]);
            free(moves_copy);
            return NULL;
        }

        rotate(cube, move);
    }

    free(moves_copy);
    return strdup(moves);  // Return a new copy of the moves string
}

void freeCube(Cube* cube) {
    if (!cube) free(cube);
}