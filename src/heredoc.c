//#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void process_heredoc(const char *filename, const char *delimiter)
{
	FILE *file = fopen(filename, "r");
	char line[MAX_LINE_LENGTH];

	if (!file) {
		perror("Erro ao abrir o ficheiro");
		exit(EXIT_FAILURE);
	}

	printf("Início do Heredoc (Delimitador: %s):\n", delimiter);

	while (fgets(line, sizeof(line), file)) {
		// Remove o '\n' do final da linha
		line[strcspn(line, "\n")] = '\0';

		// Se encontrar o delimitador, para de ler
		if (strcmp(line, delimiter) == 0) {
			printf("Fim do Heredoc (Delimitador encontrado).\n");
			break;
		}

		// Caso contrário, processa a linha
		printf("Linha processada: %s\n", line);
	}

	fclose(file);
}

int main(int argc, char **argv) 
{
	const char *filename;
	const char *delimiter;

	if (argc != 3) {
		fprintf(stderr, "Uso: %s <nome_do_ficheiro> <delimitador>\n", argv[0]);
		return EXIT_FAILURE;
	}

	filename = argv[1];
	delimiter = argv[2];

	process_heredoc(filename, delimiter);

	return EXIT_SUCCESS;
}

