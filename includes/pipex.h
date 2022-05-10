/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nono <nono@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:25:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/10 11:58:22 by nono             ###   ########.fr       */
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
	char	**cmd1;
	char	**cmd2;
	char	*outfile_path;
	char	**env;
}	t_data;

void	clean_end(t_data *data);
void	error_exit(t_data *data, char *s);
void	exec_cmd(t_data *data);
char	**tokenized_cmd(char *cmd);

#endif