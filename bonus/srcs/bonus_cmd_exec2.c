/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:03:00 by nono              #+#    #+#             */
/*   Updated: 2022/06/02 17:18:17 by nfauconn         ###   ########.fr       */
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

/* static void	parent_exec(t_data *data, char **cmd, int *pipe)
{

}

static void	child_exec(t_data *data, char **cmd, int *pipe)
{

}

void	last_exec(t_data *data, char **cmd, int *pipe)
{

}


void	first_exec(t_data *data, char **cmd, int *pipe)
{

} */

int	exec_cmd(t_data *data)
{
	int		status;
	int		p1[2];
	int		p2[2];
	pid_t	pid;

	clean_pipe_creation(data, p1);
	clean_pipe_creation(data, p2);
	pid = fork();
	if (pid == 0)
	{
		// first_exec
		close(p1[0]);
		close(p2[0]);
		close(p2[1]);
		clean_dup(data, data->cmd->tab, data->fd_in, STDIN_FILENO);
		clean_dup(data, data->cmd->tab, p1[1], STDOUT_FILENO);
ft_printerror("data->cmd->tab[0] = %s\n", data->cmd->tab[0]);
		if (!find_path_then_execve(data->cmd->tab, data->paths, data->env_tab))
			return (1);//error_exit(data, data->cmd->tab[0], NULL, "command not found");
	}
	else
	{
		data->cmd = data->cmd->next;
		pid = fork();
		if (pid == 0)
		{
			close(p1[1]);
			close(p2[0]);
			clean_dup(data, data->cmd->tab, p1[0], STDIN_FILENO);
//			clean_dup(data, data->cmd->tab, p2[1], STDOUT_FILENO);
//ft_printerror("data->cmd->tab[0] in 2nd exec = %s\n", data->cmd->tab[0]);
			if (!find_path_then_execve(data->cmd->tab, data->paths, data->env_tab))
				return(2);//error_exit(data, data->cmd->tab[0], NULL, "command not found");
		}
		else
		{
			data->cmd = data->cmd->next;
			pid = fork();
			if (pid == 0)
			{
				close(p1[0]);
				close(p2[1]);
				clean_dup(data, data->cmd->tab, p2[0], STDIN_FILENO);
				clean_dup(data, data->cmd->tab, p1[1], STDOUT_FILENO);
ft_printerror("data->cmd->tab[0] in third exec = %s\n", data->cmd->tab[0]);
				if (!find_path_then_execve(data->cmd->tab, data->paths, data->env_tab))
					return(3);//error_exit(data, data->cmd->tab[0], NULL, "command not found");				
			}
			else
			{
				// last exec
				data->cmd = data->cmd->next;
				pid = fork();
				if (pid == 0)
				{
					close(p1[1]);
					close(p2[0]);
					close(p2[1]);
					clean_dup(data, data->cmd->tab, p1[0], STDIN_FILENO);
					clean_dup(data, data->cmd->tab, data->fd_out, STDOUT_FILENO);
ft_printerror("data->cmd->tab[0] in last exec= %s\n", data->cmd->tab[0]);
					if (!find_path_then_execve(data->cmd->tab, data->paths, data->env_tab))
						return(4);//error_exit(data, data->cmd->tab[0], NULL, "command not found");
				}
			}
		}
	}
	close(p1[0]);
	close(p1[1]);
	close(p2[0]);
	close(p2[1]);	
	wait(&status);
	if (WIFEXITED(status))
	wait(NULL);
	wait(NULL);
/* 	i = 0;
	while (i++ < 4)
		wait(NULL); */
	return (0);
}
