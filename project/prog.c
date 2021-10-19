#include "prog.h"
#include "input_data.h"
#include <stdio.h>
#include <malloc.h>
#include <stddef.h>

res_coef *linear_regress( int *a, const int size) {
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
    Sx /= size;
    Sy /= size;
    Sxy /= size;
    Sxx /= size;

    res_coef *res = malloc(sizeof(res_coef));
    if(res == NULL){
        return NULL;
    }
    res->k = (Sx * Sy - Sxy) / (Sx * Sx - Sxx);
    res->b = (Sxy - res->k * Sxx) / Sx;
    return res;

}
