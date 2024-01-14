#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#pragma region heap.h
#ifndef HEAP_H_
#define HEAP_H_


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

#pragma endregion

#pragma region type.h
#ifndef TYPE_H_
#define TYPE_H_
/**
 * A function defining how 2 compare unk variable (generic structure)
 */
typedef int (*CompareFunction)(void *, void *);

/**
 * An action
 */
typedef void (*Action)();

/**
 * Consume 1 void data to do something <br>
 * Ex: free pointer, print pointer
 */
typedef void (*Consume1)(void *);

/**
 * Hash a void data
 */
typedef int (*HashFunction)(void *);

/**
 * Compare 2 data
 */
int intCmp(void *v1, void *v2);

int intCmp(void *v1, void *v2)
{
    int i1 = void2(int, v1);
    int i2 = void2(int, v2);

    return i1 - i2;
}

#endif // TYPE_H_
#pragma endregion

#pragma region hash.h

//
// Created by tu on 12/11/23.
//

#ifndef INYEAR4_1_HASH_H
#define INYEAR4_1_HASH_H

int hashInt(void *vi);

int hashVoid(void *v, size_t size);

int hashString(const char *c);

#endif //INYEAR4_1_HASH_H

int hashInt(void *vi) {
    int value = void2(int, vi);
    value ^= value >> 16;
    value *= 0x85ebca6b;
    value ^= value >> 13;
    value *= 0xc2b2ae35;
    value ^= value >> 16;
    return value;
}

int hashVoid(void *v, size_t size) {
    int hash = 17;

    char *c = (char*)v;

    for (int i = 0; i < size; i++) {
        hash = (hash * 33) ^ c[i];
    }

    return hash;
}

int hashString(const char *c) {
    int hash = 17;

    for (int i = 0; c[i] != '\0'; i++) {
        hash = (hash * 33) ^ c[i];
    }

    return hash;
}


#pragma endregion

#pragma region array_list
//
// Created by bhtuw on 19/11/2023.
//

#ifndef MINI_LIBRARY_ARRAY_LIST_H
#define MINI_LIBRARY_ARRAY_LIST_H

typedef struct
{
    int length;
    int capacity;
    void **content;
} ArrayList;


ArrayList *createArraylist();


/**
 * Add an object to a list
 */
void arraylist_add_last(ArrayList *list, void *object);

/**
 * Insert an object to the specified position
 */
void arraylist_insert(ArrayList *list, int index, void *obj);

/**
 * Get object at index
 */
void *arraylist_get(ArrayList *list, int index);

/**
 * Remove and return element so user can free it if needed
 */
void *arraylist_remove(ArrayList *list, int index);

void _arraylist_next(ArrayList *list, int *index, void **obj);

/**
 * foreach object in the list, you do thing
 */
#define arraylist_foreach(obj, list) \
    int _i = 0;            \
    for (void *obj = list->content[0]; _i < list->length; _arraylist_next(list, &_i, &obj))

void arraylist_free(ArrayList *list);

#endif //MINI_LIBRARY_ARRAY_LIST_H

//
// Created by bhtuw on 19/11/2023.
//

#define MIN_CAPACITY 10
#define ALLOCATE_THRESHOLD (100 / 100)
#define ALLOCATE_RATIO 2

void _arr_enlarge(ArrayList *list)
{
    if (list->length >= list->capacity * ALLOCATE_THRESHOLD)
    {
        list->capacity *= ALLOCATE_RATIO;
        list->content = realloc(list->content, list->capacity * sizeof(void *));
    }
}

ArrayList *createArraylist()
{
    /* Allocate Memory */
    ArrayList *list = malloc(sizeof(ArrayList));
    if (list == NULL)
        return NULL;

    // initialize fields
    list->capacity = MIN_CAPACITY;
    list->length = 0;
    list->content = calloc(MIN_CAPACITY, sizeof(void *)); // content = array of pointer
    return list;
}

void _arraylist_next(ArrayList *list, int *index, void **obj)
{
    (*index)++;
    *obj = list->content[*index];
}

