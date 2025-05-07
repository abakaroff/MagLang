#include "parser.h"
#include <stdlib.h>
#include <string.h>

ASTNode *create_node(Token token, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->token = token;
    node->left = left;
    node->right = right;
    node->body = NULL;
    node->body_count = 0;
    node->else_body = NULL;
    node->else_body_count = 0;
    return node;
}

ASTNode *parse_expression(Token *tokens, int start, int end) {
    if (start > end) return NULL;

    for (int i = end; i >= start; i--) {
        if (tokens[i].type == TOKEN_OPERATOR) {
            ASTNode *left = parse_expression(tokens, start, i - 1);
            ASTNode *right = parse_expression(tokens, i + 1, end);
            return create_node(tokens[i], left, right);
        }
    }

    return create_node(tokens[start], NULL, NULL);
}

ASTNode **parse_block(Token *tokens, int *pos, int *stmt_count) {
    ASTNode **stmts = malloc(sizeof(ASTNode*) * 100);
    *stmt_count = 0;

    while (tokens[*pos].type != TOKEN_RBRACE && tokens[*pos].type != TOKEN_EOF) {
        if (tokens[*pos].type == TOKEN_KEYWORD && strcmp(tokens[*pos].value, "if") == 0) {
            stmts[*stmt_count] = parse_if(tokens, pos);
        } else if (tokens[*pos].type == TOKEN_KEYWORD && strcmp(tokens[*pos].value, "while") == 0) {
            stmts[*stmt_count] = parse_while(tokens, pos);
        } else {
            int expr_start = *pos;
            while (tokens[*pos].type != TOKEN_SEMICOLON && tokens[*pos].type != TOKEN_EOF)
                (*pos)++;
            stmts[*stmt_count] = parse_expression(tokens, expr_start, *pos - 1);
            if (tokens[*pos].type == TOKEN_SEMICOLON) (*pos)++;
        }
        (*stmt_count)++;
    }

    if (tokens[*pos].type == TOKEN_RBRACE) (*pos)++;
    return stmts;
}
