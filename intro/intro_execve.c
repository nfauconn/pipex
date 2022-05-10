#include "pipex.h"

/*execve --> exec with - Vector (pointer to string args)
**					   - Environnment
**
** file descriptor = unique number across a process 
**					 --> key to an input / output ressource
*/

int	main(int argc, char **argv, char **env)
{
	int	pid;


	(void)argc;
	pid = fork();
	if (pid == -1)
	{
		printf("error\n");
		return (1);
	}
	if (pid == CHILD)
	{
		int	ret;
		ret = execve("./a.out", argv, env);
		if (ret == -1)
			return (42);
	}
	else
	{
		int	status;
		int	status_code;
		wait(&status);			// status va etre remplie par la valeur de retour du child
		if (WIFEXITED(status)) //macro qui renvoie vrai si le fils s'est termine a cause d'un signal
		{
			status_code = WEXITSTATUS(status);
			if (status_code == 42)
				ft_printf("failure\n");
			else
				ft_printf("success\n");
		}
	}
	printf("finished\n");
	return (0);
}