void arraylist_add_last(ArrayList *list, void *elem)
{
    // need bigger size
    _arr_enlarge(list);

    /* Adds one element of generic pointer type to the internal array */
    list->content[list->length] = elem;
    list->length += 1;
}

void arraylist_insert(ArrayList *list, int index, void *obj)
{
    // bigger size
    _arr_enlarge(list);

    memcpy(list->content + index + 1, list->content + index, list->length - index);
    list->content[index] = obj;
    list->length++;
}

void *arraylist_get(ArrayList *list, int index)
{
    /* Gets an member of the array at an index */
    return list->content[index];
}

void *arraylist_remove(ArrayList *list, int index)
{
    /* Removes one element at and index */
    if (index > list->length - 1)
        return NULL;

    void *del_elem = list->content[index];
    list->length--;
    // move all back elem forward
    memcpy(list->content + index, list->content + index + 1, list->length - index);
    return del_elem;
}

void arraylist_free(ArrayList *list)
{
    /* Clears the internal array */
    free(list->content);
    free(list);
}


#pragma endregion

#pragma region sll

#ifndef SLL_H_
#define SLL_H_

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
SingleLinkedList *CreateSll();

/**
 * Add an object to the last part of the list
*/
void sllAddLast(SingleLinkedList *list, void *value);

/**
 * Add an object at the index
 * @return 1: success; 0: index out of bound
*/
int sllInsert(SingleLinkedList *list, void *value, int index);

/**
 * Get an object at the index
*/
void *sllGet(SingleLinkedList *list, int index);

/**
 * Remove an object at index, return that object
*/
void *sllRemove(SingleLinkedList *list, int index);

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

void sllFree(SingleLinkedList* list);

#endif // SLL_H_


SingleLinkedList *CreateSll()
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

void sllAddLast(SingleLinkedList *list, void *value)
{
    SingleLinkedNode *newNode = sln_create(value);
    __sll_add_node_last(list, newNode);
}

int sllInsert(SingleLinkedList *list, void *value, int index)
{
    SingleLinkedNode *newNode = sln_create(value);
    return __sll_insert_node(list, newNode, index);
}

void *sllGet(SingleLinkedList *list, int index)
{
    SingleLinkedNode* node = __sll_get_node(list, index);
    return node == NULL ? NULL : node->value;
}

void *sllRemove(SingleLinkedList *list, int index)
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

void sllFree(SingleLinkedList *list)
{
    free(list);
}


#pragma endregion

#pragma region queue
#ifndef QUEUE_H_
#define QUEUE_H_

#define Queue SingleLinkedList

Queue* createQueue();

void enqueue(Queue* queue, void* value);

void* dequeue(Queue* queue);

void* queuePeek(Queue* queue);

void queueFree(Queue* queue);


#endif // QUEUE_H_

Queue* createQueue() {
    return CreateSll();
}

void enqueue(Queue* queue, void* value) {
    sllAddLast(queue, value);
}

void* dequeue(Queue* queue) {
    return sllRemove(queue, 0);
}

void* queuePeek(Queue* queue) {
    return sllGet(queue, 0);
}

void queueFree(Queue* queue) {
    sllFree(queue);
}


#pragma endregion

#pragma region stack
#ifndef STACK_H_
#define STACK_H_


#define Stack SingleLinkedList

Stack* createStack();

void stackPush(Stack* stack, void* value);

void* stackPop(Stack* stack);

void* stackPeek(Stack* stack);

void stackFree(Stack* stack);


#endif // STACK_H_

Stack* createStack() {
    return CreateSll();
}

void stackPush(Stack* stack, void* value) {
    sllInsert(stack, value, 0);
}

void* stackPop(Stack* stack) {
    return sllRemove(stack, 0);
}

void* stackPeek(Stack* stack) {
    return sllGet(stack, 0);
}

void stackFree(Stack* stack) {
    sllFree(stack);
}

#pragma endregion

#pragma region map
//
// Created by tu on 12/11/23.
//

#ifndef INYEAR4_1_HASH_MAP_H
#define INYEAR4_1_HASH_MAP_H

