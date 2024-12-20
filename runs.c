#include "runs.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Функция для подсчета серий
int count_runs(const int *vector, size_t length) {
    int runs = 1;
    for (size_t i = 1; i < length; i++) {
        if (vector[i] != vector[i - 1]) {
            runs++;
        }
    }
    return runs;
}

// Вычисление p-value с использованием erfc
double calculate_p_value(int runs, size_t length, double pi) {
    double expected_runs = 2 * length * pi * (1 - pi);
    double denominator = 2 * sqrt(2 * length * pi * (1 - pi));

    double p_value = erfc(fabs(runs - expected_runs) / denominator);
    return p_value;
}

// Основная функция Runs теста
int runs_test(const int *vector, size_t length, double alpha) {
    int n1 = 0;
    for (size_t i = 0; i < length; i++) {
        if (vector[i] == 1) n1++;
    }

    double pi = (double)n1 / length;

    // Проверка пропорции
    if (fabs(pi - 0.5) > (2 / sqrt(length))) {
        printf("Провал теста пропорции: pi = %.5f\n", pi);
        return 0; // Не случайна
    }

    // Подсчет количества серий
    int runs = count_runs(vector, length);

    // Вычисление p-value
    double p_value = calculate_p_value(runs, length, pi);

    printf("Runs: %d, p-value: %.10f\n", runs, p_value);

    if (p_value < alpha) {
        return 0; // Не случайна
    }
    return 1; // Случайна
}
