/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:55:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/16 16:03:37 by sdiouane         ###   ########.fr       */
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

void check_next(char *line)
{
	int i = 0;
	int f = 0;
	while (line[i] != '\0')
	{
		if(line[i] != ' ' && line[i] != '\t' && line[i] != '\0' )
			f = 1;
		i++;
	}
	if(f == 0)
		syntax_error();
}

void parse_single_input(char *line, char c)
{
	int i = 0;
	while (line[i] <= 32)
		i++;
	if (line[i] == c )
		syntax_error();
	while (line[i] )
	{
		if (line[i] == c)
		{
			i++;
			check_next(line + i);
		}
		i++;
	}
}
// void parse_single_and(char *line)
// {
// 	int i = 0;
// 	while (line[i] <= 32)
// 		i++;
// 	if (line[i] == '&' )
// 		syntax_error();
// 	while (line[i] )
// 	{
// 		if (line[i] == '&')
// 		{
// 			i++;
// 			check_next(line + i);
// 		}
// 		i++;
// 	}
// }

void parse_double_input(char *line, char c)
{
	int i = 0;
	while (line[i] <= 32)
		i++;
	if (line[i] == c && line[i + 1] == c)
		syntax_error();
	while (line[i])
	{
		if (line[i] == c && line[i + 1] == c)
		{
			i = i + 2;
			check_next(line + i + 2);
		}
		i++;
	}
}

// void parse_and(char *line)
// {
// 	int i = 0;
// 	while (line[i] <= 32)
// 		i++;
// 	if (line[i] == '&' && line[i + 1] == '&')
// 		syntax_error();
// 	while (line[i])
// 	{
// 		if (line[i] == '&' && line[i + 1] == '&')
// 		{
// 			i = i + 2;
// 			check_next(line + i + 2);
// 		}
// 		i++;
// 	}
// }

void parsing(char *line)
{
    parse_single_input(line, '|');
    parse_single_input(line, '&');
    parse_double_input(line, '|');
    parse_double_input(line, '&');
	nbr_quotes(line);
}