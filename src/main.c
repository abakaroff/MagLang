#include <stdio.h>
#include <string.h>
#include "variables/variables.h"
#include "executor/executor.h"

#define MAX_INPUT 1024

// Основная функция интерпретатора
int main() {
    init_vars(); // Инициализация переменных
    char input[MAX_INPUT];
    
    printf("Simple Interpreter. Type 'exit' to quit.\n");
    
    // Главный цикл REPL (Read-Eval-Print Loop)
    while (1) {
        printf("> ");
        if (!fgets(input, MAX_INPUT, stdin)) break;
        
        // Удаляем символ новой строки
        char *pos = strchr(input, '\n');
        if (pos) *pos = '\0';
        
        if (strcmp(input, "exit") == 0) break;
        if (strlen(input) == 0) continue;
        
        execute_command(input); // Выполняем команду
    }
    
    return 0;
}
