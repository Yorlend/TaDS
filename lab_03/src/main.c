#include <stdio.h>
#include "misc/errors.h"
#include "convert_mat.h"
#include "operations.h"
#include "mat_io.h"

int main(int argc, const char **argv)
{
    int status = SUCCESS;

    stdmat_t mat = stdm_zero(50, 70);
    stdm_randomize(&mat, 90);

    stdmat_t vec = stdm_zero(1, 50);
    stdm_randomize(&vec, 50);

    stdmat_t res = stdm_null();

    double time_std;
    double time_spa;
    bool correct;
    if (test_mul(&correct, &time_std, &time_spa, &res, &vec, &mat) != SUCCESS)
        printf("test not success.\n");
    else
    {
        printf("correct: %d\n", correct);
        printf("time std: %lf\n", time_std);
        printf("time spa: %lf\n", time_spa);
    }

    FILE* file = fopen("data.csv", "w");
    run_tests(file, 10, 10, 100, 10, 200);
    fclose(file);

    return status;
}
