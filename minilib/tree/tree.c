#include "tree/tree.h"
#include "list/stack.h"
#include "list/single_linked_list.h"
#include "stdlib.h"

TreeNode *treeCreateNode(void *data) {
    quickCalloc(TreeNode, node);
    node->data = data;
    return node;
}

Tree *createTree(TreeNode *root) {
    quickCalloc(Tree, tree);
    tree->root = root;
    return tree;
}

TreeNode *_rootFindNode(void *data, TreeNode *root, CompareFunction func) {
    if (!root)
        return NULL;

    if (func(root->data, data) == 0) {
        return root;
    } else {
        // find in right
        TreeNode *right = _rootFindNode(data, root->right, func);
        if (right != NULL)
            return right;
            // if nothing in right, try in deeper lv
        else
            return _rootFindNode(data, root->left, func);
    }
}

TreeNode *treeFindNode(void *data, Tree *tree, CompareFunction func) {
    if (!tree || !func)
        return NULL;
    return _rootFindNode(data, tree->root, func);
}

void treeAddLastChild(TreeNode *node, void *data) {
    if (!node)
        return;

    // make new node
    TreeNode *cur = treeCreateNode(data);
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

void treePreOrder(Tree *t, Consume1 action) {
    // check the tree
    if (!t) return;
    TreeNode *root = t->root;
    if (!root) return;

    // stack of node
    Stack *stackOfTop = createStack();
    stackPush(stackOfTop, root);

    // the data in preorder will be stored here
    SingleLinkedList *dataInPreOrder = CreateSll();

    while (stackOfTop->length > 0) {
        // get node add to back of data list
        TreeNode *node = (TreeNode *) stackPop(stackOfTop);
        sllAddLast(dataInPreOrder, node->data);

        // push all child in revert order
        TreeNode *child = node->left;
        Stack *revertor = createStack();
        while (child) {
            stackPush(revertor, child);
            // go to next sibling;
            child = child->right;
        }
        while (revertor->length > 0) stackPush(stackOfTop, stackPop(revertor));
        stackFree(revertor);
    }

    sll_foreach(data, dataInPreOrder) {
        action(data);
    }

    sllFree(dataInPreOrder);
    stackFree(stackOfTop);
}

void nodeInOrder(TreeNode *root, Consume1 action) {
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

void treeInOrder(Tree *t, Consume1 action) {
    if (t) {
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
    for (int i = 0; i < index; i++) {
        if (!child) break;
        child = child->right;
    }
    return child;
}

void nodePostOrder(TreeNode *root, Consume1 action) {
    Stack *nodeStack = createStack();
    Stack *indexStack = createStack();
    int rootIndex = 0;
    SingleLinkedList *list = CreateSll();

    while (root || nodeStack->length > 0) {
        if (root) {
            stackPush(nodeStack, root);
            stackPush(indexStack, copy2heap(&rootIndex, sizeof(int)));
            rootIndex = 0;

            // move to child
            root = root->left;
            continue; // continue until no more first child
        }

        TreeNode *node = (TreeNode *) stackPop(nodeStack);
        int *nodeIndex = (int *) stackPop(indexStack);

        sllAddLast(list, node->data);

        // pop all children of a node
        while (nodeStack->length > 0 && *nodeIndex == childrenCount((TreeNode *) stackPeek(nodeStack)) - 1) {
            node = (TreeNode *) stackPop(nodeStack);
            free(nodeIndex);
            nodeIndex = (int *) stackPop(indexStack);

            sllAddLast(list, node->data);
        }

        // if there is another layer assign the root
        if (nodeStack->length > 0) {
            root = getChild(((TreeNode *) stackPeek(nodeStack)), *nodeIndex + 1);
            rootIndex = *nodeIndex + 1;
        }
        free(nodeIndex);
    }

    sll_foreach(o, list) {
        action(o);
    }

    stackFree(nodeStack);
    stackFree(indexStack);
    sllFree(list);
}

void treePostOrder(Tree *t, Consume1 action) {
    if (t) {
        nodePostOrder(t->root, action);
    }
}

long nodeHeight(TreeNode *node) {
    long childHeight = 0;

    // iterate children and get max height
    TreeNode *child = node->left;
    while (child) {
        long currentHeight = nodeHeight(child);
        childHeight = childHeight > currentHeight ? childHeight : currentHeight;
        child = child->right;
    }

    return childHeight + 1;
}

long treeHeight(Tree *tree) {
    return nodeHeight(tree->root);
}

long _treeNodeDepth(TreeNode *node, long current, void *data, CompareFunction compare) {
    if (!node)
        return -1;

    if (compare(node->data, data) == 0) {
        return current;
    } else {
        // find in right
        long right = _treeNodeDepth(node->right, current + 1, data, compare);
        if (right != -1)
            return right;
            // if nothing in right, try in deeper lv
        else
            return _treeNodeDepth(node->left, current + 1, data, compare);
    }
}


long treeNodeDepth(Tree *tree, void *data, CompareFunction compare) {
    if (!tree) return -1;

    return _treeNodeDepth(tree->root, 0, data, compare);
}

