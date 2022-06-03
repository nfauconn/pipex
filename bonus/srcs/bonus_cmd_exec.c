/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/06/03 18:12:41 by nfauconn         ###   ########.fr       */
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

static void	child_exec(t_data *data, t_cmd *cmd, int *write_fd, int *read_fd)
{
//	int		redir[2];

	close(write_fd[0]);
	close(read_fd[1]);
/* 	redir[0] = data->fd_in;
	redir[1] = pipe[1];*/
	clean_dup(data, cmd->tab, read_fd[0], STDIN_FILENO); 
	clean_dup(data, cmd->tab, write_fd[1], STDOUT_FILENO);
	if (!find_path_then_execve(cmd->tab, data->paths, data->env_tab))
	{
		close(read_fd[0]);
		close(write_fd[1]);
		error_exit(data, cmd->tab[0], NULL, "mid command not found");
	}
}

static void	child_first_exec(t_data *data, t_cmd *cmd, int *write_fd, int *read_fd)
{
	close(read_fd[0]);
	close(read_fd[1]);
	close(write_fd[0]);
	clean_dup(data, cmd->tab, data->fd_in, STDIN_FILENO);
	clean_dup(data, cmd->tab, write_fd[1], STDOUT_FILENO);
	if (!find_path_then_execve(cmd->tab, data->paths, data->env_tab))
	{
		error_exit(data, cmd->tab[0], NULL, "first command not found");
	}
}

static void	child_last_exec(t_data *data, t_cmd *cmd, int *write_fd, int *read_fd)
{
	close(read_fd[1]);
	close(write_fd[0]);
	close(write_fd[1]);
	clean_dup(data, cmd->tab, read_fd[0], STDIN_FILENO);
	clean_dup(data, cmd->tab, data->fd_out, STDOUT_FILENO);
	if (!find_path_then_execve(cmd->tab, data->paths, data->env_tab))
	{
		error_exit(data, cmd->tab[0], NULL, "last command not found");
	}
}

int	exec_cmd(t_data *data)
{
	int		i;
	int		parent_to_child[2];
	int		child_to_parent[2];
	pid_t	pid;
	t_cmd	*tmp;

	tmp = data->cmd;
	i = 0;

	while (tmp && i < data->nb_cmd)
	{
		clean_pipe_creation(data, parent_to_child);
		clean_pipe_creation(data, child_to_parent);
		pid = fork();
		if (pid < 0)
			error_exit(data, "fork", NULL, strerror(errno));//return (errno); 
		if (pid == 0)
		{
			if (i == 0)
				child_first_exec(data, tmp, child_to_parent, parent_to_child);
			else if (i == data->nb_cmd - 1 && i % 2)
				child_last_exec(data, tmp, child_to_parent, parent_to_child);
			else if (i == data->nb_cmd - 1 && !(i % 2))
				child_last_exec(data, tmp, child_to_parent, parent_to_child);
			else if (!(i % 2))
				child_exec(data, tmp, child_to_parent, parent_to_child);
			else
				child_exec(data, tmp, parent_to_child, child_to_parent);
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
