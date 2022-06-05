/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:01:21 by user42            #+#    #+#             */
/*   Updated: 2022/06/05 16:35:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	add_to_list(t_cmd **list, int index, char *cmd)
{
	t_cmd	*new;
	t_cmd	*tmp;

	if (!*list)
	{
		*list = (t_cmd *)malloc(sizeof(t_cmd));
		(*list)->i = 0;
		(*list)->index = index;
		(*list)->fd_in = STDIN_FILENO;
		(*list)->fd_out = STDOUT_FILENO;
		(*list)->tab = tokenized_cmd(cmd);
		(*list)->next = NULL;
	}
	else
	{
		new = (t_cmd *)malloc(sizeof(t_cmd));
		new->i = 0;
		new->index = index;
		new->fd_in = STDIN_FILENO;
		new->fd_out = STDOUT_FILENO;
		new->tab = tokenized_cmd(cmd);
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}

static void	fill_cmd_list(t_cmd **cmd_list, int nb_cmd, char **argv)
{
	int		i;

	i = 0;
	while (i < nb_cmd)
	{
		add_to_list(cmd_list, i, argv[i + 2]);
		i++;
	}
}

void	fill_data(t_data *data, int ac, char **argv, char **envp)
{
	data->nb_cmd = ac - 3;
	data->fd_in = clean_open(data, data->fd_in, argv[1], O_RDONLY);
	fill_cmd_list(&data->cmd, data->nb_cmd, argv);
	data->fd_out = clean_open(data, data->fd_out, argv[ac - 1], O_WRONLY);
	data->env = env_list(envp);
	data->paths = split_paths(envp);

//	cmd_list_iter(data->cmd, ft_2D_array_display);
}
