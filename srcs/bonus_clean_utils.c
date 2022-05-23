/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_clean_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:02:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/23 21:04:39 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	bonus_clean_close(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	bonus_clean_dup(t_data_b *data, char **cmd, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		bonus_error_exit(data, "dup2: ", cmd[0], strerror(errno));
	close(old_fd);
}

int	bonus_clean_open(t_data_b *data, int fd, char *file_path, int flag)
{
	if (flag == O_RDONLY)
		fd = open(file_path, O_RDONLY);
	else if ((int)flag == (int)O_WRONLY)
		fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		bonus_error_exit(data, "open: ", file_path, strerror(errno));
	return (fd);
}

void	bonus_clean_pipe_creation(t_data_b *data, int *redir)
{
	if (pipe(redir) == -1)
		bonus_error_exit(data, "pipe: ", strerror(errno), NULL);
}
