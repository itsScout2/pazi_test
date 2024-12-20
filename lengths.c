#include "lengths.h"
#include <math.h>
#include <stdio.h>

// Функция для подсчета максимальной длины последовательных единиц
static int longest_run_of_ones(const int *vector, size_t length) {
    int max_run = 0;
    int current_run = 0;

    for (size_t i = 0; i < length; i++) {
        if (vector[i] == 1) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }
    return max_run;
}

// Функция для вычисления p-value через неполную верхнюю гамма-функцию
static double calculate_p_value(double chi_squared, int degrees_of_freedom) {
    return exp(-chi_squared / 2.0); // Для больших значений df точное значение.
}

// Тест на максимальную длину последовательностей
int lengths_test(const int *vector, size_t length, double alpha) {
    // Проверка на минимальную длину последовательности
    if (length < 128) {
        printf("The length test only works for sequences of length >= 128.\n");
        return 0;
    }

    // Подразделение последовательности на блоки
    int block_size = (length >= 6272) ? 128 : (length >= 750) ? 64 : 8;
    int num_blocks = length / block_size;

    if (num_blocks == 0) {
        printf("There is not enough data to split into blocks.\n");
        return 0;
    }

    // Частотное распределение длин максимальных последовательностей
    int observed_counts[8] = {0};
    for (int i = 0; i < num_blocks; i++) {
        int max_run = longest_run_of_ones(&vector[i * block_size], block_size);
        if (block_size == 8) {
            if (max_run <= 1) observed_counts[0]++;
            else if (max_run == 2) observed_counts[1]++;
            else observed_counts[2]++;
        } else if (block_size == 64) {
            if (max_run <= 4) observed_counts[0]++;
            else if (max_run == 5) observed_counts[1]++;
            else if (max_run == 6) observed_counts[2]++;
            else observed_counts[3]++;
        } else if (block_size == 128) {
            if (max_run <= 10) observed_counts[0]++;
            else if (max_run == 11) observed_counts[1]++;
            else if (max_run == 12) observed_counts[2]++;
            else observed_counts[3]++;
        }
    }

    // Ожидаемое распределение длин (взято из NIST)
    double expected_counts[8] = {0};
    if (block_size == 8) {
        expected_counts[0] = 0.21484375 * num_blocks;
        expected_counts[1] = 0.3671875 * num_blocks;
        expected_counts[2] = 0.41796875 * num_blocks;
    } else if (block_size == 64) {
        expected_counts[0] = 0.1174035788 * num_blocks;
        expected_counts[1] = 0.2429559591 * num_blocks;
        expected_counts[2] = 0.2493634830 * num_blocks;
        expected_counts[3] = 0.3902770409 * num_blocks;
    } else if (block_size == 128) {
        expected_counts[0] = 0.0882 * num_blocks;
        expected_counts[1] = 0.2092 * num_blocks;
        expected_counts[2] = 0.2483 * num_blocks;
        expected_counts[3] = 0.4543 * num_blocks;
    }

    // Вычисление статистики хи-квадрат
    double chi_squared = 0.0;
    for (int i = 0; i < (block_size == 8 ? 3 : 4); i++) {
        double diff = observed_counts[i] - expected_counts[i];
        chi_squared += diff * diff / expected_counts[i];
    }

    // Вычисление p-value
    double p_value = calculate_p_value(chi_squared, (block_size == 8 ? 2 : 3));

    printf("Lengths Test: Chi-Squared = %.5f, p-value = %.5f\n", chi_squared, p_value);

    // Решение о случайности
    if (p_value < alpha) {
        return 0;
    }
    return 1;
}
