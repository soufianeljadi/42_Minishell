/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:56:31 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/11 14:04:38 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_operator(char *s, int i)
{
	if (s)
	{
		if ((s[i] == '>' && s[i + 1] == '>') || \
			(s[i] == '<' && s[i + 1] == '<'))
			return (2);
		else if (s[i] == '|' || s[i] == '<' || \
			s[i] == '>')
			return (1);
	}
	return (0);
}

int	ft_scape_quotes(char *input, int i)
{
	char		qt;

	if (input)
	{
		qt = input[i];
		while (input[++i] && ((input[i] != qt) || \
			((input[i] == qt) && (!i || \
				input[i - 1] == '\\'))))
			;
	}
	return (i);
}

static int	ft_word_len(char *s, int *i)
{
	int			l;
	int			ref;

	l = ft_is_operator(s, *i);
	if (s && !l)
	{
		ref = *i;
		while (s && s[*i])
		{
			if ((s[*i] == '\'' || s[*i] == '\"') && \
				(!(*i) || s[(*i) - 1] != '\\'))
				*i = ft_scape_quotes(s, *i);
			else if (ft_is_operator(s, *i))
				break ;
			if (s[*i])
				(*i)++;
		}
		return (*i - ref);
	}
	*i += l;
	return (l);
}

char	*ft_strs_join(char *s1, char *s2)
{
	char		*str;

	str = NULL;
	if (!s1 && s2)
		str = ft_strdup(s2);
	else if (s1 && !s2)
		str = ft_strdup(s1);
	else if (s1 && s2)
		str = ft_strjoin(s1, s2);
	return (free (s1), free (s2), str);
}

char	*ft_add_sep(char *s)
{
	int			i;
	int			j;
	int			w_len;
	char		*str;

	j = 0;
	i = 0;
	str = NULL;
	while (s && s[i])
	{
		w_len = ft_word_len(s, &i);
		if (w_len)
		{
			str = ft_strs_join(str, ft_substr(s, j, w_len));
			str = ft_strs_join(str, ft_strdup(" "));
			j += w_len;
		}
	}
	return (str);
}
