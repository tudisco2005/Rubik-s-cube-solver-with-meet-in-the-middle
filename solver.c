#include "solver.h"
#include "cube.h"
#include "graphic.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int evalCube(Cube* cube) {
    int score = 0;
    int expected[NUM_FACES] = {COLOR_WHITE, COLOR_YELLOW, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_ORANGE};
    for (int i = 0; i < NUM_FACES; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (cube->color[i][j][k] == expected[i]) {
                    score++;
                }
            }
        }
    }
    return score;
}

Cube* copyCube(Cube* cube) {
    Cube* new_cube = NULL;
    if ((new_cube = (Cube*)malloc(sizeof(Cube))) == NULL) {
        perror("Error allocating memory for cube");
        return NULL;
    }

    for (int i = 0; i < NUM_FACES; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                new_cube->color[i][j][k] = cube->color[i][j][k];
            }
        }
    }

    return new_cube;
}

int compareCubes(Cube* cube1, Cube* cube2) {
    if (!cube1 || !cube2) return 0;

    // Compare each face of the cube
    // up face
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cube1->color[FACE_UP][i][j] != cube2->color[FACE_UP][i][j]) {
                return 0;
            }
        }
    }

    // down face
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cube1->color[FACE_DOWN][i][j] != cube2->color[FACE_DOWN][i][j]) {
                return 0;
            }
        }
    }

    // left face
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cube1->color[FACE_LEFT][i][j] != cube2->color[FACE_LEFT][i][j]) {
                return 0;
            }
        }
    }

    // right face
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cube1->color[FACE_RIGHT][i][j] != cube2->color[FACE_RIGHT][i][j]) {
                return 0;
            }
        }
    }

    // front face
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cube1->color[FACE_FRONT][i][j] != cube2->color[FACE_FRONT][i][j]) {
                return 0;
            }
        }
    }

    // back face
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cube1->color[FACE_BACK][i][j] != cube2->color[FACE_BACK][i][j]) {
                return 0;
            }
        }
    }

    // printf("same\n");
    // printf("1\n");
    // printCube(cube1);
    // printf("2\n");
    // printCube(cube2);

    return 1;
}

void freeGraph(Node** graph, long long size) {
    if (!graph) return;

    for (long long i = 0; i < size; i++) {
        if (graph[i]) {
            free(graph[i]->cube);
            free(graph[i]);
        }
    }

    free(graph);
}

char* reverseMoves(char* moves, int len) {
    char *solution = (char*)malloc(sizeof(char) * len + 1);
    if (!solution) {
        perror("Error allocating memory for solution");
        exit(1);
    }

    // Reverse the moves by converting to lowercase and then to uppercase
    for (int i = 0; i < len; i++) {
        if (isupper(moves[i])) {
            solution[i] = tolower(moves[i]);
        } else if (islower(moves[i])) {
            solution[i] = toupper(moves[i]);
        } else {
            solution[i] = moves[i];
        }
    }
    
    solution[len] = '\0';
    return solution;
}

