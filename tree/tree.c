#include "tree/tree.h"
#include "list/stack.h"
#include "list/single_linked_list.h"
#include "stdlib.h"

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

void treePreOrder(Tree *t, Processor1 action)
{
    // check the tree
    if (!t) return;
    TreeNode *root = t->root;
    if (!root) return;

    // stack of node
    Stack *stackOfTop = stack_create();
    stack_push(stackOfTop, root);

    // the data in preorder will be stored here
    SingleLinkedList *dataInPreOrder = sll_create();

    while (stackOfTop->length > 0) {
        // get node add to back of data list
        TreeNode *node = (TreeNode*) stack_pop(stackOfTop);
        sll_add_last(dataInPreOrder, node->data);

        // push all child in revert order
        TreeNode *child = node->left;
        Stack *revertor = stack_create();
        while (child) {
            stack_push(revertor, child);
            // go to next sibling;
            child = child->right;
        }
        while (revertor->length > 0) stack_push(stackOfTop, stack_pop(revertor));
        stack_free(revertor);
    }

    sll_foreach(data, dataInPreOrder) {
        action(data);
    }

    sll_free(dataInPreOrder);
    stack_free(stackOfTop);
}

void nodeInOrder(TreeNode *root, Processor1 action)
{
    if (root != NULL) {
        // visit first child
        TreeNode *firstChild = root->left;
        nodeInOrder(firstChild, action);

        // visit seft
        action(root->data);

        // the rest
        if (firstChild != NULL) {
            TreeNode *rest = firstChild->right;

            while (rest != NULL) {
                nodeInOrder(rest, action);
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
        nodeInOrder(t->root, action);
    }
}

int childrenCount(TreeNode *node) {
    int count = 0;
    TreeNode *child = node->left;
    while (child) {
        count++;
        child = child->right;
    }
    return count;
}

TreeNode *getChild(TreeNode *parent, int index) {
    TreeNode *child = parent->left;
    for (int i = 0; i < index; i ++) {
        if (!child) break;
        child = child->right;
    }
    return child;
}

void nodePostOrder(TreeNode *root, Processor1 action)
{
    Stack *nodeStack = stack_create();
    Stack *indexStack = stack_create();
    int rootIndex = 0;
    SingleLinkedList *list = sll_create();

    while (root || nodeStack->length > 0) {
        if (root) {
            stack_push(nodeStack, root);
            stack_push(indexStack, copy2heap(&rootIndex, sizeof(int)));
            rootIndex = 0;

            // move to child
            root = root->left;
            continue; // continue until no more first child
        }

        TreeNode *node = (TreeNode*)stack_pop(nodeStack);
        int *nodeIndex = (int*) stack_pop(indexStack);

        sll_add_last(list, node->data);

        // pop all children of a node
        while (nodeStack->length > 0 && *nodeIndex == childrenCount((TreeNode*) stack_peek(nodeStack)) - 1) {
            node = (TreeNode*)stack_pop(nodeStack);
            free(nodeIndex);
            nodeIndex = (int*) stack_pop(indexStack);

            sll_add_last(list, node->data);
        }

        // if there is another layer assign the root
        if (nodeStack->length > 0) {
            root = getChild(((TreeNode *) stack_peek(nodeStack)), *nodeIndex + 1);
            rootIndex = *nodeIndex + 1;
        }
        free(nodeIndex);
    }

    sll_foreach(o, list) {
        action(o);
    }

    stack_free(nodeStack);
    stack_free(indexStack);
    sll_free(list);
}

void treePostOrder(Tree *t, Processor1 action)
{
    if (t)
    {
        nodePostOrder(t->root, action);
    }
}