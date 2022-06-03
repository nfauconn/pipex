/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:22:10 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/31 16:02:22 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

t_list	*env_list(char **env)
{
	int		i;
	int		len;
	t_list	*env_list;
	t_list	*new;

	len = 0;
	while (env[len])
		len++;
	env_list = NULL;
	i = 0;
	while (env[i])
	{
		new = (t_list *)malloc(sizeof(t_list));
	 	new->content = ft_strdup(env[i]);
		new->next = NULL;
		ft_lstadd_back(&env_list, new);
		i++;
	}
/* 	t_list *tmp;
	int j = 0;
	tmp = env_list;
	while (tmp)
	{
		printf("env_list elem %d = %s\n", j, (char *)tmp->content);
		tmp = tmp->next;
		j++;
	} */
	return (env_list);
}

char	**env_tab(char **env)
{
	int		i;
	int		len;
	char	**env_tab;

	len = ft_2D_array_size(env);
	env_tab = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (env[i])
	{
		env_tab[i] = ft_strdup(env[i]);
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}