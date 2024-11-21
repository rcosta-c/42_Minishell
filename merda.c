#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    input = readline("Enter text: ");
    if (input) {
        // Process the input
        printf("You entered: %s\n", input);
        free(input); // Free the memory allocated by readline
    } else {
        printf("Error reading input.\n");
    }
	rl_clear_history();
    return 0;
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *a;

    a = readline("merda: ");
    if (a == NULL) {
        printf("Erro ao ler a entrada ou EOF encontrado.\n");
        return 1; // Retorna um código de erro
    }

    printf("Você digitou: %s\n", a);
    free(a); // Libera a memória alocada por readline
    return 0;
}*/
