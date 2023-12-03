#pragma region minilib-combined
#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>
#include <string.h>

#define quickCalloc(type, variable) type *variable = (type *) calloc (1, sizeof(type))

#define void2(type, pointer) (*((type *)pointer))

void *copy2heap(void *data, size_t data_size);

void *copy2heap(void *data, size_t data_size)
{
    void *p = malloc(data_size);
    memcpy(p, data, data_size);
    return p;
}
#endif // HEAP_H_

#ifndef TYPE_H_
#define TYPE_H_

/**
 * A function defining how 2 compare unk variable (generic structure)
 */
typedef int (*CompareFunction)(void *, void *);

typedef void (*Action)();

typedef void (*Processor0)();

typedef void (*Processor1)(void *);

/**
 *
 */
int intCmp(void *v1, void *v2);

int intCmp(void *v1, void *v2)
{
    int i1 = void2(int, v1);
    int i2 = void2(int, v2);

    return i1 - i2;
}

#endif // TYPE_H_

#ifndef SLL_H_
#define SLL_H_

#include <stdlib.h>

typedef struct sln
{
	void *value;
	struct sln *next;
} SingleLinkedNode;

typedef struct sll
{
	int length;
	SingleLinkedNode *first;
	SingleLinkedNode *last;
} SingleLinkedList;

/**
 * Create a SingleLinkedList
*/
SingleLinkedList *sll_create();

/**
 * Add an object to the last part of the list 
*/
void sll_add_last(SingleLinkedList *list, void *value);

/**
 * Add an object at the index 
 * @return 1: success; 0: index out of bound
*/
int sll_insert(SingleLinkedList *list, void *value, int index);

/**
 * Get an object at the index
*/
void *sll_get(SingleLinkedList *list, int index);

/**
 * Remove an object at index, return that object 
*/
void *sll_remove(SingleLinkedList *list, int index);

/**
 * Move node to next node and obj to the value of the next node
 * @param node: address of pointer to the current node 
 * @param obj: address of pointer to the variable to store value
 * @return 1: if the operation success
 *         0: if node is already the last node
*/
int sll_next(SingleLinkedNode **node, void **obj);

#define sll_foreach(obj, list)             \
	SingleLinkedNode *_node = list->first; \
	void *obj;                             \
	while (sll_next(&_node, &obj))

void sll_free(SingleLinkedList* list);


SingleLinkedList *sll_create()
{
	SingleLinkedList *list = (SingleLinkedList *)malloc(sizeof(SingleLinkedList));
	list->first = NULL;
	list->last = NULL;
	list->length = 0;

	return list;
}

/**
 * Get node at index
 */
SingleLinkedNode *__sll_get_node(SingleLinkedList *list, int index)
{
	if (index >= list->length) return NULL;

	SingleLinkedNode *current = list->first;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current;
}

/**
 * add node to the last, increase length
 */
void __sll_add_node_last(SingleLinkedList *list, SingleLinkedNode *node)
{
	// increase length
	list->length++;
	// if empty list
	if (list->first == NULL)
	{
		// add node to both first and last
		list->first = list->last = node;
	}
	else // add node after last
	{
		list->last->next = node;
		list->last = node;
	}
}

/**
 * insert node at index, increase length
 */
int __sll_insert_node(SingleLinkedList *list, SingleLinkedNode *node, int index)
{
	if (index > list->length) return 0;

	// if insert at first
	if (index == 0)
	{
		node->next = list->first;
		list->first = node;
		list->length++;
		return 1;
	}
	// insert last 
	else if (index == list->length)
	{
		// this function increase already
		__sll_add_node_last(list, node);
		return 1;
	} 
	else
	{
		// add node at middle
		SingleLinkedNode *current = __sll_get_node(list, index - 1);
		// add next node
		node->next = current->next;
		// add this node
		current->next = node;
		list->length++;
		return 1;
	}
}

/**
 * remove a node, decrease length, free the node
 * @param prevNode: the node before the node need removing
 * @return value that the node holds
 */
void *__sll_remove_node(SingleLinkedList *list, SingleLinkedNode *node, SingleLinkedNode *prevNode)
{
	// node is first node
	if (prevNode == NULL)
	{
		list->first = node->next;
	}
	// node is the last node
	else if (node->next == NULL)
	{
		prevNode->next = NULL;
		list->last = prevNode;
	}
	// node is in the middle 
	else
	{
		prevNode->next = node->next;
	}

    list->length--;
	void *value = node->value;
	free(node);
	return value;
}

SingleLinkedNode *sln_create(void *value)
{
	SingleLinkedNode *node = (SingleLinkedNode *)malloc(sizeof(SingleLinkedNode));
	node->next = NULL;
	node->value = value;
	return node;
}

void sll_add_last(SingleLinkedList *list, void *value)
{
	SingleLinkedNode *newNode = sln_create(value);
	__sll_add_node_last(list, newNode);
}

int sll_insert(SingleLinkedList *list, void *value, int index)
{
	SingleLinkedNode *newNode = sln_create(value);
	return __sll_insert_node(list, newNode, index);
}

void *sll_get(SingleLinkedList *list, int index)
{
	SingleLinkedNode* node = __sll_get_node(list, index);
	return node == NULL ? NULL : node->value;
}

void *sll_remove(SingleLinkedList *list, int index)
{
	if (index >= list->length)
		return NULL;

	if (index == 0)
	{
		return __sll_remove_node(list, list->first, NULL);
	}

	SingleLinkedNode *prev = __sll_get_node(list, index - 1);
	SingleLinkedNode *current = prev->next;

	return __sll_remove_node(list, current, prev);
}

