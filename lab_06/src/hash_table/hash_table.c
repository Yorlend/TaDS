#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "misc/errors.h"
#include "hash_table/hash_table.h"

#define MAX(a, b) ((a) < (b) ? (b) : (a))

hash_table_t hash_null(void)
{
    hash_table_t table;

    table.size = 0;
    table.step = 0;
    table.data = NULL;
    table.func = NULL;

    return table;
}

hash_table_t hash_init(size_t size, size_t step, hf_t func)
{
    hash_table_t table = hash_null();

    if (size > 0 && step > 0 && func != NULL)
    {
        table.data = calloc(size, sizeof(hash_data_t));
        if (table.data != NULL)
        {
            table.size = size;
            table.step = step;
            table.func = func;
        }
    }

    return table;
}

void hash_destroy(hash_table_t *table)
{
    if (table->data != NULL)
    {
        free(table->data);
        *table = hash_null();
    }
}

static bool __table_initialized(const hash_table_t *table)
{
    return table->size > 0 && table->data != NULL && table->func != NULL;
}

static int __hash_input(hash_table_t *table, size_t size, FILE *file)
{
    rewind(file);
    int status = SUCCESS;

    assert(size != 0);

    *table = hash_init(size, DEFAULT_STEP, DEFAULT_FUNC);
    assert(__table_initialized(table));

    int tmp;
    while (status == SUCCESS && fscanf(file, "%d", &tmp) == 1)
        status = hash_insert(table, tmp);

    if (!feof(file))
        status = INP_ERR;
    
    return status;
}

int hash_input(hash_table_t *table, size_t size, const char *filename)
{
    FILE *file = fopen(filename, "r");
    int status = SUCCESS;

    if (file == NULL)
        status = INP_ERR;
    else
    {
        status = __hash_input(table, size, file);
        fclose(file);
    }

    return status;
}

void hash_output(const hash_table_t *table)
{
    assert(__table_initialized(table));

    printf("Хеш-таблица:\n");
    printf("+-----+-------+-----+\n");
    printf("|  i  | value | cmp |\n");
    printf("+-----+-------+-----+\n");

    for (size_t i = 0; i < table->size; i++)
    {
        hash_data_t data = table->data[i];
        if (data.has_value)
            printf("| %3ld | %5d | %3zu |\n", i, data.key, data.cmp_count);
        else
            printf("| %3ld |       | %3zu |\n", i, data.cmp_count);
    }

    printf("+-----+-------+-----+\n");
    // printf("Максимальное число сравнений: %zu\n", hash_get_max_cmp_count(table));
}

bool hash_find(hash_table_t *table, data_t data)
{
    assert(__table_initialized(table));

    size_t index = table->func(data, table->size) % table->size;
    hash_data_t tdata = table->data[index];

    while (tdata.has_value && tdata.key != data)
    {
        index = (index + table->step) % table->size;
        tdata = table->data[index];
    }

    return tdata.key == data && tdata.has_value;
}

int hash_insert(hash_table_t *table, data_t data)
{
    assert(__table_initialized(table));

    size_t index = table->func(data, table->size) % table->size;
    hash_data_t tdata = table->data[index];
    size_t increments = 0;

    while (tdata.has_value && tdata.key != data && increments < table->size)
    {
        index = (index + table->step) % table->size;
        tdata = table->data[index];
        increments++;
    }

    if (tdata.key == data)
        return SUCCESS;

    if (!tdata.has_value)
    {
        tdata.key = data;
        tdata.has_value = true;
        tdata.cmp_count = increments + 1;
        table->data[index] = tdata;
        return SUCCESS;
    }

    return MEM_ERR;
}

int hash_remove(hash_table_t *table, data_t data, size_t *cmp_count)
{
    assert(__table_initialized(table));

    size_t index = table->func(data, table->size) % table->size;
    hash_data_t tdata = table->data[index];
    size_t increments = 0;

    while (tdata.key != data && increments < table->size)
    {
        index = (index + table->step) % table->size;
        tdata = table->data[index];
        increments++;
    }

    *cmp_count = increments + 1;

    if (tdata.has_value && tdata.key == data)
    {
        tdata.has_value = false;
        tdata.cmp_count = increments + 1;
        table->data[index] = tdata;
        return SUCCESS;
    }

    return NO_ELEM;
}

double hash_get_mean_cmp_count(const hash_table_t *table)
{
    size_t cmps = 0;
    size_t count = 0;

    for (size_t i = 0; i < table->size; i++)
    {
        hash_data_t data = table->data[i];
        if (data.has_value)
        {
            cmps += data.cmp_count;
            count++;
        }
    }

    return count == 0 ? 0 : (double)cmps / count;
}

size_t hash_get_max_cmp_count(const hash_table_t *table)
{
    size_t max = 0;

    for (size_t i = 0; i < table->size; i++)
    {
        hash_data_t data = table->data[i];
        if (data.has_value)
            max = MAX(max, data.cmp_count);
    }

    return max;
}

size_t hash_sizeof(const hash_table_t *table)
{
    return sizeof(hash_table_t) + table->size * sizeof(hash_data_t);
}

int hash_restruct(hash_table_t *table)
{
    hash_data_t *old_data = table->data;
    table->data = calloc(table->size, sizeof(hash_data_t));
    assert(table->data != NULL);

    table->func = hasher2;

    for (size_t i = 0; i < table->size; i++)
        if (old_data[i].has_value)
            hash_insert(table, old_data[i].key);

    free(old_data);
    return SUCCESS;
}

size_t hasher1(data_t data, size_t table_size)
{
    return data % table_size;
}

size_t hasher2(data_t data, size_t table_size)
{
    const double phi = 0.6180339887;

    double AK_w = phi * data;
    double frac = AK_w - floor(AK_w);

    return frac * table_size;
}
