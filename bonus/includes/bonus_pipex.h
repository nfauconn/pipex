/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/05 16:33:53 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PIPEX_H
# define BONUS_PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CHILD 0

typedef struct s_cmd
{
	char			**tab;
	int				i;
	int				index;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int		nb_cmd;
	int		fd_in;
	t_cmd	*cmd;
	int		fd_out;
	t_list	*env;
	char	**env_tab;
	char	**paths;
}	t_data;

void	clean_close(int fd[2]);
void	clean_dup(t_data *data, char **cmd, int old_fd, int new_fd);
void	clean_end(t_data *data);
int		clean_open(t_data *data, int fd, char *file_path, int flag);
void	clean_pipe_creation(t_data *data, int *redir);
char	**env_tab(char **env);
void	error_exit(t_data *data, char *s1, char *s2, char *s3);
int	exec_cmd(t_data *data);
void	fill_data(t_data *data, int argc, char **argv, char **envp);
void	handling(int argc, char **argv, char **envp);
void	init_data(t_data *data);
t_list	*env_list(char **env);
char	**split_paths(char **env);
char	**tokenized_cmd(char *cmd);

/* LST UTILS */
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	cmd_list_clear(t_cmd **lst, void (*del)(void *));
void	cmd_list_iter(t_cmd *lst, void (f)(char **));

#endif