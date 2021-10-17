#ifndef __NODE_H__
#define __NODE_H__

#include "misc/types.h"

typedef struct node
{
    id_t col_index;    // индекс столбца
    struct node* next; // следующий элемент
} node_t;

#endif /* __NODE_H__ */
