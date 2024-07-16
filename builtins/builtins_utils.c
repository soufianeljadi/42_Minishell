/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:38:51 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/14 00:15:33 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_token(char **t, int *tc, const char *start, int length)
{
	t[*tc] = ft_malloc(sizeof(char) * (length + 1));
	ft_strncpy(t[*tc], start, length);
	t[*tc][length] = '\0';
	(*tc)++;
}

static void	skip_whitespace(const char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
}

char	**split_with_quotes(const char *text)
{
	char		**tokens;
	int			tc;
	int			in_q;
	const char	*start;
	const char	*end;

	(1) && (tc = 0, in_q = 0, start = text, end = text);
	tokens = ft_malloc(sizeof(char *) * MAX_TOKEN_LENGTH);
	while (*end != '\0')
	{
		if (*end == '"' || *end == '\'')
			(1) && (in_q = !in_q, end++);
		else if ((*end == ' ' || *end == '\t') && !in_q)
		{
			if (end > start)
				add_token(tokens, &tc, start, end - start);
			(skip_whitespace(&end), start = end);
		}
		else
			end++;
	}
	if (end > start)
		add_token(tokens, &tc, start, end - start);
	tokens[tc] = NULL;
	return (tokens);
}
