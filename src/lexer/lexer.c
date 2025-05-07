#include "lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool in_keyword(const char *word){
    const char *keywords[] = {
        "if", "else", "for",
        "while", "print"
    };
    for (int i = 0; i < 5; i++){
        if (strcmp(word, keywords[i]) == 0) return true;
    }
    return false;
}

void tokensize(const char *input, Token *tokens, int *token_count){
    const char *p = input;
    *token_count = 0;

    while (*p){
        if (isspace(*p)){
            p++;
            continue;
        }

        // числа
        if (isdigit(*p)){
            int i = 0;
            while (isdigit(*p) || *p == "."){
                tokens[*token_count].value[i++] = *p++;
            }
            tokens[*token_count].value[i] = "\0";
            tokens[*token_count].type = TOKEN_NUMBER;
            (*token_count)++;
            continue;
        }
        // строки для print
        if (*p == '"'){
            p++;
            int i = 0;

            while (*p != '"' && *p){
                tokens[*token_count].value[i++] = *p++;
            }
            tokens[*token_count].value[i] = '\0';
            tokens[*token_count].type = TOKEN_STRING;
            (*token_count)++;
            if (*p == '"') p++;
            continue;
        }

        // операторы и скобки
        if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '=' || 
            *p == '{' || *p == '}' || *p == '(' || *p == ')' || *p == ';') {
            tokens[*token_count].value[0] = *p;
            tokens[*token_count].value[1] = '\0';
            tokens[*token_count].type = 
                (*p == '{') ? TOKEN_LBRACE :
                (*p == '}') ? TOKEN_RBRACE :
                (*p == '(') ? TOKEN_LPAREN :
                (*p == ')') ? TOKEN_RPAREN :
                (*p == ';') ? TOKEN_SEMICOLON :
                TOKEN_OPERATOR;
            (*token_count)++;
            p++;
            continue;
        }

        // ключевые слова и переменные
        if (isalpha(*p)) {
            int i = 0;
            while (isalnum(*p)) tokens[*token_count].value[i++] = *p++;
            tokens[*token_count].value[i] = '\0';
            tokens[*token_count].type = is_keyword(tokens[*token_count].value) ? TOKEN_KEYWORD : TOKEN_VARIABLE;
            (*token_count)++;
            continue;
        }
        p++;
    }
    tokens[*token_count].type = TOKEN_EOF;
}
