#include "pipex.h"

void	main_work(int pipe_to_main[2], int pipe_to_child[2])
{
	int	y;

	y = 10;
	close(pipe_to_child[0]);
	close(pipe_to_main[1]);
	if (write(pipe_to_child[1], &y, sizeof(int)) == -1)
	{
		printf("error\n");
		return ;
	}
//	printf("result of y (%d) ", y);
	if (read(pipe_to_main[0], &y, sizeof(int)) == -1)
	{
		printf("error\n");
		return ;
	}
	printf("multiplied by child = %d\n", y);
}

void	child_work(int pipe_to_main[2], int pipe_to_child[2])
{
	int	x;

	close(pipe_to_main[0]);
	close(pipe_to_child[1]);
	if (read(pipe_to_child[0], &x, sizeof(int)) == -1)
	{
		printf("error\n");
		return ;
	}
//	printf("child : received x = %d\n", x);
	x *= 4;
	if (write(pipe_to_main[1], &x, sizeof(int)) == -1)
	{
		printf("error\n");
		return ;
	}
}

int	main()
{
	int pid;
	int	pipe_to_main[2];
	int	pipe_to_child[2];

	if (pipe(pipe_to_main) == -1)
	{
		printf("error\n");
		return (1);
	}
	if (pipe(pipe_to_child) == -1)
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
	if (pid == 0) //child process
	{
		child_work(pipe_to_main, pipe_to_child);
	}
	else		// main process
	{
		main_work(pipe_to_main, pipe_to_child);
	}
}
