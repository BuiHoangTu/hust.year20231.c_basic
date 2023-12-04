#include "tree/tree.h"
#include <stdio.h>
#include <string.h>
#include "core/type.h"

Tree *tree;

void makeRoot(char *command) {
    int id;
    sscanf(command + 8, "%d", &id);

    TreeNode *root = treeMakeNode(copy2heap(&id, sizeof(int)));
    tree = treeMakeTree(root);
}

void insert(char *command) {
    int parentId, curId;
    sscanf(command + 6, "%d %d", &curId, &parentId);

    // check if child exist
    TreeNode *child = treeFindNode(&curId, tree, intCmp);
    if (child)
        return;

    // find the parent
    TreeNode *parent = treeFindNode(&parentId, tree, intCmp);
    if (!parent)
        return;
    treeAddLastChild(parent, copy2heap(&curId, sizeof(int)));
}

void printNodeData(void *data) {
    printf("%d ", void2(int, data));
}

void inOrder() {
    treeInOrder(tree, printNodeData);
}

void preOrder() {
    treePreOrder(tree, printNodeData);
}

void postOrder() {
    treePostOrder(tree, printNodeData);
}

void height(char *command) {
    int nodeId;
    sscanf(command + 6, "%d", &nodeId);
    TreeNode *root = treeFindNode(&nodeId, tree, intCmp);
    Tree *tmpTree = treeMakeTree(root);
    printf("%ld\n", treeHeight(tmpTree));
    free(tmpTree);
}

void depth(char *command) {
    int nodeId;
    sscanf(command + 5, "%d", &nodeId);
    printf("%ld\n", treeNodeDepth(tree, &nodeId, intCmp));

}

int main(int argc, const char *argv[]) {
    char *line = (char *) malloc(1024);

    while (1) {
        fgets(line, 1024, stdin);
        if (strncmp("*", line, 1) == 0)
            break;
        if (strncmp("Insert", line, 6) == 0)
            insert(line);
        if (strncmp("InOrder", line, 7) == 0)
            inOrder();
        if (strncmp("PreOrder", line, 8) == 0)
            preOrder();
        if (strncmp("PostOrder", line, 9) == 0)
            postOrder();
        if (strncmp("MakeRoot", line, 8) == 0)
            makeRoot(line);
        if (strncmp("Height", line, 6) == 0)
            height(line);
        if (strncmp("Depth", line, 5) == 0)
            depth(line);
    }

    return 0;
}
