#include "pipex.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	arr[] = {1, 2, 3, 4, 1, 2, 7};
	int	arrSize = sizeof(arr) / sizeof(int);
	int start;
	int	end;
	int fd[2];

	if (pipe(fd) == -1)
		printf("error\n");

	int id = fork();
	if (id == -1)
		printf("error\n");
	if (id == 0)
	{
		start = 0;
		end = (arrSize / 2);
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}

	int sum = 0;
	int	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("calculated partial sum = %d\n", sum);

	if (id == 0)
	{
		close(fd_in);
		if (write(fd_out, &sum, sizeof(int)) == -1)
			printf("error\n");
		close(fd_out);
	}
	else
	{
		int	sum_from_child;
		close(fd_out);
		if (read(fd_in, &sum_from_child, sizeof(sum_from_child)) == -1)
			printf("error\n");
		close(fd_in);

		int	total_sum = sum + sum_from_child;
		printf("total sum is : %d\n", total_sum);
	}
	wait(NULL);
	return (0);
}