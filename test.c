#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *line;
    while (1) {
        line = readline("prompt >> ");
        printf("%s\n", line);
    }
}




