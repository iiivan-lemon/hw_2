#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>
#include <stdio.h>
#include "input_data.h"
#include "prog.h"


#include <time.h>

#define PATH "hello.txt"
#define CONVERT_TO_SEC 1000000000.0


int main() {

    int size = 0;
    printf("enter size of input data: ");
    if (scanf("%d", &size) != 1) {
        return EXIT_FAILURE;
    }
    if (write_file(PATH, size) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int *a = read_file(PATH, size);
    if (a == NULL) {
        return EXIT_FAILURE;
    }
    res_coef *res;
    struct timespec start, finish;

    clock_gettime(CLOCK_MONOTONIC, &start);
    // последовательное решение - 1 поток
    res = linear_regress(a, size);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed = (double) (finish.tv_sec - start.tv_sec);
    elapsed += (double) (finish.tv_nsec - start.tv_nsec) / CONVERT_TO_SEC;

    printf("%lf\n", elapsed);
    if (res == NULL) {
        return EXIT_FAILURE;
    }
    printf("k = %f  b = %f\n", res->k, res->b);


    return 0;
}
