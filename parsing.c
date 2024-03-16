/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:55:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/16 21:42:14 by sdiouane         ###   ########.fr       */
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

int parse_double_input(char *line, char c)
{
	int i = 0;
	while (line[i] <= 32)
		i++;
	if (line[i] == c && line[i + 1] == c)
		return(1);
	while (line[i])
	{
		if (line[i] == c && line[i + 1] == c)
		{
			i = i + 2;
			return(check_next(line + i));
		}
		i++;
	}
	return(0);
}


int parsing(char *line)
{
    // char *res;
    char **buff;
    int i = 0;
    // int r = 0;
	
    if (parse_single_input(line, '|'))
		return (1);
    else if (parse_single_input(line, '&'))
		return (1);
    else if (parse_double_input(line, '|'))
		return (1);
    else if (parse_double_input(line, '&'))
		return (1);
	nbr_quotes(line);

	buff = ft_split(line, '|');
	while (buff[i])
    	printf("%s\n", buff[i++]);
	// return (buff);
	return(0);
}
// int parsing(char *line)
// {
//     // char *res;
//     char **buff;
//     int i = 0;
//     int r = 0;
	
//     r = parse_single_input(line, '|');
//     r = parse_single_input(line, '&');
//     r = parse_double_input(line, '|');
//     r = parse_double_input(line, '&');
// 	nbr_quotes(line);

// 	buff = ft_split(line, '|');
// 	while (buff[i])
//     	printf("%s\n", buff[i++]);
//     	printf("%d\n",r);
// 	// return (buff);
// 	return(r);
// }



