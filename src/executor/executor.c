#include "executor.h"
#include "../variables/variables.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Обрабатывает присваивание (x = 10)
static void handle_assignment(const char* input) {
    char name[32];
    char expr[256];
    
    if (sscanf(input, "%31s = %255[^\n]", name, expr) == 2) {
        double val = evaluate_expr(expr);
        set_var(name, val);
    } else {
        printf("Invalid assignment\n");
    }
}

// Обрабатывает команду print
static void handle_print(const char* input) {
    char arg[256];
    if (sscanf(input, "print %255[^\n]", arg) == 1) {
        if (arg[0] == '"') {
            // Вывод строки
            printf("%s\n", arg + 1);
        } else {
            // Вывод значения переменной
            printf("%f\n", get_var(arg));
        }
    }
}

// Вычисляет значение выражения
double evaluate_expr(const char* expr) {
    // Очень упрощенное вычисление
    if (is_number(expr)) {
        return atof(expr);
    }
    return get_var(expr);
}

// Выполняет команду
void execute_command(const char* input) {
    if (strncmp(input, "print", 5) == 0) {
        handle_print(input);
    } 
    else if (strchr(input, '=')) {
        handle_assignment(input);
    }
    else {
        printf("Unknown command\n");
    }
}