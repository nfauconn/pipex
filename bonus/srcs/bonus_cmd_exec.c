/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/06/06 19:30:11 by user42           ###   ########.fr       */
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

static int	child_exec(t_data *data, t_cmd *cmd)
{
	if (cmd->index == 0)

//	ft_printerror("\ncmd %d ---- fd_in = %d | fd_out = %d\n", cmd->index, cmd->fd_in, cmd->fd_out);
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
	int		prev_output;
	int		redir[data->nb_cmd][2];
	pid_t	pid;
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		clean_pipe_creation(data, redir[cmd->index]);
		pid = fork();
		if (pid < 0)
			error_exit(data, "fork", NULL, strerror(errno));//return (errno); 
		if (pid == 0)
		{
			if (cmd->index == 0)
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
			else if (cmd->index > 0 && cmd->index != data->nb_cmd - 1)
			{
				cmd->fd_in = prev_output;
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
				child_exec(data, cmd);
			}
			return (0) ;
		}
		else
		{
			if (cmd->index != data->nb_cmd - 1)
				prev_output = redir[cmd->index][0];
			else
				close(redir[cmd->index][0]);
			if (cmd->index != 0)
				close(redir[cmd->index - 1][0]);
			close(redir[cmd->index][1]);
			sleep(1);
			cmd = cmd->next;
		}
	}
 	int	i;
	i = 0;
/*	while (i < data->nb_cmd - 1)
	{
		close(redir[i][0]);
		close(redir[i][1]);
	}
	i = 0; */
	while (i++ < data->nb_cmd - 1)
	{
		wait(NULL);
	}
	return (0);
}
