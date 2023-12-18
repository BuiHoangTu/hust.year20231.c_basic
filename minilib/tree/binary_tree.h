#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

/**
 * In this implementation, both left and right are the child
 */

#include "tree_define.h"
#include "core/type.h"

/// <summary>
/// Make a node with data
/// </summary>
/// <param name="data">Content of the node, maybe id</param>
/// <returns>tree node with the data</returns>
TreeNode *bTreeMakeNode(void *data);

/// <summary>
/// Make a tree for easier tree contain than keeping root
/// </summary>
/// <param name="root">TreeNode representing root of the tree</param>
/// <returns>Tree</returns>
Tree *makeBTree(TreeNode *root);

/// <summary>
/// Find the first node with that has data match with data by func.
/// </summary>
/// <param name="data">sample data</param>
/// <param name="tree">the tree that need to search from</param>
/// <param name="func">how to compare 2 void pointer compare treenode date with sample data</param>
/// <returns>One node that match, NULL if none match</returns>
TreeNode *bTreeFindNode(void *data, Tree *tree, CompareFunction func);

void bTreePreOrder(Tree *t, Consume1 action);

void bTreeInOrder(Tree *t, Consume1 action);

void bTreePostOrder(Tree *t, Consume1 action);

long bTreeHeight(Tree *tree);

long bTreeNodeDepth(Tree *tree, void *data, CompareFunction compareFunction);


#endif // BINARY_TREE_H_