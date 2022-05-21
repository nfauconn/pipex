/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:06:32 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/20 17:06:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data)
{
	data->infile_path = NULL;
	data->fd_in = 0;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->outfile_path = NULL;
	data->fd_out = 1;
	data->env = NULL;
	data->paths = NULL;
}
