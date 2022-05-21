/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:21:00 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/20 12:34:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_paths(char **env)
{
	int		i;
	char	*trunc;
	char	**paths;

	paths = NULL;
	while (env && *env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			trunc = ft_substr(*env, 5, ft_strlen(*env));
			paths = ft_split(trunc, ':');
			free(trunc);
			i = 0;
			while (paths[i])
			{
				ft_strfjoin(&paths[i], "/");
				i++;
			}
			return (paths);
		}
		env++;
	}
	return (paths);
}
