//
// Created by tu on 25/12/2023.
//

#include "stdio.h"

int main() {
    int n;
    scanf("%d", &n);


    int odd = 0, even = 0, cur;
    for (int i = 0; i < n; i++) {
        scanf("%d", &cur);
        if (cur % 2 == 0) even ++;
        else odd ++;
    }

    printf("%d %d", odd, even);
}