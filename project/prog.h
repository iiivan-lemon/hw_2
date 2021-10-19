#ifndef HW_2_PROG_H
#define HW_2_PROG_H
#include <stdio.h>
#include <string.h>

struct res_coefficients{
    double k;
    double b;
};
typedef struct res_coefficients res_coef;

res_coef* linear_regress( int*,int );

#endif     //   HW_2_PROG_H
