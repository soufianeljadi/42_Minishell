/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/01 22:01:31 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void echo_with_option(char **args)
{
	int i;
	int j;
	
	i = 2;
	while(args[i])
	{
		j = 0;
		while(args[i][j] != '\0')
		{
			if(args[i][j] == '"')
			{
				j++;
				while(args[i][j] != '"')
				{
					printf("%c",args[i][j]);
					j++;
				}
			}
			else if(args[i][j] == '\'')
			{
				j++;
				while(args[i][j] != '\'')
				{
					printf("%c",args[i][j]);
					j++;
				}
			}
			else
				printf("%c",args[i][j]);  //normal
			j++;
		}
		if(args[i + 1])
			printf(" ");
		i++;
	}
}
static void echo_no_option(char **args)
{
	int i;
	int j;
	
	i = 1;
	while(args[i])
	{
		j = 0;
		while(args[i][j] != '\0')
		{
			if(args[i][j] == '"')
			{
				j++;
				while(args[i][j] != '"')
				{
					printf("%c",args[i][j]);
					j++;
				}
			}
			else if(args[i][j] == '\'')
			{
				j++;
				while(args[i][j] != '\'')
				{
					printf("%c",args[i][j]);
					j++;
				}
			}
			else
				printf("%c",args[i][j]);  //normal
			j++;
		}
		if(args[i + 1])
			printf(" ");				
		i++;
	}
	printf("\n");
}

static int only_n(char *s)
{
	int i;
	
	if (s && s[0] == '-')
	{
		i = 1;
		while (s[i] == 'n')
			i++;
		if(s[i] == '\0')
			return(1);
	}
	return(0);
}

void echo_fct(char **args)
{
	
	if(!strcmp(args[0],"echo") && args[1])
	{
		if(only_n(args[1]))
			echo_with_option(args);
		else
			echo_no_option(args);
	}
	else if(!strcmp(args[0],"echo") && !args[1])
		printf("\n");
	
}
