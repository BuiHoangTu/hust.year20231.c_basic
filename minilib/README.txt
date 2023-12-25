# MINI_LIB
The extended data type structure for vanilla C language
**Disclaimer:** This code is for learning purpose, using with prudence in production. Owner does *NOT*
guarantee the quality of this code.
## Naming convention
CamelCase
1. Type
Any new type should be treated as reference type. Ex: NewType, HashMap, ...
Long type can be shortened. Ex: SingleLinkedList -> Sll, ...
2. Function
Functions of mini_lib usually support a new type. Thus, their names should indicate the associate type.
Ex: newTypeAction, hashMapPut, ...

There are 2 name types of function actionType, typeAction.
    1. If Type is the main type (HashMap, SLL) and function return that type,
    we use actionType. Ex: createHashMap, configType, ...
    1. If return type is subtype (SingleLinkedNode), we use mainTypeActionSubtype.
    Ex: sllCreateNode, ...
    1. If function does kind of search in DataType, we use actionMainType.
    Ex: hashMapGet
3. File
Type and function declaration should be grouped in my_type.h and function description should
be in my_type.c