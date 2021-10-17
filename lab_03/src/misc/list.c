#include <stdlib.h>
#include <stdbool.h>
#include "misc/errors.h"
#include "misc/list.h"

list_t lst_empty(void)
{
    list_t lst;

    lst.head = NULL;

    return lst;
}

void lst_destroy(list_t* list)
{
    if (list == NULL)
        return;

    while (list->head != NULL)
    {
        node_t *next = list->head->next;
        free(list->head);
        list->head = next;
    }
}

list_t lst_reserve(id_t size, id_t value)
{
    list_t lst = lst_empty();
    bool valid = true;

    while (size-- > 0)
    {
        node_t *node = malloc(sizeof(node_t));
        valid = node != NULL;
        if (!valid)
            break;
        node->next = lst.head;
        node->col_index = value;
        lst.head = node;
    }

    if (!valid)
        lst_destroy(&lst);

    return lst;
}

id_t lst_get(const list_t* list, id_t index)
{
    if (list != NULL)
    {
        node_t* node = list->head;
        while (node != NULL && index-- > 0)
            node = node->next;
        
        if (node != NULL)
            return node->col_index;
    }

    return 0;
}

void lst_set(list_t* list, id_t index, id_t value)
{
    if (list != NULL)
    {
        node_t* node = list->head;
        while (node != NULL && index-- > 0)
            node = node->next;
        
        if (node != NULL)
            node->col_index = value;
    }
}

size_t lst_calc_mem(const list_t *lst)
{
    size_t size = sizeof(list_t);

    for (node_t *node = lst.head; node != NULL; node = node->next)
        size += sizeof(node_t);

    return size;
}
