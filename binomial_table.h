#ifndef BINOMIAL_TABLE_H
#define BINOMIAL_TABLE_H

#include <stddef.h>

typedef struct {
    double alpha;
    double critical_value;
} CriticalValue;

double get_binomial_critical_value(double alpha);

#endif