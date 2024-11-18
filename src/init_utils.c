#include "../includes/minishell.h"

void    init_tk_flag1(t_sh *sh, int x)
{
    sh->tokens[x].cmd = false;
	sh->tokens[x].arg = false;
	sh->tokens[x].pipe = false;
	sh->tokens[x].r_in = false;
	sh->tokens[x].r_out = false;
	sh->tokens[x].s_quote = false;
	sh->tokens[x].d_quote = false;
	sh->tokens[x].f_quote = false;
	sh->tokens[x].envp = false;
	sh->tokens[x].file = false;
	sh->tokens[x].exp_e = false;
	sh->tokens[x].exp_t = false;
}

void    init_cmds(t_sh *sh, int x)
{
    sh->comands[x].pipe = false;
	sh->comands[x].infile = NULL;
	sh->comands[x].outfile = NULL;
	sh->comands[x].arg = NULL;
	sh->comands[x].n_args = 0;
    sh->comands[x].errors.cmd_not_found = false;
    sh->comands[x].errors.empty_pipe = false;
    sh->comands[x].errors.infile_noaccess = false;
    sh->comands[x].errors.infile_notvalid = false;
    sh->comands[x].errors.outfile_noaccess = false;
    sh->comands[x].errors.outfile_notvalid = false;
}

