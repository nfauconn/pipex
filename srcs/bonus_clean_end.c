/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_clean_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:30:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/23 21:04:38 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	bonus_clean_end(t_data_b *data)
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

void	bonus_error_exit(t_data_b *data, char *s1, char *s2, char *s3)
{
	ft_printerror("%s%s: %s\n", s1, s2, s3);
	bonus_clean_end(data);
	exit(EXIT_FAILURE);
}
