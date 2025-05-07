#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>
bool is_number(const char* s);

typedef struct {
    char name[50];
    double value;
} Variable;

void init_vars();
void set_var(const char* name, double value);
double get_var(const char* name);
void print_all_vars();
int evaluate_condition(const char* condition);

#endif
