#include "tree/binary_tree.h"

TreeNode *bTreeMakeNode(void *data) {
    quickCalloc(TreeNode, newNode);
    newNode->data = data;
    return newNode;
}

Tree *makeBTree(TreeNode *root) {
    quickCalloc(Tree, tree);
    tree->root = root;
    return tree;
}

TreeNode *_bTreeFindNode(void *data, TreeNode *root, CompareFunction compareFunction) {
    if (root == NULL) {
        return NULL;
    }

    if (compareFunction(data, root->data) == 0) return root;

    TreeNode *left = _bTreeFindNode(data, root->left, compareFunction);
    if (left) return left;

    TreeNode *right = _bTreeFindNode(data, root->right, compareFunction);
    return right;
}


TreeNode *bTreeFindNode(void *data, Tree *tree, CompareFunction compareFunction) {
    if (tree == NULL || compareFunction == NULL) {
        return NULL;
    }

    return _bTreeFindNode(data, tree->root, compareFunction);
}

void bNodePreOrder(TreeNode *node, Consume1 action) {
    if (node != NULL) {
        action(node->data);
        bNodePreOrder(node->left, action);
        bNodePreOrder(node->right, action);
    }
}

void bTreePreOrder(Tree *t, Consume1 action) {
    if (t) {
        bNodePreOrder(t->root, action);
    }
}

// Function to perform in-order traversal on the tree
void bNodeInOrder(TreeNode *node, void (*action)(void *)) {
    if (node != NULL) {
        bNodeInOrder(node->left, action);
        action(node->data);
        bNodeInOrder(node->right, action);
    }
}

void bTreeInOrder(Tree *t, Consume1 action) {
    if (t) {
        bNodeInOrder(t->root, action);
    }
}


// Function to perform post-order traversal on the tree
void bNodePostOrder(TreeNode *node, void (*action)(void *)) {
    if (node != NULL) {
        bNodePostOrder(node->left, action);
        bNodePostOrder(node->right, action);
        action(node->data);
    }
}

void bTreePostOrder(Tree *t, Consume1 action) {
    if (t) {
        bNodePostOrder(t->root, action);
    }
}
