//
// Created by tu on 25/12/2023.
//
/**
* Viết chương trình C thực hiện các công việc cài đặt một cây gia phả như sau
(1). Yêu cầu người dùng nhập vào N đại diện cho số người nam có trên cây gia phả.
(2). Yêu cầu nhập vào N dòng, mỗi dòng có định dạng sau: ID của cha, ID của người hiện tại, Tên người, số con trai của người đó đó, danh sách tên các người con cách nhau bởi dấu cách. Chú ý rằng trong cây gia phả này thì một người có thể có tên trùng với tổ tiên ở trên của họ. Nếu ID của cha bằng -1 thì nó ám chỉ người hiện tại đang là tổ tiên của cả dòng họ (trong cây gia phả thì đây là nút gốc)
(3) Biết rằng người ta quy ước thành viên đầu tiên trong cây gia phả là thuộc thế hệ số 0, chương trình cho phép người dùng nhập vào tên người và thế hệ của họ, chương trình phải in ra ra số lượng các thế hệ sau của họ mà có trùng tên với người đó. Giả sử không có ai cùng một thế hệ mà trùng tên nhau.
*/

#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "tree/tree.h"
#include "array/array_list.h"

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

int countInTree(Tree *root) {

}

int main () {
    char *line = (char*) malloc(1024);

    Tree *tree = createTree(NULL);

    int n;
    fgets(line, 1024, stdin);
    sscanf(line, "%d", &n);

    // root
    Person *root = createPerson();

    fgets(line, 1024, stdin);
    int firstParentId;
    sscanf(strtok(line, " "), "%d", &firstParentId);
//    root->id = firstParentId;

    int firstId;
    sscanf(strtok(NULL, " "), "%d", &firstId);
    root->id = firstId;

    char *firstName = strdup(strtok(NULL, " "));
    root->name = firstName;

    TreeNode* firstNode = treeCreateNode(root);
    tree->root = firstNode;

    int firstChildCount;
    sscanf(strtok(NULL, " "), "%d", &firstChildCount);

    for (int j = 0; j < firstChildCount; j++) {
        char *childName = strdup(strtok(NULL, " "));
        Person *child = createPerson();
        child->name = childName;
        child->id = j;

        treeAddLastChild(firstNode, child);
    }


    // next gen
    for (int i = 0; i < n - 1; i ++) {
        fgets(line, 1024, stdin);
        int fatherId;
        sscanf(strtok(line, " "), "%d", &fatherId);

        TreeNode *fatherNode = treeFindNode(&fatherId, tree, comparePersonWithId);

        int curId;
        sscanf(strtok(NULL, " "), "%d", &curId);

        char *name = strdup(strtok(NULL, " "));

        // insert id by name
        TreeNode *childNode = fatherNode->left;
        while (childNode) {
            if (comparePersonWithName(childNode, name)) {
                ((Person*)(childNode->data))->id = curId;
            }
        }

        // insert child
        int childCount;
        sscanf(strtok(NULL, " "), "%d", &childCount);

        for (int j = 0; j < childCount; j++) {
            char *childName = strdup(strtok(NULL, " "));
            Person *child = createPerson();
            child->name = childName;
            child->id = j;

            treeAddLastChild(firstNode, child);
        }

    }

    // get search father
    fgets(line, 1024, stdin);

    char *name = strdup(strtok(line, " "));

    int curId;
    sscanf(strtok(NULL, " "), "%d", &curId);

    TreeNode *fatherNode = treeFindNode(&curId, tree, comparePersonWithId);


    TreeNode *childNode = fatherNode->left;
    while (childNode) {
        if (comparePersonWithName(childNode, name)) {
            ((Person*)(childNode->data))->id = curId;
        }
    }

}