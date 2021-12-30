#ifndef __ARRAY_STACK_H__
#define __ARRAY_STACK_H__

#include <stddef.h>
#include <stdbool.h>
#include "misc/types.h"

typedef struct
{
    data_t *data;       // Указатель на область памяти
    data_t *top_low;    // Указатель на верхний элемент нижнего стека
    data_t *top_high;   // Указатель на верхний элемент верхнего стека
    size_t data_size;   // Размер массива
} astack_t;

// Непроинициализированный стек
astack_t astack_null(void);

// Пустой стек
astack_t astack_empty(size_t size);

// Освобождение памяти
void astack_destroy(astack_t *stack);

// Проверка на корректность
bool astack_is_valid(const astack_t *stack);

// Вставка в нижний (первый) стек
int astack_push_low(astack_t *stack, data_t value);

// Вставка в верхний (второй) стек
int astack_push_high(astack_t *stack, data_t value);

// Удаление из нижнего (первого) стека
int astack_pop_low(astack_t *stack, data_t *value);

// Удаление из верхнего (второго) стека
int astack_pop_high(astack_t *stack, data_t *value);

// Вывод нижнего (первого) стека
void astack_low_print(const astack_t *stack);

// Вывод верхнего (второго) стека
void astack_high_print(const astack_t *stack);

// Вывод используемой стеком памяти
size_t astack_sizeof(const astack_t *stack);

#endif /* __ARRAY_STACK_H__ */
