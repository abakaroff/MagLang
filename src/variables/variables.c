#include "variables.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  

#define MAX_VARS 100
static Variable vars[MAX_VARS];
static int var_count = 0;

void init_vars(){
    var_count = 0;
}

void set_vars(const char* name, double value){
    for (int i = 0; i < var_count; i++){
        if (strcmp(vars[i].name, name) == 0){
            vars[i].value = value;
            return;
        }
    }
    if (var_count < MAX_VARS){
        strcpy(vars[var_count].name, name);
        vars[var_count].value = value;
        var_count++;
    }
    else{
        printf("Error");
    }
}

double get_var(const char* name){
    for (int i = 0; i < var_count; i++){
        if (strcmp(vars[i].name, name)){
            return vars[i].value;
        }
    }
    return 0;
}

void print_all_vars() {
    for (int i = 0; i < var_count; i++) {
        printf("%s = %f\n", vars[i].name, vars[i].value);
    }
}

int evaluate_condition(const char* condition) {    
    char var1[50] = {0}, op[3] = {0}, var2[50] = {0};
    if (sscanf(condition, "%49s %2s %49s", var1, op, var2) != 3) {
        printf("Error: Condition must be in format 'var op var'\n");
        return 0;
    }

    double val1 = is_number(var1) ? atof(var1) : get_var(var1);
    double val2 = is_number(var2) ? atof(var2) : get_var(var2);
    
    if (strcmp(op, "<") == 0) return val1 < val2;
    if (strcmp(op, ">") == 0) return val1 > val2;
    if (strcmp(op, "<=") == 0) return val1 <= val2;
    if (strcmp(op, ">=") == 0) return val1 >= val2;
    if (strcmp(op, "==") == 0) return val1 == val2;
    if (strcmp(op, "!=") == 0) return val1 != val2;

    printf("Error: Unknown operator '%s'\n", op);
    return 0;
}

bool is_number(const char* s) {
    if (*s == '-') s++;
    while (*s) {
        if (!isdigit(*s) && *s != '.') return false;
        s++;
    }
    return true;
}
