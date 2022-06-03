/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/05/25 17:51:04 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	find_path_then_execve(char **cmd, char **paths, char **env)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd[0]);
		execve(cmd_path, cmd, env);
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (0);
}

static void	child_exec(t_data *data, char **cmd, int *pipe)
{
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
	if (!find_path_then_execve(cmd, data->paths, data->env))
	{
		close(redir[0]);
		close(redir[1]);
		error_exit(data, cmd[0], NULL, "command not found");
	}
}

void	exec_cmd(t_data *data)
{
	int		pipe[2];
	pid_t	pid;

	clean_pipe_creation(data, pipe);
	pid = fork();
	if (pid < 0)
		error_exit(data, "fork", NULL, strerror(errno));
	if (pid == 0)
		child_exec(data, data->cmd1, pipe);
	else
	{
		pid = fork();
		if (pid == 0)
			child_exec(data, data->cmd2, pipe);
		clean_close(pipe);
	}
	wait(NULL);
	wait(NULL);
}
