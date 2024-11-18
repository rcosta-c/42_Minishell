/*#include "../includes/minishell.h"
#include <sys/stat.h>

//char	*build_cmd_path(t_sh *sh, )
int	main(int ac, char **av)
{
	char	**path;
	char	*temp;
	struct stat	path_stat;

	int x;

	x = 0;
	path = ft_split(getenv("PATH"), ':');
	write(1, "\n", 1);
	temp = ft_strjoin("/bin", "/ls");
	if(stat(temp, &path_stat) == 0 && access(temp, X_OK) == 0)
		x = 0;	
	else
	{
		while(path[x])
		{
			temp = ft_strjoin(path[x], "/ls");
			if(stat(temp, &path_stat) == 0 && access(temp, X_OK) == 0)
			{
				printf("acesso ao comando confirmado!\n %s\n", temp);
				break;
			}
			x++;
		}
	}
	x = -1;
	while(path[++x])
		free(path[x]);
	free(path);
	return(0); // return(temp);
}*/