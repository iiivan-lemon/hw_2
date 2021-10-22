#include <gtest/gtest.h>
#include <cstdlib>
#include <random>

extern "C" {
#include "input_data.h"
}

#define SIZE_CONDITION 100000000
#define PATH "text.txt"

TEST(TestInputData1, RandomArraySize) {
    size_t size_test = rand() % SIZE_CONDITION + 1;
    EXPECT_TRUE(write_file(PATH, size_test) == EXIT_SUCCESS);
    EXPECT_TRUE(read_file(PATH,size_test) != nullptr);
    int *a = (int*) malloc(size_test*sizeof(int));
    size_t i = 0;
    FILE *f;
    f = fopen(PATH, "r");
    while(fscanf(f, "%d", &a[i]) > 0) {
        i++;
    }
    fclose(f);
    free(a);
    EXPECT_TRUE(i == size_test);

}


