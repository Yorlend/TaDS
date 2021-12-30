#ifndef __LIST_STACK_H__
#define __LIST_STACK_H__

#include "misc/types.h"
#include <stddef.h>
#include <stdbool.h>

#define UNBOUND 0       // Если стек, ограниченный только объемом оперативной памяти,
                        // то capacity = UNBOUND

typedef struct node
{
    struct node *prev;  // Предыдущий (нижний) элемент
    data_t value;       // Значение текущего элемента
} node_t;

typedef struct
{
    node_t *top;        // Верхний элемент стека
    size_t size;        // Количество элементов в стеке
    size_t capacity;    // Вместимость стека
} lstack_t;

// Пустой список
lstack_t lstack_empty(size_t capacity);

// Освобождение памяти
void lstack_destroy(lstack_t *stack);

// Проверка на пустоту
bool lstack_is_empty(const lstack_t *stack);

// Вставка элемента
int lstack_push(lstack_t *stack, data_t value);

// Удаление элемента
int lstack_pop(lstack_t *stack, data_t *value);

// Вывод стека и адресов
void lstack_print(const lstack_t *stack);

// Память, занимаемая стеком
size_t lstack_sizeof(const lstack_t *stack);

#endif /* __LIST_STACK_H__ */