/**
 * @param size: how many elements are in the map <br>
 * @param capacity: length of content <br>
 * @param content: array of array_list <br>
 * @param hashFunction: how to hash a key
 * @param compareFunction: how to compare 2 key
 */
typedef struct hash_map {
    ArrayList** content;
    int size;
    int capacity;
    HashFunction hashFunction;
    CompareFunction compareFunction;
}HashMap;

HashMap *createHashmap(HashFunction hashFunction, CompareFunction compareFunction);

/**
 * Insert value to map
 * @param map
 * @param key
 * @param value new value
 * @param compare compare 2 key
 * @return old value if key existed <br>
 * NULL if no existed key
 */
void *hashmapPut(HashMap *map, void *key, void *value);

void *hashmapGet(HashMap *map, void *key);

ArrayList *keySet(HashMap *map);

void freeHashmap(HashMap* map, Consume1 freeKey, Consume1 freeValue);

#endif //INYEAR4_1_HASH_MAP_H
//
// Created by tu on 12/11/23.
//

#define DEFAULT_MAP_SIZE 100
#define MAP_SCALE 2

typedef struct entry{
    void *key;
    void *value;
    int hashCode;
}Entry;

void hashmapInitContent(HashMap *map) {
    map->content = (ArrayList**) malloc(map->capacity * sizeof(ArrayList*));
    for (int i = 0; i < map->capacity; i++) {
        map->content[i] = createArraylist();
    }
}

void hashmapFreeContent(ArrayList **content, int length, Consume1 freeKey, Consume1 freeValue, int doFreeEntry) {
    for (int i = 0; i < length; ++i) {
        ArrayList *bucket = content[i];
        if (doFreeEntry) {
            for (int j = 0; j < bucket->length; j++) {
                // free each entry, key, val
                Entry *entry = (Entry *) arraylist_get(bucket, j);
                if (freeKey) freeKey(entry->key);
                if (freeValue) freeValue(entry->value);
                free(entry);
            }
        }
        arraylist_free(bucket);
    }

    free(content);
}

void enlargeHashmap(HashMap *map) {
    // get old length and map
    int oldCapacity = map->capacity;
    ArrayList **oldContent = map->content;

    // enlarge content
    map->capacity *= MAP_SCALE;
    hashmapInitContent(map);

    // move old content
    for (int i = 0; i < oldCapacity; i++) {
        ArrayList *oldBucket = oldContent[i];
        for (int j = 0; j < oldBucket->length; j++) {
            Entry *entry = (Entry*) oldBucket->content[j];
            int newIndex = abs(entry->hashCode % map->capacity);
            arraylist_add_last(map->content[newIndex], entry);
        }
    }

    // free old content
    hashmapFreeContent(oldContent, oldCapacity, NULL, NULL, 0);
}

HashMap *createHashmap(HashFunction hashFunction, CompareFunction compareFunction) {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));

    map->capacity = DEFAULT_MAP_SIZE;

    hashmapInitContent(map);

    map->compareFunction = compareFunction;
    map->hashFunction = hashFunction;
    map->size = 0;

    return map;
}

void *hashmapPut(HashMap *map, void *key, void *value) {
    if (map->size >= map->capacity) {
        enlargeHashmap(map);
    }

    int hashCode = map->hashFunction(key);
    int index = abs(hashCode % map->capacity);
    ArrayList *bucket = map->content[index];

    // search for key in bucket, if exists, replace
    for (int i = 0; i < bucket->length; i++) {
        Entry *entry = (Entry*)arraylist_get(bucket, i);
        // check key equal key
        if (entry->key == key || map->compareFunction(entry->key, key) == 0) {
            void *oldValue = entry->value;
            entry->value = value;
            return oldValue;
        }
    }

    // if not exist, add entry
    Entry *newEntry = (Entry*) malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->hashCode = hashCode;
    arraylist_add_last(bucket, newEntry);

    map->size += 1;
    return NULL;
}

