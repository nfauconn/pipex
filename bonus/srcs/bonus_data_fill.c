/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:01:21 by user42            #+#    #+#             */
/*   Updated: 2022/05/25 13:05:39 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	fill_data(t_data *data, int ac, char **argv, char **envp)
{
	int	i;

	data->fd_in = clean_open(data, data->fd_in, argv[1], O_RDONLY);
	data->cmd = (t_cmd *)malloc(sizeof(t_cmd) * (ac - 3));
	i = 2;
	while (i < ac)
	{
		data->cmd->tab = tokenized_cmd(argv[i]);
		printf("cmd[%d] = %s\n", i, data->cmd->tab[0]);
		data->cmd = data->cmd->next;
	}
	data->fd_out = clean_open(data, data->fd_out, argv[ac - 1], O_WRONLY);
	data->env = envp;
	data->paths = split_paths(envp);
}
