/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:29:04 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/31 16:47:36 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

void	cmd_list_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*curr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

void	cmd_list_clear(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*curr;

	curr = *lst;
	while (curr)
	{
		del(curr->tab);
		free(curr);
		curr = curr->next;
	}
	*lst = NULL;
}

void	cmd_list_iter(t_cmd *lst, void (f)(char **))
{
	while (lst)
	{
		f(lst->tab);
		lst = lst->next;
	}
}
