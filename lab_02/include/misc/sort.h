#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>


// Тип: указатель на функцию компаратор
typedef int (*compare_t)(const void*, const void*);

// Тип: указатель на функцию сортировки
typedef void (*sort_t)(void*, size_t, size_t, compare_t);

// Сортировка выбором
void selection_sort(void* base, size_t nitems, size_t size, compare_t cmp);

// Сортировка слиянием
void merge_sort(void* base, size_t nitems, size_t size, compare_t cmp);

// Выводит объем затрачиваемой на сортировку выбором памяти
size_t selection_mem(size_t N, size_t size);

// Выводит объем затрачиваемой на сортировку слиянием памяти
size_t merge_mem(size_t N, size_t size);

#endif /* __SORT_H__ */
