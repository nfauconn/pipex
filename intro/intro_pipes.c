
#include "pipex.h"

// PIPES

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	id;
	int	fd[2]; //fd_in = read end		 of the pipe 
				// fd_out = write end

	if (pipe(fd) == -1)
		printf("an error occured with opening the pipe\n");
	id = fork();
	if (id == -1)
		printf("error occured with fork\n");
	if (id == 0) //si on est dans le child
	{
		close(fd_in);
		int x;
		printf("enter your age: ");
		scanf("%d", &x);
		if (write(fd_out, &x, sizeof(int)) == -1)
			printf("an error occured with opening the pipe\n");
		close(fd_out);
	}
	else
	{
		wait(NULL); // to avoid the child to become a zombie --> LEAKS
		close(fd_out);
		int	y;
		read(fd_in, &y, sizeof(int));
		close(fd_in);
		printf("got from child process %d\n", y);
	}
	return (0);
}