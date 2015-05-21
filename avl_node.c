#include "avl_node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int height(struct avl_node *node) {
    return node == NULL ? 0 : node->height;
}

struct avl_node *new_avl_node(char *string) {
    struct avl_node *node = malloc(sizeof(struct avl_node));

    if (node == NULL) {
        return NULL;
    }

    memcpy(node->string, string, MAX_STRING_LENGTH);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

struct avl_node *right_rotate(struct avl_node *y) {
    struct avl_node *x = y->left;
    struct avl_node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct avl_node *left_rotate(struct avl_node *x) {
    struct avl_node *y = x->right;
    struct avl_node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int get_balance(struct avl_node *node) {
    return node == NULL ? 0 : height(node->left) - height(node->right);
}

struct avl_node *insert(struct avl_node *node, char *string) {
    // 1. perform normal BST rotation

    if (node == NULL) {
        return new_avl_node(string);
    }

    int cmp = strcmp(string, node->string);

    if (cmp == 0) {
        return node;
    }
    else if (cmp < 0) {
        node->left = insert(node->left, string);
    }
    else {
        node->right = insert(node->right, string);
    }

    // 2. update height of this ancestor node

    node->height = max(height(node->left), height(node->right)) + 1;

    // 3. get the balance factor of this ancestor node to check if it became unbalanced

    int balance = get_balance(node);

    // if it became unbalanced, there are 4 cases

    // left-left

    if (balance > 1 && strcmp(string, node->left->string) < 0) {
        return right_rotate(node);
    }

    // right-right

    if (balance < -1 && strcmp(string, node->right->string) > 0) {
        return left_rotate(node);
    }
    
    // left-right
    
    if (balance > 1 && strcmp(string, node->left->string) > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // right-left
    
    if (balance < -1 && strcmp(string, node->right->string) < 0) {
        node->right = right_rotate(node);
        return left_rotate(node);
    }

    // return the unchanged node
    return node;
}

void preorder_traversal(struct avl_node *root) {
    if (root != NULL) {
        printf("%s\n", root->string);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

bool word_exists(struct avl_node *root, char *word) {
    if (root == NULL) {
        return false;
    }

    int comparison = strcmp(word, root->string);
    bool retval = false; 

    if (comparison == 0) {
        retval = true;
    }
    else if (comparison < 0) {
        retval = word_exists(root->left, word);
    }
    else {
        retval = word_exists(root->right, word);
    }

    return retval;
}
