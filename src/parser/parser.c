#include "parser.h"
#include <stdlib.h>

// Создает новый узел AST
ASTNode *create_node(Token token, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->token = token;
    node->left = left;
    node->right = right;
    return node;
}

// Парсит выражение (очень упрощенно)
ASTNode *parse_expression(Token *tokens, int start, int end) {
    if (start > end) return NULL;
    
    // Просто возвращаем первый токен как узел
    return create_node(tokens[start], NULL, NULL);
}