#include <stdio.h>

int	main(int ac, char **argv)
{
	if (ac == 2)
		printf("%s\n", argv[1]);
	else
		return(1);
	return(0);
}