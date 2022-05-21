/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/05/21 19:28:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_exec(t_data *data, char **cmd, int *pipe)// char **cmd, int fd_in, int fd_out)
{
	int		i;
	char	*cmd_path;
	int		redir[2];

	if (cmd == data->cmd1)
	{
		close(pipe[0]);
		redir[0] = data->fd_in;
		redir[1] = pipe[1];
	}
	else if (cmd == data->cmd2)
	{
		close(pipe[1]);
		redir[0] = pipe[0];
		redir[1] = data->fd_out;
	}
	clean_dup(data, cmd, redir[0], STDIN_FILENO);
	clean_dup(data, cmd, redir[1], STDOUT_FILENO);
	i = 0;
	while (data->paths[i])
	{
		cmd_path = ft_strjoin(data->paths[i], cmd[0]);
		execve(cmd_path, cmd, data->env);//execve(cmd_path, cmd, data->env);
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	close(redir[0]);
	close(redir[1]);
	error_exit(data, cmd[0], "command not found", NULL);
}

void	exec_cmd(t_data *data)
{
	int		pipe[2];
	pid_t	pid;
/* 	int		status;
 */
	clean_pipe_creation(data, pipe);
	pid = fork();
	if (pid < 0)
		error_exit(data, "fork", strerror(errno), NULL);
	if (pid == 0)
		child_exec(data, data->cmd1, pipe);//data->cmd1, data->fd_in, pipe[1]);
	else
	{
 		wait(NULL);
		pid = fork();
		if (pid == 0)
			child_exec(data, data->cmd2, pipe);// data->cmd2, pipe[0], data->fd_out);
		clean_close(pipe);
	}
	wait(NULL);
}
