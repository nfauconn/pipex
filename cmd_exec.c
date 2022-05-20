/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/05/20 17:25:35 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_exec(t_data *data, char **cmd, int fd_in, int fd_out)
{
	int		i;
	char	*cmd_path;

	clean_dup(data, cmd, fd_in, STDIN_FILENO);
	clean_dup(data, cmd, fd_out, STDOUT_FILENO);
	i = 0;
	while (data->paths[i])
	{
		cmd_path = ft_strjoin(data->paths[i], cmd[0]);
		execve(cmd_path, cmd, data->env);
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	close(fd_in);
	close(fd_out);
}

void	exec_cmd(t_data *data)
{
	int		pipe[2];
	pid_t	pid;

	clean_pipe_creation(data, pipe);
	pid = fork();
	if (pid < 0)
		error_exit(data, "fork: ", NULL, strerror(errno));
	if (pid == 0)
	{
		close(pipe[0]);
		child_exec(data, data->cmd1, data->fd_in, pipe[1]);
	}
	else
	{
		wait(NULL);
		pid = fork();
		if (pid == 0)
		{
			close(pipe[1]);
			child_exec(data, data->cmd2, pipe[0], data->fd_out);
		}
		else
			clean_close(pipe);
	}
}
