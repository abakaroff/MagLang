#ifndef VARIABLES_H
#define VARIABLES_H

// Инициализация системы переменных
void init_vars();

// Установка значения переменной
void set_var(const char* name, double value);

// Получение значения переменной
double get_var(const char* name);

// Проверка, является ли строка числом
int is_number(const char* s);

#endif
