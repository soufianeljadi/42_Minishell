/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:08:35 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/21 01:13:38 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_next(char *line,int i)
{
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if(line[i] == '\0')
		return(1);
	while(line[i] != '|')
	{
		if(line[i] != ' ' && line[i] != '\t' && line[i] != '\0' )
			return(0);
		i++;
	}
	return(1);
}
int parse_single_input(char *line, char c)
{
	int i = 0;
	int r = 0;
	
	while (line[i] <= 32)
		i++;
	if (line[i] == c)
		return(1);
	while (line[i])
	{
		if (line[i] == c)
		{
			i++;
			r = check_next(line , i);
			if(r == 1)
				return(1);
		}
		i++;
	}
	return(0);
}
