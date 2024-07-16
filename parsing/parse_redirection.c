/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/09 22:56:33 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	only_spaces__(char *line, int i)
{
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}

static int	process_double_redirect(char *line, int i, int *r)
{
	if (line[i + 2] != '\0' && (line[i + 2] == '<' || line[i + 2] == '>'))
	{
		*r = 1;
		return (i);
	}
	i += 2;
	*r = only_spaces__(line, i);
	if (*r)
		return (i);
	return (i);
}

static int	process_single_redirect(char *line, int i, int *r)
{
	if (line[i + 1] == '\0')
	{
		*r = 1;
		return (i);
	}
	*r = only_spaces__(line, i + 1);
	if (*r)
		return (i);
	return (i);
}

static int	check_line(char *line, int i, int *r)
{
	while (line[i] != '\0')
	{
		if (line[i + 1] != '\0'
			&& ((line[i] == '>' && line[i + 1] == '>')
				|| (line[i] == '<' && line[i + 1] == '<')))
		{
			i = process_double_redirect(line, i, r);
			if (*r)
				break ;
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			i = process_single_redirect(line, i, r);
			if (*r)
				break ;
		}
		i++;
	}
	return (i);
}

int	parse_redirection(char *line)
{
	int	i;
	int	r;
	int	t;

	i = 0;
	r = 0;
	t = 0;
	while (line[i] != '\0' && line[i] <= 32)
		i++;
	i = check_line(line, i, &r);
	if (r == 1)
		return (1);
	return (0);
}
