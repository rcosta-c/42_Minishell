/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:54:30 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/18 11:01:31 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_status;

static void	ft_get_minimal_envp(t_sh *sh)
{
	char	cwd[10000];
	char	*temp_home;

	sh->vars.envp_total = 5;
	sh->envp = malloc(sizeof(char *) * (sh->vars.envp_total + 1));
	if (!sh->envp)
		return ;
	getcwd(cwd, sizeof(cwd));
	sh->envp[0] = ft_strjoin("PWD=", cwd);
	sh->envp[1] = ft_strdup("SHLVL=1");
	sh->envp[2] = ft_strdup("PATH=/usr/bin:/bin");
	sh->envp[3] = ft_strdup("USER=42");
	temp_home = get_my_home(sh);
	sh->envp[4] = ft_strjoin("HOME=", temp_home);
	sh->envp[5] = NULL;
	free(temp_home);
}

void	handbrake_and_exit(t_sh *sh)
{
	sh->vars.sh_status = false;
	g_status = EXIT_SIGQUIT;
	ft_exit(sh, NULL);
}

static void	tokenizer(t_sh *sh)
{
	sh->cmd_line = prepare_line(sh->cmd_line);
	if (sh->cmd_line)
		count_tokens(sh);
	init_tokens(sh);
	copy_tokens(sh);
	filter_tokens(sh);
	ft_redir_multiargs(sh);
	search_expand(sh);
	cleaning_quotes(sh);
}

static void	sh_loop(t_sh *sh)
{
	char	*prompt;
	bool	start_sh;

	start_sh = false;
	init_cycle(sh);
	while (start_sh == false)
	{
		prompt = get_prompt(sh);
		sh->cmd_line = readline(prompt);
		free(prompt);
		if (!sh->cmd_line)
			handbrake_and_exit(sh);
		start_sh = verify_cmdline(sh, sh->cmd_line);
	}
	save_to_history(sh, sh->cmd_line);
	if (ft_strlen(sh->cmd_line) > 0)
	{
		tokenizer(sh);
		init_parser(sh);
		fill_parser(sh);
		executor(sh);
		free_tokens(sh);
		free_cmds(sh);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_sh	*sh;

	(void)ac;
	(void)av;
	sh = ft_calloc(1, sizeof(t_sh));
	if (sh == NULL)
		return (EXIT_FAILURE);
	if (envp == NULL || envp[0] == NULL)
		ft_get_minimal_envp(sh);
	else
		ft_getenv(sh, envp);
	init_prompt_utils(sh);
	init_error(sh);
	while (1)
		sh_loop(sh);
	rl_clear_history();
	return (0);
}
