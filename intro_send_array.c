#include "pipex.h"

int	main()
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		printf("error\n");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("error\n");
		return (1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		int	array[3] = {1, 20, 3};
		int len = 3;
		if (write(fd[1], &len, sizeof(int)) == -1) // SEND ARRAY SIZE FIRST
		{										// IF STRING : STRLEN + 1
			printf("error\n");
			return (1);
		}
		if (write(fd[1], array, sizeof(int) * len) == -1)
		{
			printf("error\n");
			return (1);
		}
		close(fd[1]);
	}
	else
	{
		int	array[5];
		int	len = 0;
		close(fd[1]);
		if (read(fd[0], &len, sizeof(int)) == -1)
		{
			printf("error\n");
			return (1);
		}
		if (read(fd[0], array, sizeof(int) * len) == -1)
		{
			printf("error\n");
			return (1);
		}
		close(fd[0]);
		int	i = 0;
		int sum = 0;
		while (i < len)
			sum += array[i++];
		printf("sum = %d\n", sum);
		wait(NULL); 				//dont forget (les close aussi)
	}
}
