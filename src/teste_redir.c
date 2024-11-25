#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void execute_echo_with_redirect(char *cmd, char *input_file, char *output_file, char **echo_args, char **envp) {
    int input_fd = -1;
    int output_fd = -1;
    int stdin_backup = -1;
    int stdout_backup = -1;

    // Se houver ficheiro de entrada, redireciona stdin
    if (input_file != NULL) 
    {
        printf("vai abrir o fd\n\n");
        input_fd = open(input_file, O_RDONLY);
        if (input_fd < 0) {
            perror("Erro ao abrir ficheiro de entrada");
            return;
        }
        // Guarda o stdin original e redireciona
        stdin_backup = dup(STDIN_FILENO);
        if (dup2(input_fd, STDIN_FILENO) < 0) {
            perror("Erro ao redirecionar stdin");
            close(input_fd);
                    printf("vai guardar o original e redir\n\n");

            return;
        }
        close(input_fd);
    }

    // Se houver ficheiro de saída, redireciona stdout
    if (output_file != NULL) {
            printf("vai redir o out \n\n");

        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd < 0) {
            perror("Erro ao abrir ficheiro de saída");
            return;
        }
        // Guarda o stdout original e redireciona
        stdout_backup = dup(STDOUT_FILENO);
        if (dup2(output_fd, STDOUT_FILENO) < 0) {
            perror("Erro ao redirecionar stdout");
            close(output_fd);
            return;
        }
        close(output_fd);
    }

    // Executa o comando echo com os argumentos fornecidos
    if (fork() == 0) 
    {
        printf("vai executar exevp\n\n");
        if (execve(cmd, echo_args, envp) == -1) {

           perror("Erro ao executar echo");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);  // Espera pelo término do processo filho
    }

    // Restaurar stdin se foi redirecionado
    if (stdin_backup != -1) {
        dup2(stdin_backup, STDIN_FILENO);
        close(stdin_backup);
    }

    // Restaurar stdout se foi redirecionado
    if (stdout_backup != -1) {
        dup2(stdout_backup, STDOUT_FILENO);
        close(stdout_backup);
    }
}

int main(int argc, char *argv[], char **envp) {
    char *input_file = NULL;
    char *output_file = NULL;
    char *echo_args[argc];
    int x;
    char    *cmd;
    // Processa argumentos para determinar ficheiros de redirecionamento
    int echo_arg_index = 0;
    
    x = 0;
    while(x < argc)
    {
        printf("%d=%s\n", x, argv[x]);
        x++;
    }

    printf("00=%s\n", argv[0]);    
    printf("01=%s\n", argv[1]);    
    printf("02=%s\n", argv[2]);    
    printf("03=%s\n", argv[3]);    

    output_file = argv[3];  // Ficheiro de entrada
    //input_file[1] = '\0';
    cmd = argv[1];
    

    
    echo_args[echo_arg_index] = NULL;  // Terminar a lista de argumentos com NULL

    // Executa o comando echo com redirecionamentos
    execute_echo_with_redirect(cmd, input_file, output_file, echo_args, envp);

    return 0;
}
