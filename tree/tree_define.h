#ifndef TREE_TYPE_H_
#define TREE_TYPE_H_

typedef struct treenode {
    struct treenode *left, *right, *top;
    void *data;
} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;

#endif // TREE_TYPE_H_