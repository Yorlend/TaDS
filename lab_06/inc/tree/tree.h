#ifndef __TREE_H__
#define __TREE_H__

#include "misc/types.h"
#include <stdint.h>
#include <stddef.h>


typedef struct avl_node
{
    data_t key;
    uint8_t height;

    struct avl_node *left;
    struct avl_node *right;
} node_t;

// ================================================================================
// ДДП
// ================================================================================

/**
 * @brief Ввод бинарного дерева поиска (не сбалансированного)
 * 
 * @param filename имя файла, содержащего целые числа
 * @return node_t* (указатель на корень дерева)
 */
node_t *bst_input(const char *filename);

/**
 * @brief Вывод бинарного дерева поиска в графическом виде
 * 
 * @param root корень ДДП
 */
void bst_output(const node_t *root, const char *graphname);

/**
 * @brief Освобождение памяти из-под бинарного дерева
 * 
 * @param root корень ДДП 
 */
void bst_destroy(node_t *root);

/**
 * @brief Поиск элемента в ДДП
 * 
 * @param root корень ДДП
 * @param key искомый элемент
 * @return node_t* (искомый узел)
 */
const node_t *bst_search(const node_t *root, data_t key, size_t *cmp_count);

/**
 * @brief Удаление элемента из дДП
 * 
 * @param root корень ДДП
 * @param key удаляемый элемент
 * @return node_t* (искомый узел)
 */
node_t *bst_remove(node_t *root, data_t key, size_t *cmp_count);

double bst_mean_search_cmp_count(const node_t *root);

/**
 * @brief Преобразование ДДП в АВЛ-дерево
 * 
 * @param node узел дерева
 * @return node_t* (корень сбалансированного АВЛ дерева)
 */
node_t *bst_to_avl(node_t *node);

// ====================================================================================
// АВЛ-деревья
// ====================================================================================

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
 * @brief Балансировка при вставке в отбалансированное дерево
 * 
 * @param node узел дерева
 * @return node_t* (корень сбалансированного дерева)
 */
node_t *balance(node_t *node);

/**
 * @brief Вставить значение в дерево, сохранив балансировку
 * 
 * @param root корень дерева
 * @param key значение узла
 * @return node_t* (корень сбалансированного дерева)
 */
node_t *avl_insert(node_t *root, data_t key);

/**
 * @brief Удаления ключа key из данного дерева
 * 
 * @param root корень дерева
 * @param key ключ, подлежащий удалению
 * @param[out] cmp_count количество сравнений
 * @return node_t* (указатель на новое дерево)
 */
node_t *avl_remove(node_t *root, data_t key, size_t *cmp_count);

#endif /* __TREE_H__ */
