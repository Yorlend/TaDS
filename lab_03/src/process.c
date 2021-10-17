#include <stdio.h>
#include "misc/errors.h"
#include "operations.h"
#include "process.h"
#include "mat_io.h"

int input_mat_dims(id_t *rows, id_t *cols)
{
    printf("Введите кол-во строк матрицы: ");

    if (scanf("%u", rows) != 1)
    {
        printf("Некоректный ввод.\n");
        return INP_ERR;
    }
    
    if (*rows == 0)
    {
        printf("Некорректное кол-во строк.\n");
        return INP_ERR;
    }

    printf("Введите кол-во столбцов матрицы: ");

    if (scanf("%u", cols) != 1)
    {
        printf("Некорректный ввод.\n");
        return INP_ERR;
    }

    if (*cols == 0)
    {
        printf("Некорректное кол-во столбцов.\n");
        return INP_ERR;
    }
    
    return SUCCESS;
}

int input_vec(stdmat_t *vec, id_t cols)
{
    *vec = stdm_zero(1, cols);
    if (!stdm_is_valid(vec))
    {
        printf("Возникла ошибка при выделении памяти.\n");
        return MEM_ERR;
    }

    printf("Ввод элементов вектор-строки.\n");

    printf("Вводите пары чисел (<№ столбца> <элемент>).\n");
    printf("По окончании ввода введите 0 0:\n");

    while (true)
    {
        id_t index;
        data_t value;
        if (scanf("%u%lf", &index, &value) != 2)
        {
            printf("Некорректный ввод.\n");
            return INP_ERR;
        }
        index -= 1;
        if (value == 0)
            break;
        else if (index < cols)
            vec->data[0][index] = value;
        else
        {
            printf("Номер столбца выходит за допустимые границы.\n");
            printf("Не вставилось.\n");
        }
    }

    return SUCCESS;
}

int input_mat(stdmat_t *mat, id_t rows, id_t cols)
{
    *mat = stdm_zero(rows, cols);
    if (!stdm_is_valid(mat))
    {
        printf("Возникла ошибка при выделении памяти.\n");
        return MEM_ERR;
    }

    printf("Ввод элементов матрицы.\n");

    printf("Вводите тройки чисел (<№ строки> <№ столбца> <элемент>).\n");
    printf("По окончании ввода введите 0 0 0:\n");

    while (true)
    {
        id_t row, col;
        data_t value;
        if (scanf("%u%u%lf", &row, &col, &value) != 3)
        {
            printf("Некорректный ввод.\n");
            return INP_ERR;
        }
        row -= 1;
        col -= 1;
        if (value == 0)
            break;
        else if (row < rows && col < cols)
            mat->data[row][col] = value;
        else
        {
            printf("Номер столбца и/или номер строки выходит за допустимые границы.\n");
            printf("Не вставилось.\n");
        }
    }

    return SUCCESS;
}

static size_t _smat_calc_mem(const stdmat_t *mat)
{
    smatrix_t smat = smat_null();
    size_t size = smat_calc_mem(&smat);
    smat_destroy(&smat);
    return size;
}

int test_matrices(const stdmat_t *vec, const stdmat_t *mat)
{
    double time_std, time_spa;
    stdmat_t res = stdm_null();

    printf("Производим умножение...\n");

    int status = test_mul(NULL, &time_std, &time_spa, &res, vec, mat);

    printf("Результат умножения:\n\n");
    print_stdmat(stdout, &res);

    printf("\nВремя обычного умножения:     %.0lf нс\n", time_std);
    printf("Время специального умножения: %.0lf нс\n", time_spa);

    printf("\nЗатраченная память под хранение:\n");
    printf("В плотном представлении: %zu байт\n", stdm_calc_mem(vec) + stdm_calc_mem(vec));
    printf("В разреженном виде:      %zu байт\n", _smat_calc_mem(vec) + _smat_calc_mem(vec));

    stdm_destroy(&res);

    return status;
}

int do_auto_tests(const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file != NULL)
    {
        run_tests(file, 50, 50, 500, 10, 50);
        fclose(file);
        return SUCCESS;
    }

    return BAD_FILE;
}
