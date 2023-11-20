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

void treeAddLastChild(TreeNode *node, void *data)
{
    if (!node)
        return;

    // make new node
    TreeNode *cur = treeMakeNode(data);
    // find child
    TreeNode *child = node->left;
    // if no child, just add
    if (!child) {
        node->left = cur;
        return;
    }

    // if node has children, find last
    TreeNode *mostRightNode = child;
    while (mostRightNode->right)
        mostRightNode = mostRightNode->right;
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
    if (root != NULL) {
        // visit first child
        TreeNode *firstChild = root->left;
        _nodeInOrder(firstChild, action);

        // visit seft
        action(root->data);

        // the rest
        if (firstChild != NULL) {
            TreeNode *rest = firstChild->right;

            while (rest != NULL) {
                _nodeInOrder(rest, action);
                // next siblings
                rest = rest->right;
            }
        }
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