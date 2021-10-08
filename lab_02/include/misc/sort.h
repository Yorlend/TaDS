#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>


typedef int (*compare_t)(const void*, const void*);
typedef void (*sort_t)(void*, size_t, size_t, compare_t);

void selection_sort(void* base, size_t nitems, size_t size, compare_t cmp);
void merge_sort(void* base, size_t nitems, size_t size, compare_t cmp);

#endif /* __SORT_H__ */
