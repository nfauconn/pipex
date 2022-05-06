/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:17:14 by nfauconn          #+#    #+#             */
/*   Updated: 2022/05/06 15:24:13 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	go_through_print_whithout_ws(char **s)
{
	while (ft_isprint(**s) && !ft_is_whitespace(**s))
		(*s)++;
}

static void	go_through_whitespaces(char **s)
{
	while (ft_is_whitespace(**s))
		(*s)++;
}

static int	word_count(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count++;
		go_through_whitespaces(&s);
		go_through_print_whithout_ws(&s);
	}
	return (count);
}

char	**tokenized_cmd(char *cmd)
{
	char	*tmp;
	char	**tokenized;
	int		size;
	int		i;

	size = word_count(cmd) + 1;
	printf("cmd : %s\n", cmd);
	tokenized = (char **)malloc(sizeof(char *) * size);
	i = 0;
  	while (i++ < size)
	{
		go_through_whitespaces(&cmd);
		tmp = cmd;
		go_through_print_whithout_ws(&cmd);
		tokenized[i] = ft_substr(tmp, 0, cmd - tmp);
	}
	tokenized[size] = NULL;
	return (tokenized);
}
