#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conservativegc.h"

typedef struct tree tree;

struct tree {
    int num;
    tree* left;
    tree* right;
};

tree* tree_new(int num, tree* l, tree* r) {
    tree* result = (struct tree*)malloc(sizeof(tree));

    if (result) {
        result->num = num;
        result->left = l;
        result->right = r;
    }

    return result;
}

void tree_traverse(tree* t) {
    if (t) {
        printf("%d\n", t->num);
        tree_traverse(t->left);
        tree_traverse(t->right);
    }
}

void create_test_tree(tree** result) {
    *result = tree_new(1, NULL, NULL);
    (*result)->left = tree_new(2, NULL, NULL);
    (*result)->left->left = tree_new(3, NULL, NULL);
    (*result)->left->right = tree_new(4, NULL, NULL);
    (*result)->right = tree_new(5, NULL, NULL);
}

tree* test(int i) {
    if (i < 50) {
        return test(i + 1);
    }

    return NULL;
}

int main(int argc, char** argv) {
    /* Initialize Garbage Collector */
    gc_init(&argc);
    /* Turn off stdout buffer */
    setvbuf(stdout, NULL, _IONBF, 0);
    /* Construct the tree */
    tree* test_tree;
    create_test_tree(&test_tree);
    tree_traverse(test_tree);
    gc_cleanup();
    /* Create a loop */
    test_tree->left = test_tree;
    //tree_traverse(test_tree); /* Will Stack Overflow */
    gc_cleanup();
    /* Release the test tree */
    test_tree = NULL;
    gc_cleanup();
    return EXIT_SUCCESS;
}

