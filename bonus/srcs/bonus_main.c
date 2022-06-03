/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/31 18:08:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc >= 5)
	{
		init_data(&data);
		fill_data(&data, argc, argv, envp);
		exec_cmd(&data);
		clean_end(&data);
	}
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	return (0);
}
