#include "executor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

double evaluate_expression(const char* expr) {
    char left[50] = {0}, op[3] = {0}, right[50] = {0};
    
    if (sscanf(expr, "%49s %2s %49s", left, op, right) == 3) {
        double a = is_number(left) ? atof(left) : get_var(left);
        double b = is_number(right) ? atof(right) : get_var(right);
        
        if (strcmp(op, "+") == 0) return a + b;
        if (strcmp(op, "-") == 0) return a - b;
        if (strcmp(op, "*") == 0) return a * b;
        if (strcmp(op, "/") == 0) return b != 0 ? a / b : 0;
    }
    
    return is_number(expr) ? atof(expr) : get_var(expr);
}

void handle_assignment(const char* input) {
    char var[50] = {0};
    char expr[256] = {0};
    
    if (sscanf(input, "%49s = %255[^\n]", var, expr) != 2) {
        printf("Error: Invalid assignment syntax. Use: var = value\n");
        return;
    }
    
    if (!isalpha(var[0])) {
        printf("Error: Variable name must start with a letter\n");
        return;
    }
    
    double value = evaluate_expression(expr);
    set_var(var, value);
}

void handle_print(const char* input) {
    char value[256];
    if (sscanf(input, "print %255[^\n]", value) == 1) {
        if (value[0] == '"') {
            size_t len = strlen(value);
            if (value[len - 1] == '"') value[len - 1] = '\0';
            printf("%s\n", value + 1);
        }        
        else {
            double val = get_var(value);
            printf("%f\n", val);
        }
    } else {
        printf("Error: Invalid print statement\n");
    }
}

void handle_expression(const char* input) {
    char left[50] = {0}, op[3] = {0}, right[50] = {0};
    
    if (sscanf(input, "%49s %2s %49s", left, op, right) == 3) {
        double a = (isdigit(left[0]) || (left[0] == '-' && isdigit(left[1]))) 
                 ? atof(left) : get_var(left);
        double b = (isdigit(right[0]) || (right[0] == '-' && isdigit(right[1]))) 
                 ? atof(right) : get_var(right);
        
        double result = 0;
        if (strcmp(op, "+") == 0) result = a + b;
        else if (strcmp(op, "-") == 0) result = a - b;
        else if (strcmp(op, "*") == 0) result = a * b;
        else if (strcmp(op, "/") == 0) result = b != 0 ? a / b : 0;
        else {
            printf("Unknown operator: %s\n", op);
            return;
        }
        
        printf("%f\n", result);
    } else {
        printf("Invalid expression. Use: left op right\n");
    }
}

void handle_while_loop(const char* input) {
    const char* cond_start = strchr(input, '(');
    const char* cond_end = strchr(input, ')');
    if (!cond_start || !cond_end) {
        printf("Error: Missing parentheses in while condition\n");
        return;
    }
    
    char condition[256] = {0};
    strncpy(condition, cond_start + 1, cond_end - cond_start - 1);

    const char* cmd_start = strchr(input, '{');
    const char* cmd_end = strrchr(input, '}');
    if (!cmd_start || !cmd_end) {
        printf("Error: Missing braces in while body\n");
        return;
    }

    char commands[1024] = {0};
    strncpy(commands, cmd_start + 1, cmd_end - cmd_start - 1);

    char* end = commands + strlen(commands) - 1;
    while (end > commands && (*end == ' ' || *end == ';')) {
        *end = '\0';
        end--;
    }

    int iterations = 0;
    while (evaluate_condition(condition) && iterations < 1000) {        
        char* cmd = strtok(commands, ";");
        while (cmd) {
            while (*cmd == ' ') cmd++;
            
            if (*cmd) { 
                execute_command(cmd);
            }
            cmd = strtok(NULL, ";");
        }
        
        strncpy(commands, cmd_start + 1, cmd_end - cmd_start - 1);
        end = commands + strlen(commands) - 1;
        while (end > commands && (*end == ' ' || *end == ';')) {
            *end = '\0';
            end--;
        }
        
        iterations++;
    }

    if (iterations >= 1000) {
        printf("Warning: Maximum iterations (1000) reached\n");
    }
}

void handle_if_statement(const char* input) {
    const char* cond_start = strchr(input, '(');
    const char* cond_end = strchr(input, ')');

    if (!cond_start || !cond_end) {
        printf("Error: Missing parentheses in if condition\n");
        return;
    }

    char condition[256] = {0};
    strncpy(condition, cond_start + 1, cond_end - cond_start - 1);

    const char* body_start = strchr(input, '{');
    const char* body_end = strchr(body_start, '}');
    
    if (!body_start || !body_end) {
        printf("Error: Missing braces in if body\n");
        return;
    }

    char if_body[1024] = {0};
    strncpy(if_body, body_start + 1, body_end - body_start - 1);

    const char* else_ptr = strstr(body_end + 1, "else");
    char else_body[1024] = {0};

    if (else_ptr) {
        const char* else_body_start = strchr(else_ptr, '{');
        const char* else_body_end = strchr(else_body_start, '}');
        if (else_body_start && else_body_end) {
            strncpy(else_body, else_body_start + 1, else_body_end - else_body_start - 1);
        }
    }

    if (evaluate_condition(condition)) {
        char* cmd = strtok(if_body, ";");
        while (cmd) {
            while (*cmd == ' ') cmd++;
            if (*cmd) execute_command(cmd);
            cmd = strtok(NULL, ";");
        }
    } else if (else_ptr[0] != '\0') {
        char* cmd = strtok(else_body, ";");
        while (cmd) {
            while (*cmd == ' ') cmd++;
            if (*cmd) execute_command(cmd);
            cmd = strtok(NULL, ";");
        }
    }
}

void handle_for_loop(const char* input) {
    const char* cond_start = strchr(input, '(');
    const char* cond_end = strchr(input, ')');
    if (!cond_start || !cond_end) {
        printf("Error: Missing parentheses in for loop\n");
        return;
    }

    const char* body_start = strchr(input, '{');
    const char* body_end = strchr(body_start, '}');
    if (!body_start || !body_end) {
        printf("Error: Missing braces in for body\n");
        return;
    }

    char for_body[1024] = {0};
    strncpy(for_body, body_start + 1, body_end - body_start - 1);

    char cond_text[512] = {0};
    strncpy(cond_text, cond_start + 1, cond_end - cond_start - 1);

    char init[256] = {0}, condition[256] = {0}, increment[256] = {0};
    sscanf(cond_text, "%255[^;];%255[^;];%255[^\n]", init, condition, increment);

    execute_command(init);

    int guard = 0;
    while (evaluate_condition(condition) && guard < 1000) {
        char* cmd = strtok(for_body, ";");
        while (cmd) {
            while (*cmd == ' ') cmd++;
            if (*cmd) execute_command(cmd);
            cmd = strtok(NULL, ";");
        }

        execute_command(increment);

        strncpy(for_body, body_start + 1, body_end - body_start - 1);
        guard++;
    }

    if (guard >= 1000) {
        printf("Warning: Max for loop iterations reached.\n");
    }
}


void execute_command(const char* input) {
    while (*input == ' ') input++;
    
    if (strncmp(input, "while", 5) == 0) {
        handle_while_loop(input);
    }
    else if (strncmp(input, "for", 3) == 0) {
        handle_for_loop(input);
    }
    else if (strncmp(input, "print", 5) == 0) {
        handle_print(input);
    }
    else if (strncmp(input, "if", 2) == 0) {
        handle_if_statement(input);
    } 
    else if (strchr(input, '=')) {
        handle_assignment(input);
    }
    else {
        handle_expression(input);
    }
}
