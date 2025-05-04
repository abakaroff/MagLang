#pragma once

// Типы токенов
typedef enum {
    TOKEN_NUMBER,    // Числа (42, 3.14)
    TOKEN_VARIABLE,  // Переменные (x, count)
    TOKEN_OPERATOR,  // Операторы (+, -, *, /, =)
    TOKEN_KEYWORD,   // Ключевые слова (if, else, print)
    TOKEN_STRING,    // Строки в кавычках
    TOKEN_EOF        // Конец ввода
} TokenType;

// Структура токена
typedef struct {
    TokenType type;
    char value[32]; // Значение токена
} Token;

// Функция разбиения строки на токены
void tokenize(const char *input, Token *tokens, int *count);