int expandGraph(Node*** graph_ptr, long long size, int* curr_depth, int max_depth) {
    if (*curr_depth == max_depth) return size;

    Node** graph = *graph_ptr;
    
    // Count how many nodes are at the current depth to allocate proper memory
    int nodes_at_curr_depth = 0;
    for (int i = 0; i < size; i++) {
        if (graph[i]->depth == *curr_depth) {
            nodes_at_curr_depth++;
        }
    }
    
    printf("Found %d nodes at depth %d\n", nodes_at_curr_depth, *curr_depth);
    
    // Calculate the maximum possible new nodes
    long long max_new_nodes = nodes_at_curr_depth * NUM_MOVES;
    long long expected_total_size = size + max_new_nodes;
    
    // Reallocate memory for the graph
    Node** new_graph = (Node**)realloc(graph, sizeof(Node*) * expected_total_size);
    if (!new_graph) {
        perror("Error reallocating memory for graph");
        exit(1);
    }
    
    // Update the original pointer
    *graph_ptr = new_graph;
    graph = new_graph;

    // Create a temporary array to store all potential new nodes
    Node** potential_nodes = (Node**)malloc(sizeof(Node*) * max_new_nodes);
    if (!potential_nodes) {
        perror("Error allocating memory for potential nodes");
        exit(1);
    }
    
    long long potential_count = 0;

    // Generate all potential new nodes
    for (long long i = 0; i < size; i++) {
        if (graph[i]->depth != *curr_depth) {
            continue;
        }

        for (int j = 0; j < NUM_MOVES; j++) {
            Cube* new_cube = copyCube(graph[i]->cube);
            if (!new_cube) {
                perror("Error copying cube");
                exit(1);
            }

            char* move_str = rotate(new_cube, j);
            Node* new_node = (Node*)malloc(sizeof(Node));
            if (!new_node) {
                perror("Error allocating memory for new node");
                free(new_cube);
                free(move_str);
                exit(1);
            }

            new_node->cube = new_cube;
            new_node->move = move_str;
            new_node->parent = graph[i];
            new_node->depth = *curr_depth + 1;
            
            potential_nodes[potential_count++] = new_node;
        }
    }
    
    printf("Generated %lld potential nodes at depth %d\n", potential_count, *curr_depth + 1);
    
    // Now identify unique nodes
    int new_size = size;
    int duplicates_found = 0;
    
    for (long long i = 0; i < potential_count; i++) {
        if (potential_nodes[i] == NULL) continue; // Skip already marked duplicates
        
        Node* current = potential_nodes[i];
        int found = 0;
        
        // Check against existing nodes in the graph
        for (int j = 0; j < size; j++) {
            if (compareCubes(graph[j]->cube, current->cube)) {
                found = 1;
                break;
            }
        }
        
        // If not found in existing graph, check against already added potentials
        if (!found) {
            for (int j = 0; j < i; j++) {
                if (potential_nodes[j] != NULL && compareCubes(potential_nodes[j]->cube, current->cube)) {
                    found = 1;
                    break;
                }
            }
        }
        
        if (found) {
            // It's a duplicate, free the resources
            duplicates_found++;
            free(current->cube);
            free(current->move);
            free(current);
            potential_nodes[i] = NULL;
        } else {
            // Add to the graph
            graph[new_size++] = current;
        }
    }
    
    printf("Found %d duplicates, adding %lld unique nodes\n", 
           duplicates_found, (potential_count - duplicates_found));
    
    // Free the temporary array (but not the nodes themselves)
    free(potential_nodes);

    *curr_depth += 1;

    // realloc for the actual size
    Node** final_graph = (Node**)realloc(graph, sizeof(Node*) * new_size);
    if (!final_graph) {
        perror("Error reallocating memory for graph");
        exit(1);
    }
    
    // Update the original pointer again
    *graph_ptr = final_graph;
    
    return new_size;
}

void reverseTokens(const char *input, char *output) {
    char *tokens[1024];
    int count = 0;
    
    // Creiamo una copia della stringa input (perché strtok modifica la stringa)
    char *temp = strdup(input);
    if (temp == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }
    
    // Tokenizziamo la stringa usando lo spazio come delimitatore
    char *token = strtok(temp, " ");
    while (token != NULL && count < 1024) {
        tokens[count++] = token;
        token = strtok(NULL, " ");
    }
    
    // Costruiamo la stringa output concatenando i token in ordine inverso
    output[0] = '\0'; // Inizializza la stringa output vuota
    for (int i = count - 1; i >= 0; i--) {
        strcat(output, tokens[i]);
        if (i > 0) {
            strcat(output, " ");
        }
    }
    
    free(temp);
}

// Add helper function to recursively collect moves along the path
char* collectPath(Node* node) {
    if (node->parent == NULL) {
        return strdup("");
    }

    printf("\tdepth: %d move: %s\n", node->depth, node->move);

    char* parentPath = collectPath(node->parent);
    char* moveStr = (node->move) ? node->move : "";
    size_t newLen = strlen(parentPath) + strlen(moveStr) + 2; // +1 for space and +1 for '\0'
    char *result = (char*)malloc(newLen);
    if (!result) {
        perror("Error allocating memory for collected path");
        exit(1);
    }
    snprintf(result, newLen, "%s%s ", parentPath, moveStr);
    free(parentPath);
    
    return result;
}

