/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/25 13:02:29 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc >= 5)
	{
		printf("coucou %d, %s, %s\n", argc, argv[0], envp[0]);
		init_data(&data);
		fill_data(&data, argc, argv, envp);
	}
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	return (0);
}
