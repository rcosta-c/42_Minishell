#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <signal.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
//#include "../lib/libft/libft.h"

int main()
{
	char *a;

	a = readline("merda");
	free(a);
	return(0);
}
