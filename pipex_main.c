/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nono <nono@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/10 12:03:15 by nono             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void fill_data(t_data *data, char **argv, char **envp)
{
	data->infile_path = argv[1];
	data->cmd1 = tokenized_cmd(argv[2]);
	data->cmd2 = tokenized_cmd(argv[3]);
	data->outfile_path = argv[4];
	data->env = envp;
	//		printf("data->env = %s\n", data->env[1]);			/!\ IF ENV -I
}

int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc == 5)
	{
		fill_data(&data, argv, envp);
		exec_cmd(&data);
	}
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	clean_end(&data);
	printf("FINI\n");
	return (0);
}
