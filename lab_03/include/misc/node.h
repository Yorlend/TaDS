#ifndef __NODE_H__
#define __NODE_H__

typedef struct node_t node_t;

struct node_t
{
    unsigned int col_index;     // индекс столбца
    node_t* next;               // следующий элемент
};


#endif /* __NODE_H__ */
