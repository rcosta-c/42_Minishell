#include "../includes/minishell.h"

int		g_status;


void	 print_exec(t_sh *sh)
{
	int  x;
	int xx;

	xx = 0;
	x = 0;
		while(x < sh->vars.cmds_num && sh->vars.tk_num > 0)
		{
			xx = 0;
			printf("\n******* COMAND NUM=%d *******\n", x);
			printf("**\n**\n");
			printf("**	CMD=%s 	\n", sh->comands[x].cmd);
			printf("**	N_ARGS=%d 	\n", sh->comands[x].n_args);
			while(sh->comands[x].arg && xx <= sh->comands[x].n_args)
			{
				printf("**	ARG %d = %s 	\n", xx, sh->comands[x].arg[xx]);
				xx++;
			}
			
			if(sh->comands[x].pipes == true)
				printf("**	pipe = ON!	\n");
			else
				printf("**	pipe = OFF	\n");
			if(sh->comands[x].redir == true)
				printf("**	redir = ON!	\n");
			else
				printf("**	redir = OFF!	\n");
			printf("**	INFILE=%s 	\n", sh->comands[x].infile);
			printf("**	INFILE_FD=%d \n", sh->comands[x].infile_fd);
			printf("**	IN_HEREDOC=%s 	\n", sh->comands[x].inheredoc_file);
			printf("**	IN_HEREDOC=FD=%d \n", sh->comands[x].inheredoc_fd);
			printf("**	OUTFILE=%s 	\n", sh->comands[x].outfile);
			printf("**	OUTFILE_FD=%d \n", sh->comands[x].outfile_fd);
			printf("**	OUTAPPENDFILE=%s 	\n", sh->comands[x].outappendfile);
			printf("**	OUTAPPENDFILE_FD=%d \n\n\n", sh->comands[x].outappend_fd);
			
			x++;
		}
}

void    printflags(t_sh *sh)
{
	int n = 0;

	printf("\n tknum = %d\ncmds_num=%d\nheredoc=%d\npipe=%d\nredir=%d", sh->vars.tk_num, sh->vars.cmds_num, sh->vars.heredoc_num, sh->vars.pipe_num, sh->vars.redir_num);
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
		if(sh->tokens[n].r_heredoc == true)
			printf("Flag.rheredoc = true\n");
		else
			printf("Flag.rheredoc = false\n");
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
	char	*prompt;
	//char	**temp;

	(void)ac;
	(void)av;
	sh = ft_calloc(1, sizeof(t_sh));
	//temp = ft_calloc(2, sizeof(char **));
	//sh->tokens = ft_calloc(1, sizeof(t_tokens));
	if(sh == NULL)
		return(EXIT_FAILURE);
	ft_getenv(sh, envp);
	init_error(sh);
	while(1)
	{
		sh->vars.sh_status = true;
		//free_heredoc(sh);
	//	if(!g_status)
	//		g_status = 0;
		ft_sigset();
		init_vars(sh);
		if(sh->cmd_line)
			free(sh->cmd_line);		
		prompt = get_prompt(sh); //----------VERIFICAR LEAKS AQUI!!!!
		sh->cmd_line = readline(prompt);
		free(prompt);
//printf("\ncmdline=%s\n", sh->cmd_line);
		if(!sh->cmd_line)
		{
			sh->vars.sh_status = false;
			g_status = EXIT_SIGQUIT;
			ft_exit(sh, NULL);	
		}
			
		add_history(sh->cmd_line);

		if(ft_strlen(sh->cmd_line) > 0)
		{
			sh->cmd_line = prepare_line(sh->cmd_line); //----------VERIFICAR LEAKS AQUI!!!!
			sh->vars.tk_num = count_tokens(sh);
			init_tokens(sh);
			split_cmd(sh);
			filter_tokens(sh);


			search_expand(sh);

			init_parser(sh);
			/*if(check_before_parse(sh))
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
			}*/

			fill_parser(sh);  //----------VERIFICAR LEAKS AQUI!!!!

//printflags(sh);
//print_exec(sh);
			
			executor(sh);

			free_tokens(sh);
			free_cmds(sh);
		}
	
	}
	return(0);




}