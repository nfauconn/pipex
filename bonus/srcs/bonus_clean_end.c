/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_clean_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:30:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/24 19:51:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	clean_end(t_data *data)
{
	t_cmd	**tmp;

	tmp = &data->cmd;
	while (data->cmd)
	{
		ft_2D_array_free(data->cmd->tab);
		data->cmd = data->cmd->next;
	}
	free(*tmp);
	close(data->fd_in);
	close(data->fd_out);
}

void	error_exit(t_data *data, char *s1, char *s2, char *s3)
{
	ft_printerror("%s%s: %s\n", s1, s2, s3);
	clean_end(data);
	exit(EXIT_FAILURE);
}
