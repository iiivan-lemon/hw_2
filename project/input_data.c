#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "input_data.h"


int write_file(const char *path, int size) {
    if (size < 1) {
        return EXIT_FAILURE;
    }
    FILE *f;
    f = fopen(path, "w+");
    if (!f) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(f, "%d ", i);
    }
    fclose(f);
    return EXIT_SUCCESS;
}

int *read_file(const char *path, int size) {
    if (size < 1) {
        return NULL;
    }
    int *a = (int *) malloc(size * sizeof(int));

    if (a == NULL) {
        return NULL;
    }
    FILE *f;
    f = fopen(path, "r");
    if (!f) {
        free(a);
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        if (fscanf(f, "%d", &a[i]) != 1) {
            fclose(f);
            return NULL;
        }
    }
    fclose(f);

    return a;
}

