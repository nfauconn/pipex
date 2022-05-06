
#include "pipex.h"

// PIPES

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	id;
	int	fd[2]; //fd[0] = read end		 of the pipe 
				// fd[1] = write end

	if (pipe(fd) == -1)
		printf("an error occured with opening the pipe\n");
	id = fork();
	if (id == -1)
		printf("error occured with fork\n");
	if (id == 0) //si on est dans le child
	{
		close(fd[0]);
		int x;
		printf("enter your age: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
			printf("an error occured with opening the pipe\n");
		close(fd[1]);
	}
	else
	{
		wait(NULL); // to avoid the child to become a zombie --> LEAKS
		close(fd[1]);
		int	y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("got from child process %d\n", y);
	}
	return (0);
}