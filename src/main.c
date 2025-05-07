#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "variables/variables.h"
#include "executor/executor.h"

#define MAX_INPUT 1024

int main(){
    init_vars();
    char input[MAX_INPUT];

    printf("Simple C Interpreter. Type 'exit' to quit.\n");

    while (1){
        printf("> ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT, stdin)) break;
        input[strcspn(input, "\n")] = "\0";

        if (strcmp(input, "exit") == 0) break;
        if (strlen(input) == 0) continue;

        execute_command(input);
    }
    return 0;
}
