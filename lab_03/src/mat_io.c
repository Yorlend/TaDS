#include "misc/errors.h"
#include "mat_io.h"

int scan_stdmat(FILE* file, stdmat_t *mat)
{
    if (file == NULL || mat == NULL)
        return ARGS_ERR;

    id_t rows, cols;
    if (!(fscanf(file, "%u%u", &rows, &cols) == 2 && rows != 0 && cols != 0))
        return BAD_FILE;
    
    *mat = stdm_zero(rows, cols);
    if (!stdm_is_valid(mat))
        return MEM_ERR;
    
    int status = SUCCESS;
    for (id_t row = 0; row < rows && status == SUCCESS; row++)
        for (id_t col = 0; col < cols && status == SUCCESS; col++)
            if (fscanf(file, "%lf", &mat->data[row][col]) != 1)
                status = BAD_FILE;

    return status;
}

int print_stdmat(FILE* file, const stdmat_t *mat)
{
    if (file == NULL || mat == NULL)
        return ARGS_ERR;
    
    if (!stdm_is_valid(mat))
    {
        fprintf(file, "(null)\n");
        return MEM_ERR;
    }

    if (mat->cols >20 || mat->rows > 20)
        fprintf(file, "Матрица не будет выведена, так как размер превышает 20х20\n");
    else
    {
        for (id_t row = 0; row < mat->rows; row++)
        {
            for (id_t col = 0; col < mat->cols; col++)
                fprintf(file, "%8.1lf", mat->data[row][col]);
            fprintf(file, "\n");
        }
    }

    return SUCCESS;
}

int print_smat(FILE *file, const smatrix_t *mat)
{
    if (file == NULL || mat == NULL)
        return ARGS_ERR;
    
    if (!smat_is_valid(mat))
    {
        fprintf(file, "(null)\n");
        return MEM_ERR;
    }

    if (mat->cols >20 || mat->rows > 20)
        printf("Матрица не будет выведена, так как размер превышает 20х20\n");
    else
    {
        for (id_t row = 0; row < mat->rows; row++)
        {
            for (id_t col = 0; col < mat->cols; col++)
                fprintf(file, "%8.1lf", smat_get(mat, row, col));
            fprintf(file, "\n");
        }
    }

    return SUCCESS;
}

int print_smat_info(FILE *file, const smatrix_t *mat)
{
    if (file == NULL || mat == NULL)
        return ARGS_ERR;
    
    fprintf(file, "rows: %u, cols: %u, size: %u\n", mat->rows, mat->cols, mat->size);
    fprintf(file, "A: [");
    for (id_t i = 0; i < mat->size; i++)
        fprintf(file, "%6.1lf", mat->A[i]);
    fprintf(file, "]\nJA: [");
    for (id_t i = 0; i < mat->size; i++)
        fprintf(file, "%6u", mat->JA[i]);
    fprintf(file, "]\nIA: [");
    for (node_t *node = mat->IA.head; node != NULL; node = node->next)
        fprintf(file, "%3u", node->col_index);
    fprintf(file, "]\n");

    return SUCCESS;
}
