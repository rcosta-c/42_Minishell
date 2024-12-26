/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:30 by rcosta-c          #+#    #+#             */
/*   Updated: 2024/12/26 13:18:36 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			printf("**	OUTAPPENDFILE_FD=%d \n", sh->comands[x].outappend_fd);
			if(sh->comands[x].errors.cmd_not_found == true)
				printf("**	errors.cmd_not_found = ON!	\n");
			else
				printf("**	errors.cmd_not_found = OFF	\n");
			if(sh->comands[x].errors.empty_pipe == true)
				printf("**	errors.empty_pipe = ON!	\n");
			else
				printf("**	errors.empty_pipe = OFF	\n");
			if(sh->comands[x].errors.empty_redir == true)
				printf("**	empty_redir = ON!	\n");
			else
				printf("**	empty_redir = OFF	\n\n\n");
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
void	printf_flag_errors(t_sh *sh)
{
	int x;

	x = 0;
	
		printf("\n\nexec_error%d\n", sh->error.exec_error);
		printf("parse error%d\n ", sh->error.parse_error);
		printf("expand_error%d\n ", sh->error.expand_error);
		printf("token_error%d\n ", sh->error.token_error);
		printf("exit_error%d\n ", sh->error.exit_error);
		printf("cmd_error%d\n ", sh->error.cmd_error);
		printf("heredoc_error%d\n ", sh->error.heredoc_error);
	
		while(x < sh->vars.cmds_num)
		{
			
			printf("cmd_not_found%d\n ", sh->comands[x].errors.cmd_not_found);
			printf("infile_notvalid%d\n ", sh->comands[x].errors.infile_notvalid);
			printf("infile_noaccess%d\n ", sh->comands[x].errors.infile_noaccess);
			printf("outfile_noaccess%d\n ", sh->comands[x].errors.outfile_noaccess);
			printf("outfile_notvalid%d\n ", sh->comands[x].errors.outfile_notvalid);
			printf("empty_pipe%d\n ", sh->comands[x].errors.empty_pipe);
			printf("empty_redir%d\n ", sh->comands[x].errors.empty_redir);
			x++;
		}
}

static void	sh_loop(t_sh *sh)
{
		char	*prompt;

		init_cycle(sh);
		prompt = get_prompt(sh);
		sh->cmd_line = readline(prompt);
		free(prompt);
		if(!sh->cmd_line)
			handbrake_and_exit(sh);
		add_history(sh->cmd_line);
		if(ft_strlen(sh->cmd_line) > 0)
		{
			sh->cmd_line = prepare_line(sh->cmd_line);
//printf("\n\nprepline=%s\n", sh->cmd_line);
			sh->vars.tk_num = count_tokens(sh);
//printf("\n\ncmd=%s	tk_num=%d\n\n", sh->cmd_line, sh->vars.tk_num);
			init_tokens(sh);
			split_cmd(sh);
//printf("numero de tokens= %d, antes do filter=%s\n\n", sh->vars.tk_num, sh->cmd_line);
			filter_tokens(sh);
			search_expand(sh);
//printflags(sh);
			init_parser(sh);

			fill_parser(sh);

//print_exec(sh);
			executor(sh);
//printf_flag_errors(sh);
			free_tokens(sh);
			free_cmds(sh);
		}
}

int main(int ac, char **av, char **envp)
{
   	t_sh	*sh;

	(void)ac;
	(void)av;
	sh = ft_calloc(1, sizeof(t_sh));
	if(sh == NULL)
		return(EXIT_FAILURE);
	ft_getenv(sh, envp);
	init_prompt_utils(sh);
	init_error(sh);
	while(1)
		sh_loop(sh);
	rl_clear_history();
	return(0);
}

