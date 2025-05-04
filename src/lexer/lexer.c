#include "lexer.h"
#include <ctype.h>
#include <string.h>

// Проверка, является ли слово ключевым
static int is_keyword(const char *word) {
    if (strcmp(word, "if") == 0) return 1;
    if (strcmp(word, "else") == 0) return 1;
    if (strcmp(word, "print") == 0) return 1;
    return 0;
}

// Разбивает входную строку на токены
void tokenize(const char *input, Token *tokens, int *count) {
    const char *p = input;
    *count = 0;
    
    // Пропускаем пробелы
    while (*p == ' ') p++;
    
    // Обрабатываем числа
    if (isdigit(*p)) {
        int i = 0;
        while (isdigit(*p) || *p == '.') {
            tokens[*count].value[i++] = *p++;
        }
        tokens[*count].value[i] = '\0';
        tokens[*count].type = TOKEN_NUMBER;
        (*count)++;
        return;
    }
    
    // Обрабатываем строки
    if (*p == '"') {
        p++;
        int i = 0;
        while (*p != '"' && *p) {
            tokens[*count].value[i++] = *p++;
        }
        tokens[*count].value[i] = '\0';
        tokens[*count].type = TOKEN_STRING;
        (*count)++;
        if (*p == '"') p++;
        return;
    }
    
    // Обрабатываем операторы
    if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '=') {
        tokens[*count].value[0] = *p++;
        tokens[*count].value[1] = '\0';
        tokens[*count].type = TOKEN_OPERATOR;
        (*count)++;
        return;
    }
    
    // Обрабатываем переменные и ключевые слова
    if (isalpha(*p)) {
        int i = 0;
        while (isalnum(*p)) {
            tokens[*count].value[i++] = *p++;
        }
        tokens[*count].value[i] = '\0';
        tokens[*count].type = is_keyword(tokens[*count].value) ? TOKEN_KEYWORD : TOKEN_VARIABLE;
        (*count)++;
        return;
    }
    
    // Если ничего не распознано
    tokens[*count].type = TOKEN_EOF;
}