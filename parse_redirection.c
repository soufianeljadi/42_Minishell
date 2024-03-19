/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/19 01:44:32 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_next_r(char *line)
{
	int i = 0;
	int f = 0;
	if(line[i] == '>' || line[i] == '<')
		i++;
	while (line[i] != '\0')
	{
		if(line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			f = 1;
		i++;
	}
	if(f == 0)
		return(1);
	return(0);
}

int check_after(char *line)
{
	int i = 0;
	int f = 0;

	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			f = 1;
		i++;
	}
	if (f == 0)
		return (1);
	return (0);
}

int parse_redirection(char *line)
{
	int i = 0;
	int r = 0;
	while (line[i] <= 32)
		i++;
	if (line[i] == '>' || line[i] == '<')
	{
		i++;
		if (check_after(line + i) == 1)
			return (1);	
	}
	while(line[i])
	{

		if (line[i] == '>' && line[i + 1] == '<')
			return (1);
		if((line[i] == '>' && line[i - 1] != '\\') || (line[i] == '<' && line[i - 1] != '\\'))
		{
			i++;
			r = check_next_r(line + i);
		}
		i++;
	}
	if(r == 0)
		return(0);
	return(1);
}