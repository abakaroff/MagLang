#pragma once
#include "lexer.h"

typedef struct ASTNode {
    Token token;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode **body;
    int body_count;
    struct ASTNode **else_body;
    int else_body_count;
} ASTNode;

ASTNode *parse_expression(Token *tokens, int start, int end);
ASTNode *parse_if(Token *tokens, int *pos);
ASTNode *parse_while(Token *tokens, int *pos);
ASTNode *parse_for(Token *tokens, int *pos);
