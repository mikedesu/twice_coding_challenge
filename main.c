#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>

#include "avl_node.h"

#define BUFFER_SIZE 32

struct avl_node *word_tree = NULL;

// substring function
char *substr(char *s, int begin, int len);

// swap two characters in place
void swap(char *x, char *y);

// compute permutations of string, and check to see if each permutation is a word in our avl tree
void check_permutations(struct avl_node *root, char *string, int i, int n);

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("usage: %s <input_dictionary_file> <input_word>\n", argv[0]);
        exit(-1);
    }

    // argv[1] = our input dictionary file
    // argv[2] = our input word

    // read in our dictionary and construct the tree
    
    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        printf("There was an error reading the file: %s\nError: %s", argv[1], strerror(errno));
        exit(-1);
    }

    struct avl_node *root = NULL;

    while (!feof(in_file)) {
        char buffer[BUFFER_SIZE];
        if ( fgets(buffer, BUFFER_SIZE, in_file) != NULL ) {
            size_t len = strlen(buffer);
            buffer[len-1] = '\0';
            buffer[len-2] = '\0';
            root = insert(root, buffer);
        }
    }

    fclose(in_file);

    // read in our word and check the permutations for words in our dictionary
    // we will also pass in another avl_tree to store the words we find

    char *word = argv[2];
    int len = strlen(word);
    
    check_permutations(root, word, 0, len);
    
    // print out the unique words we found
    preorder_traversal(word_tree);

    return 0;
}

char *substr(char *s, int begin, int len) {
    assert(begin >= 0 && len > 0 && begin + len <= strlen(s));

    char *buffer = malloc(sizeof(char) * len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    memcpy(buffer, s+begin, len);

    return buffer;
}

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void check_permutations(struct avl_node *root, char *string, int i, int n) {
    if (i == n && strcmp(string, "") != 0 && word_exists(root, string)) {
        word_tree = insert(word_tree, string);
    }
    else {
        for (int j = i; j <= n; j++) {
            swap((string+i), (string+j));
            check_permutations(root, string, i+1, n);
            swap((string+i), (string+j));
        }
    }
}

