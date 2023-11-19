#include "tree/tree.h"

TreeNode *treeMakeNode(void *data)
{
    quickCalloc(TreeNode, node);
    node->data = data;
    return node;
}

Tree *treeMakeTree(TreeNode *root)
{
    quickCalloc(Tree, tree);
    tree->root = root;
    return tree;
}

TreeNode *_rootFindNode(void *data, TreeNode *root, CompareFunction func)
{
    if (!root)
        return NULL;

    if (func(root->data, data) == 0)
    {
        return root;
    }
    else
    {
        // find in right
        TreeNode *right = _rootFindNode(data, root->right, func);
        if (right != NULL)
            return right;
        // if nothing in right, try in deeper lv
        else
            return _rootFindNode(data, root->left, func);
    }
}

TreeNode *treeFindNode(void *data, Tree *tree, CompareFunction func)
{
    if (!tree || !func)
        return NULL;
    return _rootFindNode(data, tree->root, func);
}

void treeAddLast(TreeNode *node, void *data)
{
    if (!node)
        return;

    TreeNode *mostRightNode = node;
    while (mostRightNode->right)
        mostRightNode = mostRightNode->right;

    TreeNode *cur = treeMakeNode(data);
    mostRightNode->right = cur;
}

void _nodePreOrder(TreeNode *root, Processor1 action)
{
    if (root != NULL)
    {
        action(root->data);
        _nodePreOrder(root->left, action);
        _nodePreOrder(root->right, action);
    }
}

void treePreOrder(Tree *t, Processor1 action)
{
    if (t)
    {
        _nodePreOrder(t->root, action);
    }
}

void _nodeInOrder(TreeNode *root, Processor1 action)
{
    if (root != NULL)
    {
        _nodeInOrder(root->left, action);
        action(root->data);
        _nodeInOrder(root->right, action);
    }
}

void treeInOrder(Tree *t, Processor1 action)
{
    if (t)
    {
        _nodeInOrder(t->root, action);
    }
}

void _nodePostOrder(TreeNode *root, Processor1 action)
{
    if (root != NULL)
    {
        _nodePostOrder(root->left, action);
        _nodePostOrder(root->right, action);
        action(root->data);
    }
}

void treePostOrder(Tree *t, Processor1 action)
{
    if (t)
    {
        _nodePostOrder(t->root, action);
    }
}