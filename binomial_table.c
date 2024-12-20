#include "binomial_table.h"

static CriticalValue critical_values[] = {
    {0.10, 2.705},
    {0.05, 3.841},
    {0.025, 5.024},
    {0.01, 6.635},
    {0.005, 7.879},
    {0.001, 10.828},
    {0.0005, 12.116},
    {0.0001, 15.137},
};

double get_binomial_critical_value(double alpha) {
    size_t size = sizeof(critical_values) / sizeof(CriticalValue);
    for (size_t i = 0; i < size; i++) {
        if (critical_values[i].alpha == alpha) {
            return critical_values[i].critical_value;
        }
    }

    return -1.0;
}
