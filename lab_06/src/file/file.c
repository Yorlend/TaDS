#include <stdio.h>
#include "misc/errors.h"
#include "misc/types.h"
#include "misc/timer.h"
#include "file/file.h"


static size_t __count_nums(FILE *file)
{
    size_t counter = 0;
    int tmp = 0;

    rewind(file);
    while (fscanf(file, "%d", &tmp) == 1)
        counter++;

    return counter;
} 

static int __f_read(FILE *file, data_t *data, size_t size)
{
    rewind(file);

    for (size_t i = 0; i < size; i++)
        fscanf(file, "%d", data + i);

    return SUCCESS;
}

static int __f_get_data(const char *filename, data_t **array, size_t *size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return INP_ERR;
    
    *size = __count_nums(file);
    *array = malloc(*size * sizeof(data_t));
    int status = MEM_ERR;
    if (*array != NULL)
        status = __f_read(file, *array, *size);

    fclose(file);
    return status;
}

static int __f_set_data(const char *filename, data_t *array, size_t size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
        return INP_ERR;

    for (size_t i = 0; i < size; i++)
        fprintf(file, "%d\n", array[i]);

    fclose(file);
    return SUCCESS;
}

double f_get_mean_cmp_count(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 0;
    
    double res = __count_nums(file);
    fclose(file);
    return 0.5 * (res + 1);
}

size_t f_sizeof(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 0;
    
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fclose(file);
    return size;
}

int f_remove(const char *filename, data_t value, size_t *cmp_count)
{
    data_t *array = NULL;
    size_t size = 0;

    int status = __f_get_data(filename, &array, &size);
    if (status != SUCCESS)
        return status;

    size_t index = 0;
    while (index < size && array[index] != value)
        index++;

    for (size_t i = index; i + 1 < size; i++)
        array[i] = array[i + 1];
    size--;

    *cmp_count = index + 1;
    status = __f_set_data(filename, array, size);

    free(array);
    return status;
}
