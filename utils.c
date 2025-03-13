#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shift_array(int* arr, int size, int k) {
    int* temp = NULL;
    if((temp = (int*)malloc(sizeof(int) * size)) == NULL) {
        perror("Error allocating memory for temp array");
        return;
    }

    for (int i = 0; i < size; i++) {
        temp[(i + k) % size] = arr[i];
    }

    for (int i = 0; i < size; i++) {
        arr[i] = temp[i];
    }

    free(temp);
}

char *strdup(const char *c)
{
    char *dup = malloc(strlen(c) + 1);

    if (dup != NULL)
       strcpy(dup, c);

    return dup;
}

// Converti l'indice di un movimento in una stringa leggibile
char* getMoveString(int moveIdx) {
    static char* moveNames[] = {
        "F", "F'", "B", "B'", "U", "U'", 
        "D", "D'", "L", "L'", "R", "R'",
        "F2", "B2", "U2", "D2", "L2", "R2"
    };
    
    if (moveIdx >= 0 && moveIdx < 18) {
        return moveNames[moveIdx];
    } else {
        return "?";
    }
}