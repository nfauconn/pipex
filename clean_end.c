/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:30:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/06 17:32:59 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_end(t_data *data)
{
	int	i;
	if (data->cmd1)
	{
		i = 0;
		while (data->cmd1[i])
		{
			free(data->cmd1[i]);
			i++;
		}
		free(data->cmd1);
	}
	if (data->cmd2)
	{
		i = 0;
		while (data->cmd2[i])
			free(data->cmd2[i++]);
		free(data->cmd2);
	}
}

void	error_exit(t_data *data, char *s)
{
	ft_putstr_fd(s, 2);
	clean_end(data);
	exit(EXIT_FAILURE);
}
