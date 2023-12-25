//
// Created by tu on 25/12/2023.
//

#include "stdio.h"
#include "map/hash_map.h"
#include "core/hash.h"

#define DATA 1
#define CMD 2


int hashStr(char* str) {
    return hashString(str);
}

int main() {
    char *line = (char*)malloc(1024);
    HashMap *map = createHashmap((HashFunction) hashStr, (CompareFunction) strcmp);

    int mode = DATA;

    while (1) {
        fgets(line, 1024, stdin);

        if (mode == DATA) {
            if (strncmp(line, "*", 1) == 0) {
                mode = CMD;
                continue;
            }

            char *key = strndup(line, strlen(line) + 2);
            hashmapPut(map, key, key);

        } else {
            if (strncmp(line, "***", 3) == 0) {
                break;
            }

            char *cmd = strtok(line, " ");
            char *rest = strtok(NULL, " ");

            char *key = strndup(rest, strlen(rest));
            void *val = hashmapGet(map, key);

            if (strncmp(cmd, "find", 4) == 0) {
                if (val) printf("1\n");
                else printf("0\n");

                free(key);
                continue;
            }

            if (strncmp(cmd, "insert", 5) == 0) {
                if (val) printf("0\n");
                else {
                    printf("1\n");
                    hashmapPut(map, key, key);
                }
                continue;
            }
        }
    }
}