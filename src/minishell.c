#include "../includes/minishell.h"

int		g_status;

void    printflags(t_sh *sh)
{
	int n = 0;

	while(n < sh->vars.tk_num)
	{
		printf("\n\n\n\n TOKEN NUMERO %d \n\ntoken=%s\n\n", n, sh->tokens[n].tokens);
		if(sh->tokens[n].arg == true)
			printf("Flag.arg = true\n");
		else
		   printf("Flag.arg = false\n");
		if(sh->tokens[n].d_quote == true)
			printf("Flag.d_quote = true\n");
		else
		   printf("Flag.d_quote = false\n");
		if(sh->tokens[n].s_quote == true)
			printf("Flag.s_quote = true\n");
		else
		   printf("Flag.s_quote = false\n");
		if(sh->tokens[n].f_quote == true)
			printf("Flag.f_quote = true\n");
		else
		   printf("Flag.f_quote = false\n");
		if(sh->tokens[n].exp_t == true)
			printf("Flag.exp_t = true\n");
		else
		   printf("Flag.exp_t = false\n");
		if(sh->tokens[n].exp_e == true)
			printf("Flag.exp e = true\n");
		else
		   printf("Flag.exp e = false\n");
		if(sh->tokens[n].r_in == true)
			printf("Flag.r inm = true\n");
		else
		   printf("Flag.rin = false\n");
		if(sh->tokens[n].r_outappend == true)
			printf("Flag.r_outappend = true\n");
		else
			printf("Flag.r_outappend = false\n");
		if(sh->tokens[n].r_out == true)
			printf("Flag.r_out = true\n");
		else
		   printf("Flag.r_out = false\n");
		if(sh->tokens[n].cmd == true)
			printf("Flag.cmd = true\n");
		else
		   printf("Flag.cmd = false\n");
		if(sh->tokens[n].pipe == true)
			printf("Flag.pipe = true\n");
		else
		   printf("Flag.pipe = false\n");
		if(sh->tokens[n].file == true)
			printf("Flag.file = true\n");
		else
		   printf("Flag.file = false\n");
		n++;
	}
}

int main(int ac, char **av, char **envp)
{
   	t_sh	*sh;
	char	*a;

	(void)ac;
	(void)av;
	sh = ft_calloc(1, sizeof(t_sh));
	if(sh == NULL)
		return(EXIT_FAILURE);
	//memset(&sh, 0, sizeof(t_sh));
	sh->envp = envp;
	init_error(sh);
	while(1)
	{
		ft_sigset();
		init_vars(sh);
		/*if(sh->vars.tk_num > 0)
		{
			ft_bzero(sh->tokens, sizeof(t_tokens));
			ft_bzero(sh->comands, sizeof(t_exec));
		}*/
		if(sh->cmd_line)
			free(sh->cmd_line);		
		
		a = get_prompt();
		sh->cmd_line = readline(a);

		if(sh->cmd_line[1] == '9') // APAGAR ISTO!
		{
			free(sh->cmd_line);
			free_tokens(sh);
			free_cmds(sh);
			rl_clear_history();
			free(a);
			break;
		}



		sh->cmd_line = prepare_line(sh->cmd_line);
//		printf("\n\nline /inicio/%s/fim/", sh->cmd_line);

		sh->vars.tk_num = count_tokens(sh);
//		printf("\nnumero de tokens=%d\n", sh->vars.tk_num);
		init_tokens(sh);
		split_cmd(sh);

		filter_tokens(sh);

		search_expand(sh);


//		PRINTAR AS FLAGS DOS TOKENS!!! //
/*
		printflags(sh);
		printf("\n\n");
		int x = 0;

		while(x < sh.vars.tk_num)
		{
			printf("\n %i \n %s \n", sh.tokens[x].num, sh.tokens[x].tokens);
			x++;
		}
*/

		init_parser(sh);
		if(check_before_parse(sh))
			{
				printf("\ninvalid!!!\n");
				free_tokens(sh);
				break;
			}
		if(check_r_out(sh) || check_r_in(sh) || check_r_append_out(sh))// || check_pipe(&sh))
			{
				printf("\ninvalid!!!\n");
				free_tokens(sh);
				break;
			}

//					printf("\n\n PARSERRR\n\n");

		fill_parser(sh);

		
//		printf("\n\n %d\n\n", sh->vars.cmds_num);
		
		executor(sh);

		

		//printf("\n\n");


		
/*		x = 0;
		while(x < sh->vars.cmds_num && sh->vars.tk_num > 0)
		{
			xx = 0;
			printf("\n******* COMAND NUM=%d *******\n", x);
			printf("**\n**\n");
			printf("**	CMD=%s 	\n", sh->comands[x].cmd);
			printf("**	N_ARGS=%d 	\n", sh->comands[x].n_args);
			while(xx < sh->comands[x].n_args + 1)
			{
				printf("**	ARG %d = %s 	\n", xx, sh->comands[x].arg[xx]);
				xx++;
			}
			if(sh->comands[x].pipe)
				printf("**	pipe = ON!	\n");
			else
				printf("**	pipe = OFF	\n");
			printf("**	INFILE=%s 	\n", sh->comands[x].infile);
			printf("**	INFILE_FD=%d \n", sh->comands[x].infile_fd);
			printf("**	OUTFILE=%s 	\n", sh->comands[x].outfile);
			printf("**	OUTFILE_FD=%d \n\n\n", sh->comands[x].outfile_fd);
			x++;
		}
*/
		
		free_tokens(sh);
		free_cmds(sh);
		
	}
	return(0);




}