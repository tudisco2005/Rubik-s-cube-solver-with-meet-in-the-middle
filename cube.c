#include "cube.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

Cube* initCube() {
    Cube* cube = NULL;

    if((cube = (Cube*)malloc(sizeof(Cube))) == NULL) {
        perror("Error allocating memory for cube");
        return NULL;
    }

    // initialize cube colors
    for(int i = 0; i < NUM_FACES; i++) {
        for(int j = 0; j < SIZE; j++) {
            for(int k = 0; k < SIZE; k++) {
                cube->color[i][j][k] = i;
            }
        }
    }

    return cube;
}

void rotateDOWN(Cube* cube) {
    int temp[SIZE][SIZE];

    // rotate the DOWN matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = cube->color[FACE_UP][SIZE-j-1][i]; 
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cube->color[FACE_UP][i][j] = temp[i][j];
        }
    }

    // Fix: We need to correctly handle the rotation of the top row of each adjacent face
    // Save the top row of each face
    int front_row[SIZE];
    int right_row[SIZE];
    int back_row[SIZE];
    int left_row[SIZE];

    // Store current values
    for (int i = 0; i < SIZE; i++) {
        front_row[i] = cube->color[FACE_FRONT][0][i];
        right_row[i] = cube->color[FACE_RIGHT][0][i];
        back_row[i] = cube->color[FACE_BACK][0][i];
        left_row[i] = cube->color[FACE_LEFT][0][i];
    }

    // Rotate the edges (FRONT → RIGHT → BACK → LEFT → FRONT)
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][0][i] = front_row[i];
        cube->color[FACE_BACK][0][i] = right_row[i];
        cube->color[FACE_LEFT][0][i] = back_row[i];
        cube->color[FACE_FRONT][0][i] = left_row[i];
    }
}

void rotateR_DOWN(Cube* cube) {
    int temp[SIZE][SIZE];

    // rotate the DOWN matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = cube->color[FACE_DOWN][j][SIZE-i-1]; 
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cube->color[FACE_DOWN][i][j] = temp[i][j];
        }
    }

    // Fix: We need to correctly handle the rotation of the top row of each adjacent face
    // Save the top row of each face
    int front_row[SIZE];
    int right_row[SIZE];
    int back_row[SIZE];
    int left_row[SIZE];

    // Store current values
    for (int i = 0; i < SIZE; i++) {
        front_row[i] = cube->color[FACE_FRONT][0][i];
        right_row[i] = cube->color[FACE_RIGHT][0][i];
        back_row[i] = cube->color[FACE_BACK][0][i];
        left_row[i] = cube->color[FACE_LEFT][0][i];
    }

    // Rotate the edges 
    for (int i = 0; i < SIZE; i++) {
        cube->color[FACE_RIGHT][0][i] = back_row[i];
        cube->color[FACE_BACK][0][i] = left_row[i];
        cube->color[FACE_LEFT][0][i] = front_row[i];
        cube->color[FACE_FRONT][0][i] = right_row[i];
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

void freeCube(Cube* cube) {
    if (!cube) free(cube);
}