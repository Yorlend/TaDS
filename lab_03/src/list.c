#include "misc/list.h"
#include "misc/errors.h"
#include <stddef.h>

int init_lst(list_t* list, unsigned int size)
{
    list->head = NULL;

    for (unsigned int i = 0; i < size; i++)
    {
        node_t* curr = malloc(sizeof(node_t));

        if (curr == NULL)
        {
            printf("Ошибка выделения памяти!\n");
            return MEM_ERR;
        }

        curr->next = list->head;
        curr->col_index = -1;

        list->head = curr;
    }

    return SUCCESS;
}

void free_lst(list_t* list)
{
    node_t *curr, *tmp;
    curr = list->head;

    while (curr->next != NULL)
    {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }

    free(tmp);
}
