//
// Created by bhtuw on 20/11/2023.
//
#include "tree/tree.h"
#include "core/heap.h"
#include "stdio.h"

int int_cmp(void *v1, void *v2) {
    int i1 = void2(int, v1);
    int i2 = void2(int, v2);
    return i1 - i2;
}

void print_data_as_int(void *v0) {
    printf("%d ", void2(int, v0));
}

int main() {
    int i;

    i = 10;
    TreeNode *root = treeMakeNode(copy2heap(&i, sizeof(int)));
    Tree *tree = treeMakeTree(root);

    i = 10;
    TreeNode *parent = treeFindNode(&i, tree, int_cmp);

    i = 11;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));

    i = 1;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));

    i = 3;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));

    /**
     * tree
     * 10
     * -- 11
     * -- 1
     * -- 3
     */
    treeInOrder(tree, print_data_as_int);
    printf("\n");
    // 11 10 1 3

    i = 11;
    parent = treeFindNode(&i, tree, int_cmp);
    i = 5;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));
    i = 4;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));

    i = 3;
    parent = treeFindNode(&i, tree, int_cmp);
    i = 8;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));

    /**
     * tree
     * 10
     * |-- 11
     *   |-- 5
     *   |-- 4
     * |-- 1
     * |-- 3
     *   |-- 8
     */
    treePreOrder(tree, print_data_as_int);
    printf("\n");

    i = 3;
    parent = treeFindNode(&i, tree, int_cmp);
    i = 2;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));
    i = 7;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));

    i = 4;
    parent = treeFindNode(&i, tree, int_cmp);
    i = 6;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));
    i = 9;
    treeAddLastChild(parent, copy2heap(&i, sizeof(int)));

    /**
     * tree
     * 10
     * |-- 11
     *   |-- 5
     *   |-- 4
     *     |-- 6
     *     |-- 9
     * |-- 1
     * |-- 3
     *   |-- 8
     *   |-- 2
     *   |-- 7
     */
    treeInOrder(tree, print_data_as_int);
    printf("\n");

    treePostOrder(tree, print_data_as_int);
    printf("\n");
}