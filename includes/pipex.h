/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/20 17:21:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_data
{
	char	*infile_path;
	int		fd_in;
	char	**cmd1;
	char	**cmd2;
	char	*outfile_path;
	int		fd_out;
	char	**env;
	char	**paths;
}	t_data;

void	clean_close(int fd[2]);
void	clean_dup(t_data *data, char **cmd, int old_fd, int new_fd);
void	clean_end(t_data *data);
int		clean_open(t_data *data, int fd, char *file_path, int flag);
void	clean_pipe_creation(t_data *data, int *redir);
void	error_exit(t_data *data, char *s1, char *s2, char *s3);
void	exec_cmd(t_data *data);
void	fill_data(t_data *data, char **argv, char **envp);
void	init_data(t_data *data);
char	**split_paths(char **env);
char	**tokenized_cmd(char *cmd);

#endif