#ifndef __AVL_H__
#define __AVL_H__

#include "misc/types.h"
#include <stdint.h>


typedef struct avl_node
{
    data_t key;
    uint8_t height;

    struct node *left;
    struct node *right;
} node_t;

/**
 * @brief Выделяет память под узел дерева
 * 
 * @param key значение узла
 * @return node_t* (указатель на выделенную область памяти)
 */
node_t *node_init(data_t key);

/**
 * @brief Обёртка поля height, которая может работать с нулевыми указателями
 * 
 * @param node узел дерева
 * @return uint8_t (высота поддерева)
 */
uint8_t height(node_t *node);

/**
 * @brief Вычисление показателя балансировки узла
 * 
 * @param node узел дерева, балансировка которого вычисляется
 * @return int (показатель балансировки узла)
 */
int bfactor(node_t *node);

/**
 * @brief Восстанавливает корректное значения поля height
 * 
 * @param node узел, высота которого исправляется
 */
void fix_height(node_t *node);

/**
 * @brief Правый поворот вокруг узла
 * 
 * @param node корень поддерева
 * @return node* (новый корень полученного дерева)
 */
node_t *rotate_right(node_t *node);

/**
 * @brief Левый поворот вокруг узла
 * 
 * @param node корень поддерева
 * @return node_t* (новый корень полученного дерева)
 */
node_t *rotate_left(node_t *node);

/**
 * @brief Балансировка вокруг узла
 * 
 * @param node узел дерева
 * @return node_t* (корень отбалансированного дерева)
 */
node_t *balance(node_t *node);

/**
 * @brief Вставить значение в дерево, сохранив балансировку
 * 
 * @param root корень дерева
 * @param key значение узла
 * @return node_t* (корень сбалансированного дерева)
 */
node_t *insert(node_t *root, data_t key);

#endif /* __AVL_H__ */
