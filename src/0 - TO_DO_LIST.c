


BUILT-INS VERIFICADOS E A FUNCIONAR BEM:
UNSET (sem opcoes) (com argumentos)
PWD (sem opcoes) (e sem args)
ENV (sem opcoes) (sem argumentos)
EXPORT (sem opcoes) (ja esta esta a funcionar os argumentos)
EXIT (funcionando perfeitamente)
ECHO (funcionando perfeitamente)


CD - erros fora dos builtins 


FAZER:

-GERAR ERRO G_STATUS ou G_EXIT
-GERAR AS MENSAGENS DE ERRO ESCRITAS NECESSARIAS;

-FAZER O HANDLE DE 
    -> $PWD (VAR AMBIENTE COMO TOKEN[0])
        deve printar a var





PROCURAR + ERROS






- Criar caminhos completos para os ficheiros dos redirects.
    (ACHO QUE NAO É NECESSARIO)


-LIBERTAR MEMORIA DE SH->ENVP quando sair.


FEITO
/*


-CORRIGIR A PARTE DO PROMPT QUE USA O GETENV(FUNCAO PROIBIDA)
- Verificar funcao GETENV no promp. alterar isto.


-ALTERAR ENVP -> ALOCAR VARIAVEL CHAR ** COM OS DADOS DE ENVP para depois
ser mais facil no FT_EXPORT para acrescentar ou retirar alguma VAR AMBIENTE


-FAZER INTEGRACAO COMPLETA DE BUILTINS


- Verificação de permissao dos ficstatusheiros
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


- criar signals para ler o CTRL + D e fazer nova linha
status
-criar funcao para tirar os " " e ' '


- Criar caminhos completos para os comandos. Caso sejam bultins ou caso sejam outros
    -PRECISO ACEDER A $PATH e separar pelos : e analisar em cada um dos directorios
    -verificar com o access(path, X_OK) se existe e se tem acesso para execucao.
    -devolver esse path para o comando e juntar com o join2str
*/
