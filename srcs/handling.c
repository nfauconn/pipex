/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:07:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/23 22:31:12 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handling(char **argv, char **envp)
{
	t_data	data;

	init_data(&data);
	fill_data(&data, argv, envp);
	exec_cmd(&data);
	clean_end(&data);
}
