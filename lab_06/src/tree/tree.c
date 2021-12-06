#include "tree/tree.h"
#include <stdlib.h>
#include <stdio.h>


// вставка без сохранения сбалансированности 
static node_t *__insert(node_t *root, data_t key)
{
    if (root == NULL)
        return node_init(key);
    if (key < root->key)
    {
        node_t *tmp = __insert(root->left, key);

        if (tmp == NULL)
            return tmp;
        
        root->left = tmp;
        tmp = NULL;
    }
    else if (key > root->key)
    {
        node_t *tmp = __insert(root->right, key);        
    
        if (tmp == NULL)
            return tmp;
        
        root->right = tmp;
        tmp = NULL;
    }

    fix_height(root);
    return root;
}

static node_t *__input_bst(FILE *file)
{
    node_t *node = NULL;

    data_t tmp;

    while (fscanf(file, "%d", &tmp) == 1)
    {
        node_t *root = __insert(node, tmp);

        if (root == NULL)
        {
            bst_destroy(node);
            return NULL;
        }

        node = root;
    }

    if (feof(file))
        return node;

    bst_destroy(node);
    return NULL;
}

node_t *bst_input(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
        return NULL;

    node_t *res = __input_bst(file);

    fclose(file);
    return res;
}

static void __to_dot(const node_t *root, FILE *file)
{
    static int nullcount = 0;

    if (root->left != NULL)
    {
        fprintf(file, "    %d.%d -> %d.%d;\n", root->key, root->height, root->left->key, root->left->height);
        __to_dot(root->left, file);
    }
    else
    {
        fprintf(file, "    null%d [shape=point];\n", nullcount);
        fprintf(file, "    %d.%d -> null%d;\n", root->key, root->height, nullcount);
        nullcount++;
    }
    
    if (root->right != NULL)
    {
        fprintf(file, "    %d.%d -> %d.%d;\n", root->key, root->height, root->right->key, root->right->height);
        __to_dot(root->right, file);
    }
    else
    {
        fprintf(file, "    null%d [shape=point];\n", nullcount);
        fprintf(file, "    %d.%d -> null%d;\n", root->key, root->height, nullcount);
        nullcount++;
    }
}

void bst_output(const node_t *root, const char *graphname)
{
    char buffer[256];

    snprintf(buffer, 256, "%s.dot", graphname);
    FILE* file = fopen(buffer, "w");

    fprintf(file, "digraph g {\n");
    __to_dot(root, file);    
    fprintf(file, "}\n");

    fclose(file);

    snprintf(buffer, 256, "dot -Tpng -o%s.png %s.dot", graphname, graphname);
    system(buffer);
}

const node_t *bst_search(const node_t *root, data_t key, size_t *cmp_count)
{
    if (root == NULL)
        return NULL;

    (*cmp_count)++;

    if (root->key == key)
        return root;
    else if (root->key > key)
        return bst_search(root->left, key, cmp_count);
    else
        return bst_search(root->right, key, cmp_count);
}

static node_t *find_min(node_t *node)
{
    return node->left ? find_min(node->left) : node;
}

static node_t *remove_min(node_t *node)
{
    if (node->left == NULL)
        return node->right;
    node->left = remove_min(node->left);
    return balance(node);
}

node_t *bst_remove(node_t *root, data_t key, size_t *cmp_count)
{
    if (root == NULL)
        return NULL;
    
    (*cmp_count)++;
    if (key < root->key)
        root->left = bst_remove(root->left, key, cmp_count);
    else if (key > root->key)
        root->right = bst_remove(root->right, key, cmp_count);
    else
    {
        node_t *left = root->left;
        node_t *right = root->right;
        free(root);
        if (right == NULL)
            return left;
        node_t *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        
        return min;
    }

    return root;
}

double bst_mean_search_cmp_count(const node_t *root)
{
    if (root == NULL)
        return 0;
    
    double left = bst_mean_search_cmp_count(root->left);
    double right = bst_mean_search_cmp_count(root->right);
    return 2 + 0.5 * (left + right);
}

void bst_destroy(node_t *root)
{
    if (root != NULL)
    {
        bst_destroy(root->left);
        bst_destroy(root->right);
        free(root);
    }
}

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

static node_t *rotate_right(node_t *node)
{
    node_t *root = node->left;
    node->left = root->right;
    root->right = node;

    fix_height(node);
    fix_height(root);

    return root;
}

static node_t *rotate_left(node_t *node)
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

    if (bfactor(node) > 1)
    {
        if (bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    if (bfactor(node) < -1)
    {
        if (bfactor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    return node;
}

// dest - avl, source - bst
static node_t *__bst_to_avl(node_t *dest, node_t *source)
{
    if (source != NULL)
    {
        dest = avl_insert(dest, source->key);
        dest = __bst_to_avl(dest, source->left);
        dest = __bst_to_avl(dest, source->right);
    }
    
    return dest;
}

node_t *bst_to_avl(node_t *node)
{
    return __bst_to_avl(NULL, node);
}

node_t *avl_insert(node_t *root, data_t key)
{
    if (root == NULL)
        return node_init(key);
    if (key < root->key)
        root->left = avl_insert(root->left, key);
    else
        root->right = avl_insert(root->right, key);

    return balance(root);
}

node_t *avl_remove(node_t *root, data_t key, size_t *cmp_count)
{
    if (root == NULL)
        return NULL;
    
    (*cmp_count)++;
    if (key < root->key)
        root->left = avl_remove(root->left, key, cmp_count);
    else if (key > root->key)
        root->right = avl_remove(root->right, key, cmp_count);
    else
    {
        node_t *left = root->left;
        node_t *right = root->right;
        free(root);
        if (right == NULL)
            return left;
        node_t *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        
        return balance(min);
    }

    return balance(root);
}
