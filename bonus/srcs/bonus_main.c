/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:32:16 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/24 19:48:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
		bonus_handling(argc, argv, envp);
	else
		write(STDERR, "Invalid number of arguments\n", 28);
	return (0);
}
