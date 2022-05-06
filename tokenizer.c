/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:17:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/06 14:34:04 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count++;
		while (ft_is_whitespace(*s))
			s++;
		while (ft_isprint(*s) && !ft_is_whitespace(*s))
			s++;
	}
	return (count);
}

char	**tokenized_cmd(char *cmd)
{
	char	*tmp;
	char	**tokenized;
	int		size;

	size = word_count(cmd);
	tokenized = (char **)malloc(sizeof(char *) * size + 1);
	while (*cmd)
	{
		tmp = cmd;
		while (ft_is_whitespace(*cmd))
			cmd++;
		
		cmd++;
	}
	tokenized[size + 1] = NULL;
	return (tokenized);
}
