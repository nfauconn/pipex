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
		execve("?put", argv, env);
		printf("%s\n", strerror(errno));
	}
	else
		wait(NULL);
//	printf("finished\n");
	return (0);
}
