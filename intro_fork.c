#include "pipex.h"

int	main()
{
	int	id;
	int n;
	int i;
	int	res;

	ft_printf("process pid : %d parent pid : %d\n", getpid(), getppid());

	id = fork();
	if (id == 0) // --> child process
		n = 1;
	else // -> main process
	{
		n = 6;
	}

	res = wait(NULL); // attends qu'un processus enfant se termine (1 seul 11 et si le processus n'a pas de child, return -1)
	if (res == -1)
		ft_printf("process %d has no child to wait for\n", id);
	else
		ft_printf("\n%d finished his execution\n", res);

	i = n;
	while (i < n + 5)
	{
		ft_printf("%d", i++);
	}
	if (id != 0)
		ft_printf("\n");
	return (0);
}

// cf call fork multiple times si je me souviens plus
