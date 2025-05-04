#include "variables.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_VARS 50

// Структура для хранения переменной
typedef struct {
    char name[32];
    double value;
} Variable;

static Variable vars[MAX_VARS];
static int var_count = 0;

// Инициализация переменных
void init_vars() {
    var_count = 0;
}

// Установка значения переменной
void set_var(const char* name, double value) {
    // Проверяем, есть ли уже такая переменная
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].value = value;
            return;
        }
    }
    
    // Добавляем новую переменную
    if (var_count < MAX_VARS) {
        strcpy(vars[var_count].name, name);
        vars[var_count].value = value;
        var_count++;
    } else {
        printf("Too many variables!\n");
    }
}

// Получение значения переменной
double get_var(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return vars[i].value;
        }
    }
    return 0.0; // Возвращаем 0, если переменная не найдена
}

// Проверка, является ли строка числом
int is_number(const char* s) {
    if (*s == '-') s++;
    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}