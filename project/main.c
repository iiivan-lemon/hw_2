#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>
#include <stdio.h>
#include "input_data.h"
#include "prog.h"


#include <time.h>
#define CONVERT_TO_SEC 1000000000.0
#define PATH "hello.txt"
#define SIZE_CONDITION 100
int main() {


    if (write_file(PATH, SIZE_CONDITION) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int *a = read_file(PATH, SIZE_CONDITION);
    if (a == NULL) {
        return EXIT_FAILURE;
    }

    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);

    res_coef *res = run_prog(a, SIZE_CONDITION);
    //res_coef *res = run_prog_parallel(a, size);
    //int* pa = a;
    free(a);

    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed = (double)(finish.tv_sec - start.tv_sec);
    elapsed += (double) (finish.tv_nsec - start.tv_nsec) / CONVERT_TO_SEC;

    printf("%lf\n", elapsed);
    if (res == NULL) {
        return EXIT_FAILURE;
    }
    printf("k = %f  b = %f\n", res->k, res->b);
    free(res);

    return 0;
}
