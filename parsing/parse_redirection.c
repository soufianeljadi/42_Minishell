/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/25 21:38:02 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int only_spaces__(char *line, int i)
{
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] == '|')
		return 1;
	return 0;
}

static void check_line(char *line, int i, int *r)
{
	while (line[i] != '\0')
	{
		if (line[i + 1] != '\0' && ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<')))
		{
			if (line[i + 2] != '\0' && (line[i + 2] == '<' || line[i + 2] == '>'))
			{
				*r = 1;
				break;
			}
			i += 2;
			*r = only_spaces__(line, i);
			if (*r)
				break;
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == '\0')
			{
				*r = 1;
				break;
			}
			*r = only_spaces__(line, i + 1);
			if (*r)
				break;
		}
		i++;
	}
}

int parse_redirection(char *line)
{
	int i;
	int r;
	
	i = 0;
	r = 0;
	while (line[i] != '\0' && line[i] <= 32)
		i++;
	check_line(line, i, &r);
	if (r == 0)
		return 0;
	return 1;
}