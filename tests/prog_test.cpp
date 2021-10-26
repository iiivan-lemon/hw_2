#include <gtest/gtest.h>

#include <cstdlib>
#include <random>

#define PATH "text.txt"
extern "C" {
#include "prog.h"
#include "input_data.h"
}

#define STRESS_ITERATION_NUMBER 10
#define SIZE_CONDITION 100

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

TEST(TestConsistent2, RandomElems) {
    EXPECT_TRUE(write_file(PATH, SIZE_CONDITION) == EXIT_SUCCESS);
    int *a = read_file(PATH, SIZE_CONDITION);
    EXPECT_TRUE(a != nullptr);
    res_coef *res = run_prog(a, SIZE_CONDITION);
    FILE *f = fopen("../data/consistent_res.txt", "w+");
    EXPECT_FALSE(f == nullptr);
    fprintf(f, "%f %f", res->k, res->b);
    fclose(f);
    free(res);
    free(a);
}

TEST(time, time) {
    double general_time = 0;
    double average_time;

    size_t times = 10;
    int *a = read_file(PATH, SIZE_CONDITION);
    for (size_t i = 0; i < times; ++i) {
        double timer = clock();
        res_coef *res = run_prog(a, SIZE_CONDITION);
        timer = clock() - timer;
        general_time += timer;
        free(res);
    }
    average_time = general_time / times / CLOCKS_PER_SEC;
    FILE *f = fopen("../data/consistent_time.txt", "w+");
    fprintf(f, "%lf", average_time);
    fclose(f);
    free(a);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
