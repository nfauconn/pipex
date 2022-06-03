/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_clean_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:30:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/31 17:50:53 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	clean_end(t_data *data)
{
	t_cmd	*to_free;

	close(data->fd_in);
	if (data->cmd)
	{
		while (data->cmd)
		{
			ft_2D_array_free(data->cmd->tab);
			to_free = data->cmd;
			data->cmd = data->cmd->next;
			free(to_free);
		}
	}
	close(data->fd_out);
	if (data->env)
		ft_lstclear(&data->env, free);
	if (data->paths)
		ft_2D_array_free(data->paths);
}

void	error_exit(t_data *data, char *s1, char *s2, char *s3)
{
	ft_printerror("%s%s: %s\n", s1, s2, s3);
	clean_end(data);
	exit(EXIT_FAILURE);
}
