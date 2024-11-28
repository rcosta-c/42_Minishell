#include "../includes/minishell.h"

bool    verify_errors(t_sh *sh)
{
	int x;

	x = 0;
	if(sh->error.expand_error == true || sh->error.parse_error == true)
		return(true);
	else if(sh->error.token_error == true)
		return(true);
	else if(sh->vars.cmds_num > 0)
	{
		while(x < sh->vars.cmds_num)
		{
			if(sh->comands[x].errors.empty_pipe == true)
				return(true);
			else if(sh->comands[x].errors.infile_noaccess == true || sh->comands[x].errors.infile_notvalid == true)
				return(true);
			else if(sh->comands[x].errors.outfile_noaccess == true || sh->comands[x].errors.outfile_notvalid == true)
				return(true);
			else
				x++;
		}	
	}
	return(false);
}