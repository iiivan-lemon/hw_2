#include <gtest/gtest.h>
#include <cstdlib>
#include <random>

extern "C" {
#include "input_data.h"
}

#define SIZE_CONDITION 100
#define PATH "text.txt"

TEST(TestInputData, RandomArraySize) {
    size_t size_test = SIZE_CONDITION;

    EXPECT_TRUE(write_file(PATH, size_test) == EXIT_SUCCESS);
    int *a = read_file(PATH, size_test);
    EXPECT_TRUE(a != nullptr);

    size_t i = 0;
    FILE *f;
    f = fopen(PATH, "r");
    while (fscanf(f, "%d", &a[i]) > 0) {
        i++;
    }
    fclose(f);
    free(a);
    EXPECT_TRUE(i == size_test);
}


