/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:55:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/17 00:21:21 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void nbr_quotes(char *str)
{
	int i = 0;
	int cmp1 = 0;
	int cmp2 = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '"' && str[i - 1] != '\\')
			cmp1++;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
			cmp2++;
		i++;
	}
	
	if (cmp1 % 2 != 0 || cmp2 % 2 != 0)
		printf("error\n");
}

void syntax_error()
{
	printf("syntax error \n");
}

int check_next(char *line)
{
	int i = 0;
	int f = 0;
	if(line[i] == '|')
		return(1);
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
	if(r == 0)
		return(0);
	return(1);
}

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
int parse_redirection(char *line)
{
	int i = 0;
	int r = 0;
	while (line[i] <= 32)
		i++;
	if (line[i] == '>'|| line[i] == '<')
		return(1);
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

int parsing(char *line)
{
    if (parse_single_input(line, '|'))
		return (1);
	nbr_quotes(line);
	if(parse_redirection(line))
		return (1);
	return(0);
}

