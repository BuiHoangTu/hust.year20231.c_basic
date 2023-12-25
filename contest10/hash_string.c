//
// Created by tu on 25/12/2023.
//
#include "stdio.h"
#include "string.h"


int calculateHashCode(char s[], int k, int m) {
    int hash = 0;

    // Iterate through the characters of the string
    for (int i = 0; i < k; i++) {
        // Update the hash using the ASCII value of the character and the power term (256^(k-i-1))
        hash = (hash * 256 + s[i]) % m;
    }

    return hash;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i ++) {
        char s[1000];
        scanf("%s", s);
        int k = strlen(s);
        int hashCode = calculateHashCode(s, k, m);
        printf("%d\n", hashCode);

    }

    return 0;
}