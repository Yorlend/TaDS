#include "misc/sort.h"
#include <string.h>


// Обменивает значение двух элементов
static void swap(void* a, void* b, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        *((char*)a + i) ^= *((char*)b + i);
        *((char*)b + i) ^= *((char*)a + i);
        *((char*)a + i) ^= *((char*)b + i);
    }
}

// Находит индекс минимального элемента массива
static size_t min_index(const void* base, size_t nitems, size_t size, compare_t cmp)
{
    size_t res = 0;
    const void* min_el = base;

    for (size_t i = 1; i < nitems; i++)
    {
        const void* elem = (const char*)base + i * size;
        if (cmp(elem, min_el) < 0)
        {
            min_el = elem;
            res = i;
        }
    }

    return res;
}

void selection_sort(void* base, size_t nitems, size_t size, compare_t cmp)
{
    for (size_t i = 0; i < nitems; i++)
    {
        size_t min_i = min_index((char*)base + i * size, nitems - i, size, cmp);
        if (min_i != 0)
            swap((char*)base + i * size, (char*)base + (i + min_i) * size, size);
    }
}


// Сливает два отсортированных массива воедино, сохраняя упорядоченность
static void merge(void* base, size_t size, size_t mid, size_t right, compare_t cmp) 
{
    char tmp[size * mid];
    memmove(tmp, base, size * mid);

    size_t i = 0, j = mid;
    for (size_t k = 0; k < right; k++)
    {
        if (j == right || (i < mid && cmp(tmp + i * size, (char*)base + j * size) < 0))
        {
            memmove((char*)base + k * size, tmp + i * size, size);
            i++;
        }
        else
        {
            memmove((char*)base + k * size, (char*)base + j * size, size);
            j++;
        }
    }
}

void merge_sort(void* base, size_t nitems, size_t size, compare_t cmp)
{
    if (nitems < 2)
        return;
    
    if (nitems == 2)
    {
        if (cmp(base, (char*)base + size) > 0)
            swap(base, (char*)base + size, size);
        return;
    }

    size_t mid = nitems >> 1;

    merge_sort(base, mid, size, cmp);
    merge_sort((char*)base + mid * size, nitems - mid, size, cmp);
    merge(base, size, mid, nitems, cmp);
}

size_t selection_mem(size_t N, size_t size)
{
    return N * size;
}

size_t merge_mem(size_t N, size_t size)
{
    size_t m = 0;
    while (N > 2)
    {
        m += N;
        N = (N + 1) / 2;
    }
    m += N;

    return m * size;
}
