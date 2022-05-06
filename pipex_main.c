/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/06 17:48:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* static void	check_file(char *file, char *cmd, int mode)
{
	char	*tmp;
	int		end_name;

	tmp = cmd;
	while (*tmp != 32 || (*tmp < 9 && *tmp > 13))
		tmp++;
	end_name = tmp - cmd;
	access(file, mode);
	if (errno != 0)
	{
		ft_printf("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
} */

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		fork_id;

	if (argc == 5)
	{
		data.infile_path = argv[1];
		data.cmd1 = tokenized_cmd(argv[2]);
		data.cmd2 = tokenized_cmd(argv[3]);
		data.outfile_path = argv[4];
		data.env = envp;
		if (pipe(data.fd) != 0)
			error_exit(&data, strerror(errno));
		fork_id = fork();
		if (fork_id == 0)
		{
			data.fd[0] = open(data.infile_path, O_RDONLY);
			if (data.fd[0] == -1)
				error_exit(&data, strerror(errno));
			dup2(data.fd[0], 0);
			execve(data.cmd1[0], data.cmd1, data.env);
		}
		else
		{
			wait(NULL);
		}
		clean_end(&data);
	}
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	return (0);
}