// Improved Meet in the Middle algorithm implementation
// Improved Meet in the Middle algorithm implementation
char* meetInTheMiddle(Cube* starting, Cube* end, int max_depth) {
    if (max_depth == 0 || !starting || !end) return NULL;

    // arrays of cubes dynamically allocated
    Node** starting_graph = NULL;
    Node** end_graph = NULL;
    long long starting_size = 1;
    long long end_size = 1;
    int starting_depth = 0;
    int end_depth = 0;

    // adding the starting cube to the graph
    starting_graph = (Node**)malloc(sizeof(Node*) * starting_size);
    if (!starting_graph) {
        perror("Error allocating memory for starting graph");
        return NULL;
    }

    starting_graph[0] = (Node*)malloc(sizeof(Node));
    if (!starting_graph[0]) {
        perror("Error allocating memory for starting node");
        free(starting_graph);
        return NULL;
    }
    starting_graph[0]->cube = copyCube(starting);
    starting_graph[0]->parent = NULL;
    starting_graph[0]->depth = 0;
    starting_graph[0]->move = NULL; // starting cube not moved

    // adding the end cube to the graph
    end_graph = (Node**)malloc(sizeof(Node*) * end_size);
    if (!end_graph) {
        perror("Error allocating memory for end graph");
        freeGraph(starting_graph, starting_size);
        return NULL;
    }

    end_graph[0] = (Node*)malloc(sizeof(Node));
    if (!end_graph[0]) {
        perror("Error allocating memory for end node");
        freeGraph(starting_graph, starting_size);
        free(end_graph);
        return NULL;
    }
    end_graph[0]->cube = copyCube(end);
    end_graph[0]->parent = NULL;
    end_graph[0]->depth = 0;
    end_graph[0]->move = NULL; // end cube not moved

    // Check if start and end cubes are the same
    if (compareCubes(starting, end)) {
        freeGraph(starting_graph, starting_size);
        freeGraph(end_graph, end_size);
        return strdup("");
    }

    // Start the bidirectional search
    while (starting_depth < max_depth && end_depth < max_depth) {
        // Check for matches before expanding
        printf("---- Checking for matches before expanding ---\n");
        for (int j = 0; j < starting_size; j++) {
            for (int k = 0; k < end_size; k++) {
                if (compareCubes(starting_graph[j]->cube, end_graph[k]->cube)) {
                    printf("\n[+] Match found at depths %d and %d\n", 
                           starting_graph[j]->depth, end_graph[k]->depth);
                    
                    // Collect the path from the starting (forward) search
                    printf("Collecting path from start\n");
                    char* pathForward = collectPath(starting_graph[j]);
                    
                    // Collect the path from end
                    printf("Collecting path from end\n");
                    char* pathEnd = collectPath(end_graph[k]);
                    
                    // We need to reverse the moves in the end path
                    // First, create a properly formatted string
                    size_t pathEndLen = strlen(pathEnd);
                    char* formattedPathEnd = (char*)malloc(pathEndLen + 1);
                    if (!formattedPathEnd) {
                        perror("Error allocating memory for formatted path");
                        free(pathForward);
                        free(pathEnd);
                        freeGraph(starting_graph, starting_size);
                        freeGraph(end_graph, end_size);
                        return NULL;
                    }
                    
                    // Create reversed moves
                    reverseTokens(pathEnd, formattedPathEnd);
                    
                    // Now invert each move (uppercase to lowercase and vice versa)
                    char* invertedEnd = reverseMoves(formattedPathEnd, strlen(formattedPathEnd));
                    free(pathEnd);
                    free(formattedPathEnd);

                    // Combine the paths
                    size_t finalLen = strlen(pathForward) + strlen(invertedEnd) + 1;
                    char* finalSolution = (char*)malloc(finalLen);
                    if (!finalSolution) {
                        perror("Error allocating memory for final solution");
                        free(pathForward);
                        free(invertedEnd);
                        freeGraph(starting_graph, starting_size);
                        freeGraph(end_graph, end_size);
                        return NULL;
                    }
                    
                    // Concatenate the paths
                    strcpy(finalSolution, pathForward);
                    strcat(finalSolution, invertedEnd);
                    
                    free(pathForward);
                    free(invertedEnd);
                    
                    freeGraph(starting_graph, starting_size);
                    freeGraph(end_graph, end_size);
                    return finalSolution;
                }
            }
        }

        // Expand forward from the starting cube
        if (starting_depth <= end_depth) {
            printf("\n---------- start (%d) ----------\n", starting_depth);
            starting_size = expandGraph(&starting_graph, starting_size, &starting_depth, max_depth);
            
            // Check for matches after expanding the starting graph
            printf("---- Checking for matches after expanding start ---\n");
            for (long long j = 0; j < starting_size; j++) {
                for (long long k = 0; k < end_size; k++) {
                    if (compareCubes(starting_graph[j]->cube, end_graph[k]->cube)) {
                        printf("\n[+] Match found at depths %d and %d\n", 
                               starting_graph[j]->depth, end_graph[k]->depth);
                        
                        // Collect path as before
                        printf("Collecting path from start\n");
                        char* pathForward = collectPath(starting_graph[j]);
                        printf("Collecting path from end\n");
                        char* pathEnd = collectPath(end_graph[k]);
                        
                        // Format and reverse the end path
                        char* formattedPathEnd = (char*)malloc(strlen(pathEnd) + 1);
                        if (!formattedPathEnd) {
                            perror("Error allocating memory");
                            free(pathForward);
                            free(pathEnd);
                            freeGraph(starting_graph, starting_size);
                            freeGraph(end_graph, end_size);
                            return NULL;
                        }
                        
                        reverseTokens(pathEnd, formattedPathEnd);
                        char* invertedEnd = reverseMoves(formattedPathEnd, strlen(formattedPathEnd));
                        free(pathEnd);
                        free(formattedPathEnd);

                        // Combine paths
                        size_t finalLen = strlen(pathForward) + strlen(invertedEnd) + 1;
                        char* finalSolution = (char*)malloc(finalLen);
                        if (!finalSolution) {
                            perror("Error allocating memory for final solution");
                            free(pathForward);
                            free(invertedEnd);
                            freeGraph(starting_graph, starting_size);
                            freeGraph(end_graph, end_size);
                            return NULL;
                        }
                        
                        strcpy(finalSolution, pathForward);
                        strcat(finalSolution, invertedEnd);
                        
                        free(pathForward);
                        free(invertedEnd);
                        
                        freeGraph(starting_graph, starting_size);
                        freeGraph(end_graph, end_size);
                        return finalSolution;
                    }
                }
            }
        }
        
        // Expand backward from the end cube
        if (end_depth <= starting_depth) {
            printf("\n---------- end (%d) ----------\n", end_depth);
            end_size = expandGraph(&end_graph, end_size, &end_depth, max_depth);
            
            // Check for matches after expanding the end graph
            printf("---- Checking for matches after expanding end ---\n");
            for (int j = 0; j < starting_size; j++) {
                for (int k = 0; k < end_size; k++) {
                    if (compareCubes(starting_graph[j]->cube, end_graph[k]->cube)) {
                        printf("\n[+] Match found at depths %d and %d\n", 
                               starting_graph[j]->depth, end_graph[k]->depth);
                        
                        // Collect path as before
                        printf("Collecting path from start\n");
                        char* pathForward = collectPath(starting_graph[j]);
                        printf("Collecting path from end\n");
                        char* pathEnd = collectPath(end_graph[k]);
                        
                        // Format and reverse the end path
                        char* formattedPathEnd = (char*)malloc(strlen(pathEnd) + 1);
                        if (!formattedPathEnd) {
                            perror("Error allocating memory");
                            free(pathForward);
                            free(pathEnd);
                            freeGraph(starting_graph, starting_size);
                            freeGraph(end_graph, end_size);
                            return NULL;
                        }
                        
                        reverseTokens(pathEnd, formattedPathEnd);
                        char* invertedEnd = reverseMoves(formattedPathEnd, strlen(formattedPathEnd));
                        free(pathEnd);
                        free(formattedPathEnd);

                        // Combine paths
                        size_t finalLen = strlen(pathForward) + strlen(invertedEnd) + 1;
                        char* finalSolution = (char*)malloc(finalLen);
                        if (!finalSolution) {
                            perror("Error allocating memory for final solution");
                            free(pathForward);
                            free(invertedEnd);
                            freeGraph(starting_graph, starting_size);
                            freeGraph(end_graph, end_size);
                            return NULL;
                        }
                        
                        strcpy(finalSolution, pathForward);
                        strcat(finalSolution, invertedEnd);
                        
                        free(pathForward);
                        free(invertedEnd);
                        
                        freeGraph(starting_graph, starting_size);
                        freeGraph(end_graph, end_size);
                        return finalSolution;
                    }
                }
            }
        }
    }

    // Clean up and return no solution found
    freeGraph(starting_graph, starting_size);
    freeGraph(end_graph, end_size);
    return NULL;
}