void *hashmapGet(HashMap *map, void *key) {
    int hashCode = map->hashFunction(key);
    int index = abs(hashCode % map->capacity);
    ArrayList* bucket = map->content[index];

    // Check if the key exists in the bucket
    for (int i = 0; i < bucket->length; ++i) {
        Entry *entry = (Entry*)arraylist_get(bucket, i);
        // check key equal key
        if (entry->key == key || map->compareFunction(entry->key, key) == 0) {
            // Key found, return the associated value
            return entry->value;
        }
    }

    // Key not found
    return NULL;
}

void freeHashmap(HashMap *map, Consume1 freeKey, Consume1 freeValue) {
    if (map == NULL) {
        return;
    }

    hashmapFreeContent(map->content, map->capacity, freeKey, freeValue, 1);

    free(map);
}

ArrayList *keySet(HashMap *map) {
    ArrayList *list = createArraylist();

    for (int i = 0; i < map->capacity; ++i) {
        ArrayList *bucket = map->content[i];
        for (int j = 0; j < bucket->length; j++) {
            Entry *entry = (Entry*)arraylist_get(bucket, j);
            arraylist_add_last(list,entry->key);
        }
    }

    return list;
}




#pragma endregion

#pragma region search
//
// Created by tu on 04/12/2023.
//
#ifndef INYEAR4_1_BINARY_SEARCH_H
#define INYEAR4_1_BINARY_SEARCH_H

/**
 * Find the target index in the array
 * @param arr the array
 * @param n length of array
 * @param target pointer to target
 * @param compare how to compare each elemnt in array with target
 * @return index of target in array <br> an int that less than 0 if cant find target in array
 */
int binarySearch(void *arr[], int n, void *target, CompareFunction compare);

#endif //INYEAR4_1_BINARY_SEARCH_H
//
// Created by tu on 04/12/2023.
//

int _binarySearch(void* arr[], int leftI, int rightI, void *target, CompareFunction compare) {
    while (leftI <= rightI) {
        int current = leftI + (rightI - leftI) / 2;
        if (compare(arr[current], target) == 0)
            return current;

        if (compare(arr[current], target) < 0)
            leftI = current + 1;
        else
            rightI = current - 1;
    }
    return -1;
}


int binarySearch(void **arr, int n, void *target, CompareFunction compare) {
    return _binarySearch(arr, 0, n - 1, target, compare);
}


#pragma endregion

#pragma region heap sort 

#ifndef HEAP_SORT_H
#define HEAP_SORT_H
#include <stdlib.h>

void heapSort(void* arr[], size_t arrSize, CompareFunction compareFunction);

void heapify(void *arr[], int n, int i, CompareFunction compare)
{
    int largestIndex = i;
    int leftIndex = 2 * i + 1;
    int rightIndex = 2 * i + 2;

    if (leftIndex < n && compare(arr[leftIndex], arr[largestIndex]) > 0)
        largestIndex = leftIndex;

    if (rightIndex < n && compare(arr[rightIndex], arr[largestIndex]) > 0)
        largestIndex = rightIndex;

    if (largestIndex != i) {
        void *tmpV = arr[i];
        arr[i] = arr[largestIndex];
        arr[largestIndex] = tmpV;

        // heapify the affected subtree
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

        heapify(arr, i, 0, compareFunction);
    }
}

#endif //HEAP_SORT_H


#pragma endregion

#pragma region quick sort 
#ifndef QUICK_SORT_H
#define QUICK_SORT_H

void quickSort(void* arr[], int n, CompareFunction compare);

void quickSortArrayList(ArrayList *list, CompareFunction compare);

