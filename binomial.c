#include "binomial.h"
#include "binomial_table.h"
#include <stdio.h>


double binomial_test(int *sequence, size_t length, double alpha) {
    int ones = 0;
    for (size_t i = 0; i < length; i++) {
        if (sequence[i] == 1) ones++;
    }

    double p = 0.5;
    double expected = length * p;
    double chi_square = ((ones - expected) * (ones - expected)) / expected +
                        ((length - ones - expected) * (length - ones - expected)) / expected;

    double critical_value = get_binomial_critical_value(alpha);

    printf("Binomial test:\n");
    printf("  Chi-square statistics: %.4f\n", chi_square);
    printf("  Critical value for alpha=%.4f: %.4f\n", alpha, critical_value);

    if (chi_square > critical_value) {
        printf("  Result: the sequence is NOT random\n");
        return 0;
    }

    printf("  Result: the sequence is random\n");
    return 1;
}

