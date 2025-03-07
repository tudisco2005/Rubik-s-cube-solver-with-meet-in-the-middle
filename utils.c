#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

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