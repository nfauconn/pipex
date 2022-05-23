/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cmd_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:17:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/23 20:15:51 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

int	is_blank(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static int	word_count(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count++;
		while (*s && is_blank(*s))
			s++;
		while (*s && !is_blank(*s))
			s++;
	}
	return (count);
}

char	**tokenized_cmd(char *cmd)
{
	char	*tmp;
	char	**tokenized;
	int		size;
	int		i;

	size = word_count(cmd);
	tokenized = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		while (*cmd && is_blank(*cmd))
			cmd++;
		tmp = cmd;
		while (*cmd && !is_blank(*cmd))
			cmd++;
		tokenized[i] = ft_substr(tmp, 0, cmd - tmp);
		i++;
	}
	tokenized[size] = NULL;
	return (tokenized);
}
