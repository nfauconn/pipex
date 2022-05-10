/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nono <nono@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/05/10 12:20:51 by nono             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void clean_dup(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	close(old_fd);
}

static int clean_open(t_data *data, int fd, char *file_path, int flag)
{
	if (flag == O_RDONLY)
		fd = open(file_path, flag);
	else if (flag == O_WRONLY)
		fd = open(file_path, flag | O_APPEND);
	if (fd == -1)
		error_exit(data, strerror(errno));
	return (fd);
}

static void	create_pipe(t_data *data, int *redir)
{
	if (pipe(redir) != 0)
		error_exit(data, strerror(errno));
}

void	exec_cmd(t_data *data)
{
	int	redir_cmd1[2];
	int	redir_cmd2[2];
	int pid;

	redir_cmd1[0] = 0;
	redir_cmd1[1] = 1;
	create_pipe(data, redir_cmd1);
	pid = fork();
	if (pid == 0)
	{
		redir_cmd1[0] = clean_open(data, redir_cmd1[0], data->infile_path, O_RDONLY);
		clean_dup(redir_cmd1[0], 0);
		clean_dup(redir_cmd1[1], 1);
		execve("/usr/bin/grep", data->cmd1, data->env);
	}
	else
	{
		redir_cmd2[0] = redir_cmd1[0];
		close(redir_cmd1[0]);
		close(redir_cmd1[1]);		
		create_pipe(data, redir_cmd2);
		pid = fork();
		if (pid == 0)
		{
			clean_dup(redir_cmd2[0], 0);
			redir_cmd2[1] = clean_open(data, redir_cmd2[1], data->outfile_path, O_WRONLY);
			clean_dup(redir_cmd2[1], 1);
			execve("/usr/bin/wc", data->cmd2, data->env); // == -1)
		}
		else
		{
			close(redir_cmd2[0]);
			close(redir_cmd2[1]);
			wait(NULL);
		}
	}
	wait(NULL);
}