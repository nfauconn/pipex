/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:30:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/21 19:40:43 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	clean_end(t_data *data)
{
	if (data->cmd1)
		free_tab(data->cmd1);
	if (data->cmd2)
		free_tab(data->cmd2);
	if (data->paths)
		free_tab(data->paths);
	close(data->fd_in);
	close(data->fd_out);
}

void	error_exit(t_data *data, char *s1, char *s2, char *s3)
{
	if (!*s3)
		ft_printerror("%s: %s\n", s1, s2);
	else // if (s1 && s2 && s3)*/
		ft_printerror("%s%s: %s\n", s1, s2, s3);
	clean_end(data);
	exit(EXIT_FAILURE);
}
