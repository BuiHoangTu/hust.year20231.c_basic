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
    FILE *input = fopen("./family_tree.txt", "r");

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