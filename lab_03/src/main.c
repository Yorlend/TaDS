#include "misc/errors.h"
#include "process.h"

int main(int argc, const char **argv)
{
    if (argc == 2)
        return do_auto_tests(argv[1]);

    id_t rows = 0, cols = 0;
    stdmat_t mat = stdm_null();
    stdmat_t vec = stdm_null();

    int status = input_mat_dims(&rows, &cols);

    if (status == SUCCESS)
        status = input_vec(&vec, rows);

    if (status == SUCCESS)
        status = input_mat(&mat, rows, cols);

    if (status == SUCCESS)
        status = test_matrices(&vec, &mat);

    stdm_destroy(&mat);
    stdm_destroy(&vec);

    return status;
}
