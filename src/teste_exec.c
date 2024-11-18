/*

 
 VERIFICAR ESTE PROCESSSO.


*/
// Função para executar um único comando
void execute_command(t_sh *sh, int cmd_index, int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo filho
        // Redirecionar a entrada
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // Redirecionar a saída
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        // Executar o comando
        char **argv = malloc((sh->comands[cmd_index].n_args + 2) * sizeof(char *));
        argv[0] = sh->comands[cmd_index].cmd; // O comando
        for (int i = 0; i < sh->comands[cmd_index].n_args; i++) {
            argv[i + 1] = sh->comands[cmd_index].arg[i]; // Argumentos
        }
        argv[sh->comands[cmd_index].n_args + 1] = NULL; // Termina o array

        execvp(argv[0], argv); // Executa o comando
        perror("exec failed"); // Se execvp falhar
        exit(EXIT_FAILURE);
    } else { // Processo pai
        waitpid(pid, NULL, 0); // Espera o filho terminar
    }
}

// Função para executar todos os comandos
void execute_commands(t_sh *sh) {
    int input_fd = STDIN_FILENO; // Entrada padrão
    int output_fd;

    for (int i = 0; i < sh->num_comands; i++) {
        // Configura o arquivo de saída
        if (sh->comands[i].outfile) {
            output_fd = open(sh->comands[i].outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0) {
                perror("open outfile failed");
                continue; // Continue para o próximo comando se falhar
            }
        } else {
            output_fd = STDOUT_FILENO; // Se não houver arquivo de saída, usa a saída padrão
        }

        // Executa o comando
        execute_command(sh, i, input_fd, output_fd);

        // Fecha o descritor de saída se foi aberto
        if (sh->comands[i].outfile) {
            close(output_fd);
        }

        // Configura a entrada para o próximo comando se houver um pipe
        if (sh->comands[i].pipe) {
            int pipe_fd[2];
            if (pipe(pipe_fd) == -1) {
                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
            input_fd = pipe_fd[0]; // A entrada do próximo comando é a saída do pipe
            close(pipe_fd[1]); // Fecha a extremidade de escrita do pipe
        } else {
            input_fd = STDIN_FILENO; // Reseta a entrada padrão
        }
    }
}


















/*


PROCESO NOVO A VERIFICAR



*/


// Funções para comandos built-in
int ft_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }
    if (chdir(args[1]) != 0) {
        perror("cd failed");
        return 1;
    }
    return 0;
}

int ft_exit(char **args) {
    exit(0);
}

int ft_echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 0;
}

// Função para verificar se um comando é um built-in
bool is_builtin(char *cmd) {
    return (strcmp(cmd, "cd") == 0 || strcmp(cmd, "exit") == 0 || strcmp(cmd, "echo") == 0);
}

// Função para executar um comando built-in
void execute_builtin(t_sh *sh, int cmd_index) {
    if (strcmp(sh->comands[cmd_index].cmd, "cd") == 0) {
        ft_cd(sh->comands[cmd_index].arg);
    } else if (strcmp(sh->comands[cmd_index].cmd, "exit") == 0) {
        ft_exit(sh->comands[cmd_index].arg);
    } else if (strcmp(sh->comands[cmd_index].cmd, "echo") == 0) {
        ft_echo(sh->comands[cmd_index].arg);
    }
}

// Função para executar um único comando
void execute_command(t_sh *sh, int cmd_index, int input_fd, int output_fd) {
    if (is_builtin(sh->comands[cmd_index].cmd)) {
        execute_builtin(sh, cmd_index);
        return; // Não precisa fork ou exec para built-ins
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo filho
        // Redirecionar a entrada
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // Redirecionar a saída
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        // Executar o comando
        char **argv = malloc((sh->comands[cmd_index].n_args + 2) * sizeof(char *));
        argv[0] = sh->comands[cmd_index].cmd; // O comando
        for (int i = 0; i < sh->comands[cmd_index].n_args; i++) {
            argv[i + 1] = sh->comands[cmd_index].arg[i]; // Argumentos
        }
        argv[sh->comands[cmd_index].n_args + 1] = NULL; // Termina o array

        execvp(argv[0], argv); // Executa o comando
        perror("exec failed"); // Se execvp falhar
        exit(EXIT_FAILURE);
    } else { // Processo pai
        waitpid(pid, NULL, 0); // Espera o filho terminar
    }
}

// Função para executar todos os comandos
void execute_commands(t_sh *sh) {
    int input_fd = STDIN_FILENO; // Entrada padrão
    int output_fd;

    for (int i = 0; i < sh->num_comands; i++) {
        // Configura o arquivo de saída
        if (sh->comands[i].