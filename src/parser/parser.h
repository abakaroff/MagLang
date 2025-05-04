#pragma once
#include "../lexer/lexer.h"

// Узел абстрактного синтаксического дерева (AST)
typedef struct ASTNode {
    Token token;       // Токен узла
    struct ASTNode *left;  // Левый потомок
    struct ASTNode *right; // Правый потомок
} ASTNode;

// Создает новый узел AST
ASTNode *create_node(Token token, ASTNode *left, ASTNode *right);

// Парсит выражение
ASTNode *parse_expression(Token *tokens, int start, int end);
