#include "pipex.h"

/* dup2(fd, old_fd) duplique fd et lui donne la valeur du old_fd
** ex : si old_fd est stdout (val 1), le fd duplique sera desormais la sortie standard
** dup2 close le old_fd !!!
**
**
*/



int	child_exec(char **argv, char **env)
{
	int	file;
	file = open("test_dup2.txt", O_WRONLY | O_CREAT);
	if (file == -1)
		return (42);

	dup2(file, 1); // now, a.out output will go in file = test_dup2.txt
	close(file);   // car on l'a duplique !!! et mis a la place de stdout qui a ete close

	int	ret;
	ret = execve("./a.out", argv, env);
	return (ret);
}

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
		ret = child_exec(argv, env);
		if (ret == -1)
			return (42);
	}
	else
	{
		int	status;
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 42)
				ft_printf("failure\n");
			else
				ft_printf("success\n");
		}
	}
	printf("finished\n");
	return (0);
}
