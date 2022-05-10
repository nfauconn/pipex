/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_clean_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nono <nono@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:30:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/10 15:31:54 by nono             ###   ########.fr       */
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
			free(data->cmd1[i++]);
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

void	error_exit(t_data *data, char *s1, char *s2, char *s3)
{
	ft_printf("%s%s: %s\n", s1, s2, s3);
/* 	if (s1)
		write(STDERR, s1, ft_strlen(s2));
	if (s2)
		write(STDERR, s2, ft_strlen(s2));
	write(STDERR, "\n", 1); */
	clean_end(data);
	exit(EXIT_FAILURE);
}
