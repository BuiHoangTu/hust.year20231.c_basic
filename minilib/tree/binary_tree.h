#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

/**
 * In this implementation, both left and right are the child
 */

#include "tree_define.h"
#include "core/type.h"
#include "core/heap.h"

void bn_addLeftNode(TreeNode *root, void *nodeId, void *newNodeData, CompareFunction func)
{
    if (!root)
        return;
    if (func(root->data, nodeId) == 0)
    {
        if (root->left)
            return;
        else
        {
            quickCalloc(TreeNode, node);
            node->data = newNodeData;
            root->left = node;
        }
    }
    else
    {
        bn_addLeftNode(root->left, nodeId, newNodeData, func);
        bn_addLeftNode(root->right, nodeId, newNodeData, func);
    }
}

void bn_addRightNode(TreeNode *root, void *nodeId, void *newNodeData, CompareFunction func)
{
    if (!root)
        return;
    if (func(root->data, nodeId) == 0)
    {
        if (root->right)
            return;
        else
        {
            quickCalloc(TreeNode, node);
            node->data = newNodeData;
            root->right = node;
        }
    }
    else
    {
        bn_addRightNode(root->left, nodeId, newNodeData, func);
        bn_addRightNode(root->right, nodeId, newNodeData, func);
    }
}

TreeNode *bn_findNode(TreeNode *root, void *data, CompareFunction func)
{
    if (!root)
        return NULL;
    if (func(root->data, data) == 0)
        return root;

    TreeNode *res = bn_findNode(root->left, data, func);
    if (res)
        return res;
    else
        return bn_findNode(root->right, data, func);
}

long bn_countNode(TreeNode *root)
{
    if (!root)
        return 0;

    long childCount = 0;
    childCount += bn_countNode(root->left) + bn_countNode(root->right);

    return childCount + 1;
}

#define bn_traverse_lrn(cur, tree)                       \
    for (TreeNode *cur = bn_first_postorder(tree->root); \
         cur != NULL; cur = bn_next_postorder(cur))

#define bn_traverse_lnr(cur, tree)                 \
    for (TreeNode *cur = bn_left_most(tree->root); \
         cur != NULL; cur = bn_next_inorder(cur))

#define bn_traverse_rnl(cur, tree)                  \
    for (TreeNode *cur = bn_right_most(tree->root); \
         cur != NULL; cur = bn_prev_inorder(cur))

#define bn_MOST(x, child, out)       \
    (out) = (x);                     \
    do                               \
    {                                \
        while ((out)->child != NULL) \
        {                            \
            (out) = (out)->child;    \
        }                            \
    } while (0)

#define BS_NEAREST(x, left, right, out)                  \
    do                                                   \
    {                                                    \
        if ((x)->right != NULL)                          \
        {                                                \
            (out) = bn_##left##_most((x)->right);        \
        }                                                \
        else                                             \
        {                                                \
            (out) = (x)->top;                            \
            while ((out) != NULL && (x) == (out)->right) \
            {                                            \
                (x) = (out);                             \
                (out) = (out)->top;                      \
            }                                            \
        }                                                \
    } while (0)

TreeNode *bn_right_most(TreeNode *x)
{
    if (!x)
    {
        return NULL;
    }
    TreeNode *y;
    bn_MOST(x, right, y);
    return y;
}

int compareInt(void *v1, void *v2)
{
    int i1 = *((int *)v1);
    int i2 = *((int *)v2);
    return i2 - i1;
}

TreeNode *bn_prev_inorder(TreeNode *x)
{
    if (!x)
    {
        return NULL;
    }
    TreeNode *y;
    BS_NEAREST(x, right, left, y);
    return y;
}

#include <stdio.h>


#endif // BINARY_TREE_H_