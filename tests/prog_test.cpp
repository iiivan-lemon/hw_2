#include <gtest/gtest.h>

#include <cstdlib>
#include <random>

extern "C" {
#include "prog.h"

}

#define STRESS_ITERATION_NUMBER 10
#define SIZE_CONDITION 100000000

TEST(TestConsistent1, Bisector) {
    int *a = (int *) malloc(SIZE_CONDITION * sizeof(int));
    for (int i = 0; i < SIZE_CONDITION; ++i) {
        a[i] = i;
    }
    res_coef expect_res;
    expect_res.k = 1;
    expect_res.b = 0;
    res_coef *res = run_prog(a, SIZE_CONDITION);
    EXPECT_TRUE(res->k == expect_res.k);
    EXPECT_TRUE(res->b == expect_res.b);
    free(res);
    free(a);
}

