/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:06:32 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/24 19:51:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	init_data(t_data *data)
{
	data->fd_in = 0;
	data->cmd = NULL;
	data->fd_out = 1;
	data->env = NULL;
	data->paths = NULL;
}
