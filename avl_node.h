#ifndef AVL_NODE_H
#define AVL_NODE_H

#include <stdbool.h>

#define MAX_STRING_LENGTH 32
#define max(a, b) ((a > b) ? a : b)

struct avl_node {
    char string[MAX_STRING_LENGTH];
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

int height(struct avl_node *node);
struct avl_node *new_avl_node(char *string);
struct avl_node *right_rotate(struct avl_node *y);
struct avl_node *left_rotate(struct avl_node *x);
int get_balance(struct avl_node *node);
struct avl_node *insert(struct avl_node *node, char *string);

void preorder_traversal(struct avl_node *root);
bool word_exists(struct avl_node *root, char *word);

#endif
