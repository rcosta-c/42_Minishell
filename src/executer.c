#include "../includes/minishell.h"



// garantir que se existir uma falha na construcao da arvore de processos, a execucao nao segue, e é da mensagem de erro


// verificar o numero de comandos. se um a arvore é simples. se mais a arvore é "recursiva"


//  Verificar se comandos sao builtins, se sim mas nem todos sao criar fork()->> processo independente, fora do nosso programa para executor comandos exteriores


// Verificar se tem pipes para construir a execucao de cada comando.


// (talvez tenha de alterar a definicao do r_in e r_out para int, para passar a guardar o fileno/fd ja que vao ser ficheiros)


// verificar se tem pipes, e nesse caso porque o numero de comandos é maior que 1


// caso exista pipes, criar entao arvore de contrucao de processo.
