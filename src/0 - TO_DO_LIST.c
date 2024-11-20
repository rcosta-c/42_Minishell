
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


- criar signals para ler o CTRL + D e fazer nova linha




FEITO
/*
-criar funcao para tirar os " " e ' '


- Criar caminhos completos para os comandos. Caso sejam bultins ou caso sejam outros
    -PRECISO ACEDER A $PATH e separar pelos : e analisar em cada um dos directorios
    -verificar com o access(path, X_OK) se existe e se tem acesso para execucao.
    -devolver esse path para o comando e juntar com o join2str
*/

- 
