#include "tree/avl.h"
#include <stdlib.h>


node_t *node_init(data_t key)
{
    node_t *node = malloc(sizeof(node_t));

    if (node != NULL)
    {
        node->key = key;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

uint8_t height(node_t *node)
{
    return node ? node->height : 0;
}

int bfactor(node_t *node)
{
    return height(node->right) - height(node->left);
}

void fix_height(node_t *node)
{
    uint8_t h_left = height(node->left);
    uint8_t h_right = height(node->right);

    node->height = (h_left > h_right ? h_left : h_right) + 1;
}

node_t *rotate_right(node_t *node)
{
    node_t *root = node->left;
    node->left = root->right;
    root->right = node;

    fix_height(node);
    fix_height(root);

    return root;
}

node_t *rotate_left(node_t *node)
{
    node_t *root = node->right;
    node->right = root->left;
    root->left = node;

    fix_height(node);
    fix_height(root);

    return root;
}

node_t *balance(node_t *node)
{
    fix_height(node);

    if (bfactor(node) == 2)
    {
        if (bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    if (bfactor(node) == -2)
    {
        if (bfactor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    return node;
}

node_t *insert(node_t *root, data_t key)
{
    /// TODO: implement
}
