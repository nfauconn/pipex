/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:01:21 by user42            #+#    #+#             */
/*   Updated: 2022/05/20 17:11:58 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_data(t_data *data, char **argv, char **envp)
{
	data->infile_path = argv[1];
	data->fd_in = clean_open(data, data->fd_in, data->infile_path, O_RDONLY);
	data->cmd1 = tokenized_cmd(argv[2]);
	data->cmd2 = tokenized_cmd(argv[3]);
	data->outfile_path = argv[4];
	data->fd_out = clean_open(data, data->fd_out, data->outfile_path, O_WRONLY);
	data->env = envp;
	data->paths = split_paths(envp);
}
