/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/06/06 18:42:39 by user42           ###   ########.fr       */
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
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			execve(cmd_path, cmd, env);
		}
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (0);
}		

static int	child_exec(t_data *data, t_cmd *cmd)
{
	ft_printerror("\ncmd %d ---- fd_in = %d | fd_out = %d\n", cmd->index, cmd->fd_in, cmd->fd_out);
	clean_dup(data, cmd->tab, cmd->fd_in, STDIN_FILENO);
	clean_dup(data, cmd->tab, cmd->fd_out, STDOUT_FILENO);
	if (!find_path_then_execve(cmd->tab, data->paths, data->env_tab))
	{
		ft_printerror("!!!!!!!!! %s: command n.%d not found ------- cmd->fd_in = %d | cmd->fd_out = %d\n", cmd->tab[0], cmd->index, cmd->fd_in, cmd->fd_out);
		return (1);
		//error_exit(data, cmd->tab[0], NULL, "command not found");
	}
	return (0);
}

int	exec_cmd(t_data *data)
{
	int		i;
	int		j;
//	int		fd;
	int status;
	int		redir[data->nb_cmd][2];
	pid_t	pid;
	t_cmd	*cmd;

	cmd = data->cmd;
	i = 0;
	ft_printerror("stdin = %d\nstdout = %d\ndata->fd_in = %d\ndata->fd_out = %d\n", STDIN_FILENO, STDOUT_FILENO, data->fd_in, data->fd_out);
	while (i < data->nb_cmd - 1)
	{
		clean_pipe_creation(data, redir[i]);
		ft_printerror("created pipe n.%d, redir[%d][0] = %d, redir[%d][1]= %d\n", i, i, redir[i][0], i, redir[i][1]);
		i++;
	}
	i = 0;
	j = 0;
	while (cmd && i < data->nb_cmd)
	{
		pid = fork();
		if (pid < 0)
			error_exit(data, "fork", NULL, strerror(errno));//return (errno); 
		if (pid == 0)
		{
			if (i == 0)
			{
				cmd->fd_in = data->fd_in;
				cmd->fd_out = redir[cmd->index][1];
				while (cmd->i < data->nb_cmd - 1)
				{
					close(redir[cmd->i][0]);
					if (redir[cmd->i][1] != cmd->fd_out)
						close(redir[cmd->i][1]);
					cmd->i++;
				}
				child_exec(data, cmd);
			}
			else if (i > 0 && i != data->nb_cmd - 1)
			{
				cmd->fd_in = redir[cmd->index - 1][0];
				cmd->fd_out = redir[cmd->index][1];
				while (cmd->i < data->nb_cmd - 1)
				{
					if (redir[cmd->i][0] != cmd->fd_in)
						close(redir[cmd->i][0]);
					if (redir[cmd->i][1] != cmd->fd_out)
						close(redir[cmd->i][1]);
					cmd->i++;
				}
				child_exec(data, cmd);
			}
			else
			{
				cmd->fd_in = redir[cmd->index - 1][0];
				cmd->fd_out = data->fd_out;
				while (cmd->i < data->nb_cmd - 1)
				{
					if (redir[cmd->i][0] != cmd->fd_in)
						close(redir[cmd->i][0]);
					close(redir[cmd->i][1]);
					cmd->i++;
				}
				ft_printerror("last cmd (n.%d) fd_in = %d | fd_out = %d\n", cmd->index, cmd->fd_in, cmd->fd_out);
				child_exec(data, cmd);
			}
			return (0) ;
		}
		else
		{
			close(redir[i][0]);
			close(redir[i][1]);
			cmd = cmd->next;
			i++;
		}
	}
	while (--i)
		wait(&status);
	/* HANDLE CHILD SEGV */
	return (0);
}
