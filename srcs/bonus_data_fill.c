/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:01:21 by user42            #+#    #+#             */
/*   Updated: 2022/05/23 21:04:40 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	bonus_fill_data(t_data_b *data, int ac, char **argv, char **envp)
{
	int	i;

	data->fd_in = bonus_clean_open(data, data->fd_in, argv[1], O_RDONLY);
	data->cmd = (t_cmd *)malloc(sizeof(t_cmd) * (ac - 3));
	i = 2;
	while (i < ac)
	{
		data->cmd->tab = bonus_tokenized_cmd(argv[i]);
		data->cmd = data->cmd->next;
	}
	data->fd_out = bonus_clean_open(data, data->fd_out, argv[ac - 1], O_WRONLY);
	data->env = envp;
	data->paths = bonus_split_paths(envp);}
