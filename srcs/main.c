/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/23 22:31:44 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bonus_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		handling(argv, envp);
	else if (argc > 5)
		bonus_handling(argc, argv, envp);
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	return (0);
}
