/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/03 19:10:56 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	only_spaces__(char *line, int i)
{
	int	r;

	r = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '|')
		r = 1;
	return (r);
}

static	void	check_line(char *line, int i, int r)
{
	while (line[i] != '\0')
	{
		if ((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<'))
		{
			if (line[i + 2] == '<' || line[i + 2] == '>')
			{
				r = 1;
				break ;
			}
			i = i + 2;
			r = only_spaces__(line, i);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if ((line[i] == '>' && line[i + 1] == '<')
				|| (line[i] == '<' && line[i + 1] == '>'))
			{
				r = 1;
				break ;
			}
			r = only_spaces__(line, i + 1);
		}
		i++;
	}
}

int	parse_redirection(char *line)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (line[i] <= 32)
		i++;
	while (line[i] != '\0')
	{
		check_line(line, i, r);
		i++;
	}
	if (r == 0)
		return (0);
	return (1);
}
