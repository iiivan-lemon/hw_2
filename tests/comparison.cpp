#include <gtest/gtest.h>
#include <cstdlib>
#include <random>


TEST(Comparision1, Results) {
    FILE *f_consistent = fopen("../data/consistent_res.txt", "r");
    FILE *f_parallel = fopen("../data/parallel_res.txt", "r");
    double res_consistent = 0;
    double res_parallel = 0;
    for (int i = 0; i < 2; ++i) {
        if (fscanf(f_consistent, "%lf", &res_consistent) != 1) {
            fclose(f_consistent);
        }
        if (fscanf(f_parallel, "%lf", &res_parallel) != 1) {
            fclose(f_parallel);
        }
        EXPECT_EQ(res_parallel, res_consistent);
    }
    fclose(f_parallel);
    fclose(f_consistent);
}

TEST(Comparision2, Time) {
    FILE *f_consistent = fopen("../data/consistent_time.txt", "r");
    FILE *f_parallel = fopen("../data/parallel_time.txt", "r");
    double time_consistent = 0;
    double time_parallel = 0;

    fscanf(f_consistent, "%lf", &time_consistent);
    fscanf(f_parallel, "%lf", &time_parallel);
    printf("Consistent: %lf\n", time_consistent);
    printf("Parallel: %lf\n", time_parallel);
    fclose(f_parallel);
    fclose(f_consistent);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
