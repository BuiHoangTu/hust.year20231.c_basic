#include <stdio.h>
#include <string.h>

// Function to generate and count binary sequences
int generateAndCountBinarySequences(char sequence[], int length, int currentIndex, char forbiddenSequence[], int forbiddenLength) {
    if (currentIndex == length) {
        // Check if the generated sequence contains the forbidden sequence
        if (strstr(sequence, forbiddenSequence) == NULL) {
            return 1; // Return 1 to indicate one valid sequence has been generated
        } else {
            return 0; // Return 0 to indicate the sequence is not valid
        }
    }

    int totalCount = 0;

    // Generate sequences with '0' and '1' at the current index
    sequence[currentIndex] = '0';
    totalCount += generateAndCountBinarySequences(sequence, length, currentIndex + 1, forbiddenSequence, forbiddenLength);

    sequence[currentIndex] = '1';
    totalCount += generateAndCountBinarySequences(sequence, length, currentIndex + 1, forbiddenSequence, forbiddenLength);

    return totalCount;
}

int main() {
    // Read input value for sequence length
    int x;
    scanf("%d", &x);

    // Check if the input length is valid
    if (x < 1 || x > 20) {
        return 1; // Exit with an error code
    }

    // Read input for the forbidden sequence
    char forbiddenSequence[6];
    scanf("%5s", forbiddenSequence);

    // Create an array to store the generated binary sequence
    char binarySequence[21]; // Assuming the maximum length is 20

    // Generate and count binary sequences
    int totalCount = generateAndCountBinarySequences(binarySequence, x, 0, forbiddenSequence, strlen(forbiddenSequence));

    // Print the total count
    printf("%d\n", totalCount);

    return 0;
}
