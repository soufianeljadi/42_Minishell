/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:16:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 21:47:44 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_first_quote(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			return (i);
		i++;
	}
	return (-1);
}

static int	find_matching_quote(const char *str, char quote_type, int start)
{
	int	i;

	i = start + 1;
	while (str[i] != '\0')
	{
		if (str[i] == quote_type)
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_quotes(char *str)
{
	int	len;
	int	start;
	int	end;

	len = strlen(str);
	start = find_first_quote(str);
	end = find_matching_quote(str, str[start], start);
	if (start != -1 && end != -1)
	{
		memmove(&str[start], &str[start + 1], end - start);
		memmove(&str[end - 1], &str[end + 1], len - end);
	}
}

void	ft_rm_quotes(char *str)
{
	int		len;
	char	quote_type;
	int		start;
	int		end;

	len = strlen(str);
	if (len < 2)
		return ;
	start = find_first_quote(str);
	if (start == -1)
		return ;
	quote_type = str[start];
	end = find_matching_quote(str, quote_type, start);
	if (end == -1)
		return ;
	remove_quotes(str);
}
