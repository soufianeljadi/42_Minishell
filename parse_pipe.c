/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:08:35 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/20 21:09:28 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_next__(char *line)
{
	int i = 0;
	int f = 0;
		
	if(line[i] == '|')
	{
		syntax_error();
		return ;
	}
	while (line[i] != '\0')
	{
		if((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			f = 1;
		i++;
	}
	if (f == 0)
	{
		syntax_error();
		return ;
	}
}

void parse_after_pipe(char *line)
{
	int i = 0;
	while (line[i] <= 32)
		i++;
	if (line[i] == '|')
		syntax_error();
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			check_next__(line + i);
		}
		i++;
	}
}

int check_next(char *line)
{
	int i = 0;
	int j = 0;
	int f = 0;
	char *prompt = NULL;
		
	if(line[i] == '|')
		return(1);
	if(!line[i])
	{
		prompt = readline("pipe > ");
		parse_after_pipe(prompt + j);
	}
	while (line[i] != '\0')
	{
		if((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		{
			f = 1;
			j = i;
		}
		i++;
	}
	if (f == 1)
	{
		prompt = readline("pipe > ");
		parse_after_pipe(prompt + j);
	}
	return(0);
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
			r = check_next(line + i);
		}
		i++;
	}
	if(r == 1)
		return(1);
	return(0);
}
