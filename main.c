/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/04/26 14:34:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **argv)
{
	errno = 0;
	if (ac == 5)
	{
		open(argv[1], O_WRONLY, O_APPEND);
		if (errno != 0)
			printf("%s\n", strerror(errno));
	}
	else
		write(STDERR, "wrong number of arguments\n", 27);
	return (0);
}
