#include "tree/tree.h"
#include "misc/errors.h"
#include "misc/timer.h"
#include <stdio.h>

int main()
{
    node_t *tree = bst_input("test.txt");

    bst_output(tree, "bst");

    node_t *avl = bst_to_avl(tree);

    bst_output(avl, "avl");

    size_t cmp_count = 0;

    TIMER_BEGIN;
    
    bst_remove(tree, 100, &cmp_count);
    
    TIMER_END;

    printf("delete time BST: %llu, comparisons: %zu\n", TIMER_TICKS, cmp_count);

    cmp_count = 0;
    
    TIMER_BEGIN;

    avl_remove(avl, 100, &cmp_count);

    TIMER_END;

    printf("delete time AVL: %llu, comparisons: %zu\n", TIMER_TICKS, cmp_count);

    bst_output(tree, "bst_removed");
    bst_output(avl, "avl_removed");

    bst_destroy(tree);
    bst_destroy(avl);
    return SUCCESS;
}
