#ifndef __LIST_H__
#define __LIST_H__

#include "misc/types.h"
#include "node.h"


typedef struct list
{
    node_t* head;   // указатель на голову
} list_t;

list_t lst_empty(void);

// Освобождение памяти, занимаемой связным списком
void lst_destroy(list_t* list);

// возвращает список с неинициализированными элементами
list_t lst_reserve(id_t size, id_t value);

id_t lst_get(const list_t* list, id_t index);

void lst_set(list_t* list, id_t index, id_t value);

// Печать списка
// void lst_print(const list_t* list);

#endif /* __LIST_H__ */
