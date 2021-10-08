#include "keytable.h"
#include "studtable.h"
#include <stdlib.h>


status_t init_keytable(keytable_t* kt)
{
    if (kt == NULL)
        return FUNC_ARGS_ERROR;

    kt->data = NULL;
    kt->size = 0;

    return SUCCESS;
}

status_t update_keytable(keytable_t* kt, const studtable_t* st)
{
    if (!stable_valid(st))
        return FUNC_ARGS_ERROR;

    if (kt->size != st->size)
    {
        _key_t* newdata = realloc(kt->data, st->size * sizeof(_key_t));

        if (newdata != NULL)
        {
            kt->data = newdata;
            kt->size = st->size;
        }

        else
            return MEMORY_ERROR;
    }

    for (size_t i = 0; i < st->size; i++)
        kt->data[i] = stud_to_key(st->data + i, i);

    return SUCCESS;
}

static void _key_row_print(_key_t key)
{
    printf("\033[32;40m│%4lu│ %5.2lf │\033[0m\n", key.id, key.avg);
}

void print_keytable(const keytable_t* kt)
{
    if (kt != NULL)
    {
        printf("\033[32;40m╒═id═╤═score═╕\033[0m\n");

        for (size_t i = 0; i < kt->size; i++)
            _key_row_print(kt->data[i]);

        printf("\033[32;40m└────┴───────┘\033[0m\n");
    }
}

static int score_cmp(const void* a, const void* b)
{
    double score_1 = ((_key_t*)a)->avg;
    double score_2 = ((_key_t*)b)->avg;

    if (score_1 < score_2)
        return -1;
    else if (score_1 > score_2)
        return 1;
    return 0;
}

void keytable_sort(keytable_t* kt, sort_t sort_fn)
{
    if (kt != NULL)
        sort_fn(kt->data, kt->size, sizeof(_key_t), score_cmp);
}

void keytable_destroy(keytable_t* kt)
{
    if (kt->data != NULL)
    {
        free(kt->data);
        kt->size = 0;
        kt->data = NULL;
    }
}
