/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nono <nono@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/10 15:38:01 by nono             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_data(t_data *data)
{
	data->infile_path = NULL;
	data->fd_in = 0;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->outfile_path = NULL;
	data->fd_out = 1;
	data->env = NULL;
}

static void fill_data(t_data *data, char **argv, char **envp)
{
	data->infile_path = argv[1];
	data->fd_in = clean_open(data, data->fd_in, data->infile_path, O_RDONLY);
	data->cmd1 = tokenized_cmd(argv[2]);
	data->cmd2 = tokenized_cmd(argv[3]);
	data->outfile_path = argv[4];
	data->fd_out = clean_open(data, data->fd_out, data->outfile_path, O_WRONLY);
	data->env = envp;
	//		printf("data->env = %s\n", data->env[1]);			/!\ IF ENV -I
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc == 5)
	{
		init_data(&data);
		fill_data(&data, argv, envp);
		exec_cmd(&data);
	}
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	clean_end(&data);
	printf("FINI\n");
	return (0);
}
