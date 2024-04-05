/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/05 23:12:40 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int only_spaces__(char *line, int i )
{
	int r = 0;

	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if(line[i] == '\0' || line[i] == '|')
		r = 1;
	return(r);
}

int parse_redirection(char *line)
{
	int i = 0;
	int r = 0;
	
	while (line[i] <= 32)
		i++;
	while(line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>' )|| (line[i] == '<' && line[i + 1] == '<' ))
		{
			if(line[i + 2] == '<' || line[i + 2] == '>')
			{
				r = 1;
				break;
			}
			i = i + 2;
			r = only_spaces__(line,i);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if(line[i] == '>' && line[i + 1] == '<')
			{
				r = 1;
				break;
			}
			if(line[i] == '<' && line[i + 1] == '>')
			{
				r = 1;
				break;
			}
			r = only_spaces__(line,i + 1);
		}
		i++;
	}
	if(r == 0)
		return(0);
	return(1);
}