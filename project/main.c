#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>
#include <stdio.h>
#include "input_data.h"
#include "prog.h"


#include <time.h>

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

    res_coef *res = run_prog(a, SIZE_CONDITION);
    free(a);

    if (res == NULL) {
        return EXIT_FAILURE;
    }
    printf("k = %f  b = %f\n", res->k, res->b);
    free(res);

    return 0;
}

