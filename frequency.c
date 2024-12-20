#include "frequency.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Гамма-функция Эйлера (аппроксимация через формулу Стирлинга)
double gamma_function(double a) {
    return sqrt(2 * M_PI / a) * pow(a / M_E, a);
}

// Неполная верхняя гамма-функция Q(a, x)
double upper_incomplete_gamma(double a, double x) {
    double sum = 0.0, term = 1.0 / a;
    double t = x;

    // Рекурсивное вычисление интегральной части
    for (int k = 0; k < 100; k++) { // Итерационный предел для точности
        sum += term;
        term *= t / (a + k + 1);
    }

    return exp(-x) * pow(x, a) * sum / gamma_function(a);
}

// p-value на основе неполной гамма-функции
double chi_square_p_value(double chi_squared, int degrees_of_freedom) {
    double a = degrees_of_freedom / 2.0;
    double x = chi_squared / 2.0;
    return upper_incomplete_gamma(a, x);
}

int frequency_test(const int *vector, size_t length, size_t block_size, double alpha) {
    if (length < block_size) {
        printf("Error: the sequence length is less than the block size.\n");
        return 0;
    }

    size_t num_blocks = length / block_size;
    double chi_squared = 0.0;

    for (size_t i = 0; i < num_blocks; i++) {
        int ones_count = 0;
        for (size_t j = 0; j < block_size; j++) {
            ones_count += vector[i * block_size + j];
        }
        double pi_i = (double)ones_count / block_size;
        chi_squared += pow(pi_i - 0.5, 2);
    }

    chi_squared *= 4 * block_size;
    double p_value = chi_square_p_value(chi_squared, num_blocks - 1);

    printf("Frequency Test (NIST):\n");
    printf("  Chi-square statistics: %.3f\n", chi_squared);
    printf("  P-value: %.6f\n", p_value);
    printf("  Significance level: %.3f\n", alpha);

    if (p_value < alpha) {
        printf("  Result: the sequence is NOT random\n");
        return 0;
    } else {
        printf("  Result: the sequence is random\n");
        return 1;
    }
}
