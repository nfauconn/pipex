/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nono <nono@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/05/10 15:32:22 by nono             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void clean_dup(t_data *data, char **cmd, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		error_exit(data, "dup2: ", cmd[0], strerror(errno)); // && close(old_fd) ?
}

int clean_open(t_data *data, int fd, char *file_path, int flag)
{
	if (flag == O_RDONLY)
		fd = open(file_path, O_RDONLY);
	else if ((int)flag == (int)O_WRONLY)
		fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		error_exit(data, "open: ", file_path, strerror(errno));
	return (fd);
}

static void	create_pipe(t_data *data, int *redir)
{
	if (pipe(redir) == -1)
		error_exit(data, "pipe: ", NULL, strerror(errno));
}

void	exec_cmd(t_data *data)
{
	int	ret;
	int	pipe[2];
	int	status;
//	int	redir_cmd2[2];
	pid_t pid;

	data->fd_in = clean_open(data, data->fd_in, data->infile_path, O_RDONLY);
	data->fd_out = clean_open(data, data->fd_out, data->outfile_path, O_WRONLY);
	create_pipe(data, pipe);
	pid = fork();
	if (pid < 0)
		error_exit(data, "fork: ", NULL, strerror(errno));
	if (pid == 0)
	{
		close(pipe[0]);
//		close(data->fd_out);
		clean_dup(data, data->cmd1, data->fd_in, STDIN_FILENO);
//		close(data->fd_in);
		clean_dup(data, data->cmd2, pipe[1], STDOUT_FILENO);
//		close(pipe[1]);
		if (execve("/usr/bin/grep", data->cmd1, data->env) == -1)
			ret = 666;
	}
	else
	{
		waitpid(-1, &status, 0);
		close(pipe[1]);
		clean_dup(data, data->cmd2, pipe[0], 0);
//		close(pipe[0]);
		clean_dup(data, data->cmd2, data->fd_out, STDOUT_FILENO);
//		close(data->fd_out);
		if (execve("/usr/bin/wc", data->cmd2, data->env) == -1)
			ret = 666;
	}
/* 	close(data->fd_in);
	close(data->fd_out); */
}