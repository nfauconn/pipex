/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/23 21:04:37 by nfauconn         ###   ########.fr       */
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
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data_b
{
	int		fd_in;
	t_cmd	*cmd;
	int		fd_out;
	char	**env;
	char	**paths;
}	t_data_b;

void	bonus_clean_close(int fd[2]);
void	bonus_clean_dup(t_data_b *data, char **cmd, int old_fd, int new_fd);
void	bonus_clean_end(t_data_b *data);
int		bonus_clean_open(t_data_b *data, int fd, char *file_path, int flag);
void	bonus_clean_pipe_creation(t_data_b *data, int *redir);
void	bonus_error_exit(t_data_b *data, char *s1, char *s2, char *s3);
void	bonus_exec_cmd(t_data_b *data);
void	bonus_fill_data(t_data_b *data, int argc, char **argv, char **envp);
void	bonus_handling(int argc, char **argv, char **envp);
void	bonus_init_data_b(t_data_b *data);
char	**bonus_split_paths(char **env);
char	**bonus_tokenized_cmd(char *cmd);

#endif