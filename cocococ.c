#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <comando1> [<comando2> ... <comandoN>]\n", argv[0]);
        return 1;
    }

    int pipe_fd[2];
    int prev_fd = -1; // Descriptor do pipe anterior

    for (int i = 1; i < argc; i++) {
        if (i != argc - 1) { // Não é o último comando, cria um novo pipe
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                return 1;
            }
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            // Processo filho
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO); // Redireciona a entrada padrão do pipe anterior
                close(prev_fd);
            }

            if (i != argc - 1) {
                close(pipe_fd[0]); // Fecha a leitura do pipe atual
                dup2(pipe_fd[1], STDOUT_FILENO); // Redireciona a saída padrão para o pipe atual
                close(pipe_fd[1]);
            }

            execlp(argv[i], argv[i], NULL);
            perror("execlp"); // Só ocorre se execlp falhar
            exit(1);
        }

        // Processo pai
        if (prev_fd != -1) {
            close(prev_fd); // Fecha o pipe anterior
        }

        if (i != argc - 1) {
            close(pipe_fd[1]); // Fecha a escrita do pipe atual no processo pai
            prev_fd = pipe_fd[0]; // Atualiza o descritor para o próximo comando
        }
    }

    // Processo pai espera todos os filhos
    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }

    return 0;
}
