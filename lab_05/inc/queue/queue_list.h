#ifndef __QUEUE_LIST_H__
#define __QUEUE_LIST_H__

#include "utils/types.h"
#include <stdint.h>


typedef struct node
{
    request_t data;     // Запрос ОА
    struct node *next;  // Следующий узел
} node_t;


typedef struct
{
    uint32_t size;  // Размер очереди
    node_t *first;  // "Хвост" очереди
    node_t *last;   // "Голова" очереди
} qlist_t;


// Создание пустой очереди
qlist_t qlist_create(void);

// Очищение памяти под очередь
void qlist_destroy(qlist_t *queue);

// Вставка элемента в "хвост" очереди
int qlist_push_back(qlist_t *queue, request_t value);

// Вставка элемента в очередь
int qlist_insert(qlist_t *queue, uint32_t pos, request_t value);

// Удаление элемента из "головы" очереди
int qlist_pop_front(qlist_t *queue, request_t *value);

// Печать очереди на экран
void qlist_print(const qlist_t *queue);

#endif /* __QUEUE_LIST_H__ */
