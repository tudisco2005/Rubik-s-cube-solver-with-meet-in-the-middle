#ifndef SOLVER_H
#define SOLVER_H

#include "cube.h"

#define MAX_DEPTH 20 // Maximum depth of the search tree (god numbers)

typedef struct Node {
    Cube* cube;
    struct Node* parent;
    int depth;
    char* move;
} Node;


int evalCube(Cube* cube);
Cube* copyCube(Cube* cube);
int compareCubes(Cube* cube1, Cube* cube2);
void freeGraph(Node** graph, long long size);
int expandGraph(Node*** graph, long long size, int* curr_depth, int max_depth);
char* meetInTheMiddle(Cube* starting, Cube* end, int max_depth);
char* reverseMoves(char* moves, int len);
void reverseTokens(const char *input, char *output);
char* checkForMatch(Node* start_node, Node* end_node);

#endif