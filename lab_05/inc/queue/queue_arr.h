#ifndef __QUEUE_ARR_H__
#define __QUEUE_ARR_H__

#include "utils/types.h"
#include <stdint.h>


typedef struct
{
    uint32_t size;      // Размер очереди
    uint32_t capacity;  // Вместимость очереди
    request_t *begin;   // Начало массива, выделенного под очередь
    request_t *first;   // "Хвост" очереди
    request_t *last;    // "Голова" очереди
} qarr_t;

// Выделение памяти под пустую очередь
qarr_t qarr_create(uint32_t size);

// Очищение памяти под очередь
void qarr_destroy(qarr_t *queue);

// Вставка элемента в "хвост" очереди
int qarr_push_back(qarr_t *queue, request_t value);

// Вставка элемента в очередь
int qarr_insert(qarr_t *queue, uint32_t pos, request_t value);

// Удаление элемента из "головы" очереди
int qarr_pop_front(qarr_t *queue, request_t *value);

// Печать очереди на экран
void qarr_print(const qarr_t *queue);

#endif /* __QUEUE_ARR_H__ */
