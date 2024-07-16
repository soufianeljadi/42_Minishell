/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_nc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:26:40 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/15 00:39:27 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_quotes(char *s, char *f, int *i, int *x)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] != '\0' && s[*i] != quote)
	{
		f[*x] = s[*i];
		(*i)++;
		(*x)++;
	}
	if (s[*i] == '\0')
		exit(EXIT_FAILURE);
}

void	process_string(char *s, char *f)
{
	int	i;
	int	x;

	(1) && (i = 0, x = 0);
	while (s[i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && !is_blank(s))
			h_quotes(s, f, &i, &x);
		else
		{
			f[x] = s[i];
			x++;
		}
		i++;
	}
	f[x] = '\0';
}

char	*allocate_memory(char *s)
{
	char	*f;

	f = (char *)ft_malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (f == NULL)
		exit(EXIT_FAILURE);
	return (f);
}

char	*file_nc(char *s)
{
	char	*f;

	if (!s)
		return (NULL);
	f = allocate_memory(s);
	process_string(s, f);
	return (f);
}
