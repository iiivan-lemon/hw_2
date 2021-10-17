#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>
#include <stdio.h>
#include "input_data.h"
#include "prog.h"
#define PATH "hello.txt"
#define SIZE 10


int main(){

    if(write_file(PATH,SIZE) == EXIT_FAILURE){
        return EXIT_FAILURE;
    }

    int* a = read_file(PATH,SIZE);
    if(a == NULL){
        return EXIT_FAILURE;
    }
    res_coef* res;

    // последовательное решение - 1 поток
    res = linear_regress(a,SIZE);
    if(res == NULL){
        return EXIT_FAILURE;
    }
    printf("k = %f  b = %f",res->k,res->b);



    return 0;
}