int sll_next(SingleLinkedNode **node, void **obj)
{
    if ((*node) == NULL)
        return 0;

    *obj = (*node)->value;
    (*node) = (*node)->next;

    return 1;
}

void sll_free(SingleLinkedList *list)
{
	free(list);
}

#endif // SLL_H_


#ifndef QUEUE_H_
#define QUEUE_H_

#define Queue SingleLinkedList

Queue* queue_create();

void enqueue(Queue* queue, void* value);

void* dequeue(Queue* queue);

void* queue_peek(Queue* queue);

void queue_free(Queue* queue);


Queue* queue_create() {
    return sll_create();
}

void enqueue(Queue* queue, void* value) {
    sll_add_last(queue, value);
}

void* dequeue(Queue* queue) {
    return sll_remove(queue, 0);
}

void* queue_peek(Queue* queue) {
    return sll_get(queue, 0);
}

void queue_free(Queue* queue) {
    sll_free(queue);
}

#endif // QUEUE_H_

#ifndef STACK_H_
#define STACK_H_

#define Stack SingleLinkedList

Stack* stack_create();

void stack_push(Stack* stack, void* value);

void* stack_pop(Stack* stack);

void* stack_peek(Stack* stack);

void stack_free(Stack* stack);

Stack* stack_create() {
    return sll_create();
}

void stack_push(Stack* stack, void* value) {
    sll_insert(stack, value, 0);
}

void* stack_pop(Stack* stack) {
    return sll_remove(stack, 0);
}

void* stack_peek(Stack* stack) {
    return sll_get(stack, 0);
}

void stack_free(Stack* stack) {
    sll_free(stack);
}


#endif // STACK_H_

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

/**
 * In this implementation, left is the child, right is the next right sibling
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>

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

void treePreOrder(Tree *t, Processor1 action);

void treeInOrder(Tree *t, Processor1 action);

void treePostOrder(Tree *t, Processor1 action);


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
#endif // TREE_H_

#ifndef SELECTION_SORT_H_
#define SELECTION_SORT_H_
#include <stdlib.h>

void selectionSort(void* arr[], size_t arrSize, CompareFunction compareFunction);

void selectionSort(void *arr[], size_t arrSize, CompareFunction compareFunction) {
    for (int i = 0; i < arrSize; i++) {
        int minIdx = i;

        for (int j = i + 1; j < arrSize; j++) {
            if (compareFunction(arr[i], arr[j] ) > 0) {
                minIdx = j;
            }
        }

        void *tmp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = tmp;
    }
}

#endif //SELECTION_SORT_H_

#ifndef MERGE_SORT_H
#define MERGE_SORT_H


void mergeSort(void* arr[], int n, CompareFunction compare);

// Merges two sub-arrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(void *arr[], int l, int m, int r, CompareFunction compare)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    void** L = (void**) malloc(sizeof(void*) * n1);
    void** R = (void**) malloc(sizeof(void*) * n2);

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    free(L);

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(R);
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void sortSubArray(void *arr[], int l, int r, CompareFunction pFunction)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        sortSubArray(arr, l, m, pFunction);
        sortSubArray(arr, m + 1, r, pFunction);

        merge(arr, l, m, r, pFunction);
    }
}

void mergeSort(void *arr[], int n, CompareFunction compare) {
    sortSubArray(arr, 0, n - 1, compare);
}

#endif //MERGE_SORT_H


#ifndef HEAP_SORT_H
#define HEAP_SORT_H
void heapSort(void* arr[], size_t arrSize, CompareFunction compareFunction);

void heapify(void *arr[], int n, int i, CompareFunction compare)
{
    // Find largest among root,
    // left child and right child

    // Initialize largest as root
    int largestIndex = i;

    // left = 2*i + 1
    int leftIndex = 2 * i + 1;

    // right = 2*i + 2
    int rightIndex = 2 * i + 2;

    // If left child is larger than root
    if (leftIndex < n && compare(arr[leftIndex], arr[largestIndex]) > 0)
        largestIndex = leftIndex;

    // If right child is larger than largest
    // so far
    if (rightIndex < n && compare(arr[rightIndex], arr[largestIndex]) > 0)
        largestIndex = rightIndex;

    // Swap and continue heapify
    // if root is not the largest
    // If largest is not root
    if (largestIndex != i) {
        void *tmpV = arr[i];
        arr[i] = arr[largestIndex];
        arr[largestIndex] = tmpV;

        // Recursively heapify the affected
        // subtree
        heapify(arr, n, largestIndex, compare);
    }
}

void heapSort(void *arr[], size_t arrSize, CompareFunction compareFunction) {
    // build max heap
    for (int i = (arrSize / 2) - 1; i >= 0; i-- ) {
        heapify(arr, arrSize, i, compareFunction);
    }

    // sort
    for (int i = arrSize - 1; i >= 0; i--) {
        void *tmpV = arr[0];
        arr[0] = arr[i];
        arr[i] = tmpV;

        // Heapify root element
        // to get highest element at
        // root again
        heapify(arr, i, 0, compareFunction);
    }
}



#endif //HEAP_SORT_H
#pragma endregion


#include <stdio.h>

int cmp(void *v1, void *v2) {
    int i1 = *((int*) v1);
    int i2 = *((int*) v2);

    return i1 - i2;
}

int main() {
    int n;
    scanf("%d", &n);

    void **arr = (void*) malloc(n * sizeof(void*));

    int x;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);

        arr[i] = copy2heap(&x,sizeof(int));
    }

    heapSort(arr,n,cmp);

    for (int i = 0; i < n; ++i) {
        printf("%d ", void2(int, arr[i]));
    }
}