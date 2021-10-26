#include "prog.h"
#include "input_data.h"
#include <stdio.h>
#include <malloc.h>
#include <stddef.h>

res_coef *run_prog(int *a, const int size) {
    if (size == 0) {
        return NULL;
    }

    double Sx = 0;
    double Sy = 0;
    double Sxx = 0;
    double Sxy = 0;
    for (int i = 0; i < size; ++i) {
        Sx += i;
        Sy += a[i];
        Sxy += i * a[i];
        Sxx += i * i;
    }


    res_coef *res = (res_coef*)malloc(sizeof(res_coef));
    if (res == NULL) {
        return NULL;
    }
    res->k = (Sxy * size - Sx * Sy) / (Sxx * size - Sx * Sx);
    res->b = (Sy - res->k * Sx) / size;
    return res;
}