int partition(void *arr[], int low, int high, CompareFunction compare)
{
    int pivotIdx = high;
    void *pivot = arr[pivotIdx];

    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        // current < pivot
        if (compare(arr[j], pivot) < 0)
        {
            i++;
            // swap
            void *tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    void *tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return i + 1;
}

void sortPartition(void *arr[], int low, int high, CompareFunction compare)
{
    if (low < high)
    {
        int pivotIdx = partition(arr, low, high, compare);

        sortPartition(arr, low, pivotIdx - 1, compare);
        sortPartition(arr, pivotIdx + 1, high, compare);
    }
}

void quickSort(void *arr[], int n, CompareFunction compare)
{
    sortPartition(arr, 0, n - 1, compare);
}

void quickSortArrayList(ArrayList *list, CompareFunction compare)
{
    quickSort(list->content, list->length, compare);
}


#endif //QUICK_SORT_H
#pragma endregion

#pragma region tree_define
#ifndef TREE_TYPE_H_
#define TREE_TYPE_H_

typedef struct tree_node {
    struct tree_node *left, *right, *top;
    void *data;
} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;

#endif // TREE_TYPE_H_
#pragma endregion

#pragma region tree
/**
 * In this implementation, left is the child, right is the next right sibling
 */

#ifndef TREE_H_
#define TREE_H_

/// <summary>
/// Make a node with data
/// </summary>
/// <param name="data">Content of the node, maybe id</param>
/// <returns>tree node with the data</returns>
TreeNode *treeCreateNode(void *data);

/// <summary>
/// Make a tree for easier tree contain than keeping root
/// </summary>
/// <param name="root">TreeNode representing root of the tree</param>
/// <returns>Tree</returns>
Tree *createTree(TreeNode *root);

/// <summary>
/// Find the first node with that has data match with data by func.
/// </summary>
/// <param name="data">sample data</param>
/// <param name="tree">the tree that need to search from</param>
/// <param name="func">how to compare 2 void pointer compare tree_node date with sample data</param>
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
        return 0;

    if (compare(node->data, data) == 0) {
        return current;
    } else {
        // find in right, sibling ->no increase
        long right = _treeNodeDepth(node->right, current, data, compare);
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


#pragma endregion

#pragma region b_tree
#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

/**
 * In this implementation, both left and right are the child
 */

/// <summary>
/// Make a node with data
/// </summary>
/// <param name="data">Content of the node, maybe id</param>
/// <returns>tree node with the data</returns>
TreeNode *bTreeCreateNode(void *data);

/// <summary>
/// Make a tree for easier tree contain than keeping root
/// </summary>
/// <param name="root">TreeNode representing root of the tree</param>
/// <returns>Tree</returns>
Tree *createBTree(TreeNode *root);

/// <summary>
/// Find the first node with that has data match with data by func.
/// </summary>
/// <param name="data">sample data</param>
/// <param name="tree">the tree that need to search from</param>
/// <param name="func">how to compare 2 void pointer compare tree_node date with sample data</param>
/// <returns>One node that match, NULL if none match</returns>
TreeNode *bTreeFindNode(void *data, Tree *tree, CompareFunction func);

void bTreePreOrder(Tree *t, Consume1 action);

void bTreeInOrder(Tree *t, Consume1 action);

void bTreePostOrder(Tree *t, Consume1 action);

long bTreeHeight(Tree *tree);

long bTreeNodeDepth(Tree *tree, void *data, CompareFunction compareFunction);


#endif // BINARY_TREE_H_

TreeNode *bTreeCreateNode(void *data) {
    quickCalloc(TreeNode, newNode);
    newNode->data = data;
    return newNode;
}

Tree *createBTree(TreeNode *root) {
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

#pragma endregion

//
// Created by tu on 25/12/2023.
//
/**
* Viết chương trình C thực hiện các công việc cài đặt một cây gia phả như sau
(1). Yêu cầu người dùng nhập vào N đại diện cho số người nam có trên cây gia phả.
(2). Yêu cầu nhập vào N dòng, mỗi dòng có định dạng sau: ID của cha, ID của người hiện tại, Tên người, số con trai của người đó đó, danh sách tên các người con cách nhau bởi dấu cách. Chú ý rằng trong cây gia phả này thì một người có thể có tên trùng với tổ tiên ở trên của họ. Nếu ID của cha bằng -1 thì nó ám chỉ người hiện tại đang là tổ tiên của cả dòng họ (trong cây gia phả thì đây là nút gốc)
(3) Biết rằng người ta quy ước thành viên đầu tiên trong cây gia phả là thuộc thế hệ số 0, chương trình cho phép người dùng nhập vào tên người và thế hệ của họ, chương trình phải in ra ra số lượng các thế hệ sau của họ mà có trùng tên với người đó. Giả sử không có ai cùng một thế hệ mà trùng tên nhau.
*/


const char *STRTOK_DELIM = " \n";

typedef struct {
    int id;
    char *name;
}Person;

int comparePersonWithId(void *pVoid, void *idVoid) {
    int id = *(int*) idVoid;
    Person *person = (Person*) pVoid;

    return person->id - id;
}


int comparePersonWithName(void *pVoid, void *nameVoid) {
    char *name = (char *)nameVoid;
    Person *person = (Person*) pVoid;

    return strcmp(person->name, name);
}

Person *createPerson() {
    Person *p = (Person*) malloc(sizeof(Person));
    p->id = -1;
    p->name = NULL;

    return p;
}

/**
 * Count amount of target in treeNode
 * @param treeNode
 * @param compare how to compare treeNode.data with target
 * @param target
 * @return amount of target in treeNode
 */
int countTarget(TreeNode *treeNode, CompareFunction compare, void *target) {
    if (treeNode == NULL) return 0;

    int count = 0;
    if (compare(treeNode->data, target) == 0) count += 1;
    count += countTarget(treeNode->left, compare, target);
    count += countTarget(treeNode->right, compare, target);
    return count;
}

int main () {
    char *line = (char*) malloc(1024);
    FILE *input = stdin;

    Tree *tree = createTree(NULL);

    int n;
    fgets(line, 1024, input);
    sscanf(line, "%d", &n);

    // read the first firstPerson
    Person *firstPerson = createPerson();

    fgets(line, 1024, input);
    n --;
    int firstParentId; // ignored, bc == -1
    sscanf(strtok(line, STRTOK_DELIM), "%d", &firstParentId);

    int firstId;
    sscanf(strtok(NULL, STRTOK_DELIM), "%d", &firstId);
    firstPerson->id = firstId;

    char *firstName = strdup(strtok(NULL, STRTOK_DELIM));
    firstPerson->name = firstName;

    TreeNode* firstNode = treeCreateNode(firstPerson);
    tree->root = firstNode;

    int firstChildCount;
    sscanf(strtok(NULL, STRTOK_DELIM), "%d", &firstChildCount);

    for (int j = 0; j < firstChildCount; j++) {
        char *childName = strdup(strtok(NULL, STRTOK_DELIM));
        Person *child = createPerson();
        child->name = childName;

        treeAddLastChild(firstNode, child);
    }


    // next gen
    for (int i = 0; i < n; i ++) {
        fgets(line, 1024, input);
        int fatherId;
        sscanf(strtok(line, STRTOK_DELIM), "%d", &fatherId);

        TreeNode *fatherNode = treeFindNode(&fatherId, tree, comparePersonWithId);

        int curId;
        sscanf(strtok(NULL, STRTOK_DELIM), "%d", &curId);

        char *name = strdup(strtok(NULL, STRTOK_DELIM));

        // find self, insert id by searchingName
        TreeNode *siblingNode = fatherNode->left;

        while (siblingNode) {
            Person *curPerson = (Person *) (siblingNode->data);
            if (strcmp(curPerson->name, name) == 0) {
                curPerson->id = curId;
                break;
            }
            siblingNode = siblingNode->right;
        }

        // insert child
        int childCount;
        sscanf(strtok(NULL, STRTOK_DELIM), "%d", &childCount);

        for (int j = 0; j < childCount; j++) {
            char *childName = strdup(strtok(NULL, STRTOK_DELIM));
            Person *child = createPerson();
            child->name = childName;

            treeAddLastChild(siblingNode, child);
        }

    }

    //////////////////// search father
    fgets(line, 1024, input);

    char *searchingName = strdup(strtok(line, STRTOK_DELIM));

    int searchingId;
    sscanf(strtok(NULL, STRTOK_DELIM), "%d", &searchingId);

    TreeNode *searchingNode = treeFindNode(&searchingId, tree, comparePersonWithId);

    if (comparePersonWithName(searchingNode->data, searchingName) != 0) {
        printf("0");
        return 0;
    }

    // search child
    int count = countTarget(searchingNode->left, comparePersonWithName, searchingName);

    printf("%d", count);
}
