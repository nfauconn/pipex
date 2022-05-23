/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_data_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:06:32 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/23 21:04:42 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	bonus_init_data_b(t_data_b *data)
{
	data->fd_in = 0;
	data->cmd = NULL;
	data->fd_out = 1;
	data->env = NULL;
	data->paths = NULL;
}
