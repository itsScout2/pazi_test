#include <stdio.h>
#include <stdlib.h>
#include "binomial.h"
#include "frequency.h"
#include "runs.h"
#include "lengths.h"


void generate_random_vector(int *vector, size_t length) {
    for (size_t i = 0; i < length; i++) {
        vector[i] = rand() % 2;
    }
}

int main() {
    size_t length;
    printf("Enter vector length (32, 64, 128): ");
    scanf("%zu", &length);

    if (length != 32 && length != 64 && length != 128) {
        printf("Error: acceptable lengths - 32, 64 or 128.\n");
        return 1;
    }

    int bits = 8 * length;

    int *vector = (int *)malloc(bits * sizeof(int));
    if (!vector) {
        printf("Memory allocation error.\n");
        return 1;
    }

    generate_random_vector(vector, bits);
    printf("Generated vector: ");
    for (size_t i = 0; i < bits; i++) {
        printf("%d", vector[i]);
    }
    printf("\n");

    double alpha;
    printf("Enter significance level alpha (e.g., 0.05): ");
    scanf("%lf", &alpha);

    size_t block_size;
    printf("Enter block size (2 for bigramm, 4 for quatergramm): ");
    scanf("%zu", &block_size);

    printf("\nStarting tests:\n");

    if (!binomial_test(vector, bits, alpha)) {
        printf("\nResult: the sequence is NOT random (Binomial test).\n");
        free(vector);
        return 0;
    }

    if (!frequency_test(vector, bits, block_size, alpha)) {
        printf("\nResult: the sequence is NOT random (Frequency test).\n");
        free(vector);
        return 0;
    }

    if (!runs_test(vector, bits, alpha)) {
        printf("\nResult: the sequence is NOT random (Runs test).\n");
        free(vector);
        return 0;
    }

    if (!lengths_test(vector, bits, alpha)) {
        printf("\nResult: the sequence is NOT random (Test for the longest length of ones in a block).\n");
        free(vector);
        return 0;
    }

        printf("\nResult: the sequence is random (all tests passed).\n");
    free(vector);
    return 0;
}
