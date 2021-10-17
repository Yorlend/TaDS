#ifndef __LIST_H__
#define __LIST_H__


#include "node.h"

typedef struct list
{
    node_t* head;   // указатель на голову
} list_t;


// Инициализация связного списка
int init_lst(list_t* list, unsigned int size);

// Освобождение памяти, занимаемой связным списком
void free_lst(list_t* list);

// Печать списка
void lst_print(const list_t* list);

#endif /* __LIST_H__ */
