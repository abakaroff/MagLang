#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "variables.h"

double evaluate_expression(const char* expr);

void handle_while_loop(const char* input);
void handle_for_loop(const char* input) ;
void handle_if_statement(const char* input);
void handle_print(const char* input);
void handle_assignment(const char* input);
void handle_expression(const char* input);
void execute_command(const char* input);

#endif
