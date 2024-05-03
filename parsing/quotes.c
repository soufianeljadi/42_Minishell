/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:25:30 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/03 19:21:03 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_first_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"'))
			return (s[i]);
		i++;
	}
	return (0);
}

int	ft_next_quote(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		if (count == 2)
			return (i);
		i++;
	}
	return (0);
}

int	line_has_quotes(char **line)
{
	int		i;
	int		has_q;

	i = -1;
	has_q = 0;
	while ((*line)[++i] != '\0')
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			has_q = 1;
	}
	if (has_q == 1)
		return (1);
	return (0);
}

int	ft_quots(char **line)
{
	int		i;
	char	first_quote;
	int		end_quote;
	char	f;

	i = -1;
	if (line_has_quotes(line))
	{
		while ((*line)[++i])
		{
			f = 0;
			f = ft_first_quote((*line) + i);
			if (f != 0)
				first_quote = f;
			else if (f == 0)
				break ;
			end_quote = ft_next_quote((*line) + i, first_quote);
			i += end_quote;
			if (end_quote == 0)
				break ;
		}
		if (end_quote == 0 && first_quote != 0)
			return (1);
	}
	return (0);
}
