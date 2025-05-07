#pragma once

typedef enum {
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_OPERATOR,   // +, -, *, /, =
    TOKEN_KEYWORD,    // if, else, for, while, print
    TOKEN_STRING,     // "текст"
    TOKEN_LBRACE,     // {
    TOKEN_RBRACE,     // }
    TOKEN_LPAREN,     // (
    TOKEN_RPAREN,     // )
    TOKEN_SEMICOLON,  // ;
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[50];
} Token;

void tokenize(const char *input, Token *tokens, int *token_count);
