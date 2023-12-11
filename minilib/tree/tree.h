/**
 * In this implementation, left is the child, right is the next right sibling
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>
#include "core/heap.h"
#include "core/type.h"
#include "tree_define.h"

/// <summary>
/// Make a node with data
/// </summary>
/// <param name="data">Content of the node, maybe id</param>
/// <returns>tree node with the data</returns>
TreeNode *treeMakeNode(void *data);

/// <summary>
/// Make a tree for easier tree contain than keeping root
/// </summary>
/// <param name="root">TreeNode representing root of the tree</param>
/// <returns>Tree</returns>
Tree *treeMakeTree(TreeNode *root);

/// <summary>
/// Find the first node with that has data match with data by func.
/// </summary>
/// <param name="data">sample data</param>
/// <param name="tree">the tree that need to search from</param>
/// <param name="func">how to compare 2 void pointer compare treenode date with sample data</param>
/// <returns>One node that match, NULL if none match</returns>
TreeNode *treeFindNode(void *data, Tree *tree, CompareFunction func);

/// <summary>
/// Add a new node to the rightest side of the child node (left)
/// </summary>
/// <param name="node"></param>
/// <param name="data"></param>
void treeAddLastChild(TreeNode *node, void *data);

void treePreOrder(Tree *t, Consume1 action);

void treeInOrder(Tree *t, Consume1 action);

void treePostOrder(Tree *t, Consume1 action);

long treeHeight(Tree *tree);

long treeNodeDepth(Tree *tree, void *data, CompareFunction compareFunction);

#endif // TREE_H_