/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/06/04 14:58:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

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

static void	child_exec(t_data *data, t_cmd *cmd, int read_fd, int write_fd)
{
	clean_dup(data, cmd->tab, read_fd, STDIN_FILENO);
	clean_dup(data, cmd->tab, write_fd, STDOUT_FILENO);
	if (!find_path_then_execve(cmd->tab, data->paths, data->env_tab))
	{
		error_exit(data, cmd->tab[0], NULL, "command not found");
	}
}

int	exec_cmd(t_data *data)
{
	int		i;
	int		j;
	int		fd_in;
	int		fd_out;
	int		redir[data->nb_cmd][2];
	pid_t	pid;
	t_cmd	*tmp;

	tmp = data->cmd;
	i = 0;
	while (i < data->nb_cmd)
	{
		clean_pipe_creation(data, redir[i]);
		i++;
	}
	i = 0;
	j = 0;
	while (tmp && i < data->nb_cmd)
	{
		pid = fork();
		if (pid < 0)
			error_exit(data, "fork", NULL, strerror(errno));//return (errno); 
		if (pid == 0)
		{
			if (i == 0)
			{
				close(redir[0][0]);
				while (redir[++i])
				{
					close(redir[i][0]);
					close(redir[i][1]);
				}
				i = 0;
				child_exec(data, tmp, data->fd_in, redir[i][1]);
			}
			else if (i != data->nb_cmd - 1)
			{
				close(redir[i][0]);
				close(redir[i - 1][1]);
				fd_in = redir[i - 1][0];
				fd_out = redir[i][1];
				j = i;
				i = 0;
				while (redir[i])
				{
					if (redir[i][0] != fd_in)
						close(redir[i][0]);
					if (redir[i][1] != fd_out)
						close(redir[i][1]);
					i++;
				}
				i = j;
				child_exec(data, tmp, redir[i - 1][0], redir[i][1]);
			}
			else
			{
				close(redir[i][1]);
				fd_in = redir[i][0];
				j = i;
				i = 0;
				while (redir[i])
				{
					if (redir[i][0] != fd_in)
						close(redir[i][0]);
					close(redir[i][1]);
				}
				child_exec(data, tmp, redir[i][0], data->fd_out);
			}
			break ;
		}
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	i = 0;
	while (i++ < data->nb_cmd - 1)
		wait(NULL);
	return (0);
}
