#ifndef __BIN_TREE_H__
#define __BIN_TREE_H__

#include "misc/types.h"


typedef struct leaf
{
    data_t value;

    leaf_t *left;
    leaf_t *right;
} leaf_t;

typedef struct
{
    leaf_t *root;
} bin_tree_t;

/**
 * @brief Создает пустую структуру дерева
 * 
 * @return bin_tree_t (указатель на нулевой корень)
 */
bin_tree_t bst_init(void);

/**
 * @brief Инициализирует узел дерева по значению
 * 
 * @param value значение узла
 * @return leaf_t (результирующий узел)
 */
leaf_t leaf_init(data_t value);



#endif /* __BIN_TREE_H__ */
