//
// Created by tu on 18/12/2023.
//
#include "tree/binary_tree.h"
#include <stdio.h>
#include <string.h>
#include "core/type.h"

Tree *tree;

void makeRoot(char *command) {
    int id;
    sscanf(command + 8, "%d", &id);

    TreeNode *root = bTreeCreateNode(copy2heap(&id, sizeof(int)));
    tree = createBTree(root);
}

void addLeftChild(char *command) {
    int parentId, curId;
    sscanf(command + 12, "%d %d", &parentId, &curId);

    // check if child exist
    TreeNode *child = bTreeFindNode(&curId, tree, intCmp);
    if (child)
        return;

    // find the parent
    TreeNode *parent = bTreeFindNode(&parentId, tree, intCmp);
    if (!parent)
        return;

    if (parent->left) return;
    TreeNode *nnode = bTreeCreateNode(copy2heap(&curId, sizeof(int)));
    parent->left =  nnode;
}

void addRightChild(char *command) {
    int parentId, curId;
    sscanf(command + 13, "%d %d", &parentId, &curId);

    // check if child exist
    TreeNode *child = bTreeFindNode(&curId, tree, intCmp);
    if (child)
        return;

    // find the parent
    TreeNode *parent = bTreeFindNode(&parentId, tree, intCmp);
    if (!parent)
        return;
    if (parent->right) return;
    TreeNode *nnode = bTreeCreateNode(copy2heap(&curId, sizeof(int)));
    parent->right = nnode;
}

void printNodeData(void *data) {
    printf("%d ", void2(int, data));
}

void inOrder() {
    bTreeInOrder(tree, printNodeData);
}

void preOrder() {
    bTreePreOrder(tree, printNodeData);
}

void postOrder() {
    bTreePostOrder(tree, printNodeData);
}

int countNodesWith2Children(TreeNode *node) {
    if (node == NULL) return 0;

    int cl = countNodesWith2Children(node->left);
    int cr = countNodesWith2Children(node->right);

    int total = cl + cr;

    if (node->left != NULL && node->right != NULL) {
        total++;
    }

    return total;
}

int isRootMaxHeap(TreeNode *node) {
    if (!node)
        return 1;

    if ((node->left != NULL && intCmp(node->data, node->left->data) < 0) ||
        (node->right != NULL && intCmp(node->data, node->right->data) < 0)) {
        return 0;
    }

    return isRootMaxHeap(node->left) && isRootMaxHeap(node->right);
}

int isMaxHeap(char *command) {
    int parentId;
    sscanf(command + 9, "%d", &parentId);

    // find the parent
    TreeNode *node = bTreeFindNode(&parentId, tree, intCmp);
    return isRootMaxHeap(node);
}

int main(int argc, const char *argv[]) {
    char *line = (char *) malloc(1024);

    while (1) {
        fgets(line, 1024, stdin);
        if (strncmp("Quit", line, 4) == 0)
            break;
        if (strncmp("CountNodes2Children", line, 6) == 0) {
            int res = countNodesWith2Children(tree->root);
            printf("%d", res);
        }
        if (strncmp("InOrder", line, 7) == 0)
            inOrder();
        if (strncmp("PreOrder", line, 8) == 0)
            preOrder();
        if (strncmp("PostOrder", line, 9) == 0)
            postOrder();
        if (strncmp("MakeRoot", line, 8) == 0)
            makeRoot(line);
        if (strncmp("AddLeftChild", line, 10) == 0)
            addLeftChild(line);
        if (strncmp("AddRightChild", line, 5) == 0)
            addRightChild(line);
        if (strncmp("IsMaxHeap", line, 9) == 0) {
            int res = isMaxHeap(line);
            printf("%d", res);
        }
    }

    return 0;
}
