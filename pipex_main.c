/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/06 15:29:57 by nfauconn         ###   ########.fr       */
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
	t_cmd	cmd;

	if (argc == 5)
	{
		cmd.infile = argv[1];
		cmd.cmd1 = tokenized_cmd(argv[2]);
		cmd.env = envp;
/* 		check_file(argv[1], argv[2], F_OK);
		check_file(argv[4], argv[3], F_OK);
		fork_id = fork();
		if (fork_id != 0)
			ft_printf("hello from main process, id %d\n", fork_id);
		else
			ft_printf("hello from child process, id %d\n", fork_id); */
		clean_end(&cmd);
	}
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	return (0);
}
