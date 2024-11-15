
- Verificação de permissao dos ficheiros
    -verficar permssao para escrita
    -verificar permissao para leitura

    -- exemplo

        const char *filename = "meu_ficheiro.txt";
        if (access(filename, F_OK) == 0)
        {
            printf("ficheiro nao existe\n");
        }
        F_OK — Verifica se o ficheiro existe.
        R_OK — Verifica se tens permissão de leitura.
        W_OK — Verifica se tens permissão de escrita.
        X_OK — Verifica se tens permissão de execução.


- Criar caminhos completos para os ficheiros dos redirects.
