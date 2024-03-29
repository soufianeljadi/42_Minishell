/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/29 22:05:25 by sdiouane         ###   ########.fr       */
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
			if(args[i][j] != '"' && args[i][j] != '\'' && args[i][j] != '\\')
				printf("%c",args[i][j]);
			else if((args[i][j] == '"' || args[i][j] == '\'') && args[i][j - 1] == '\\')
				printf("%c",args[i][j]);
			else if(args[i][j] == '\\' && args[i][j + 1] == '\\')
			{
				printf("%c",args[i][j]);
				j++;
			}
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
			if(args[i][j] != '"' && args[i][j] != '\'' && args[i][j] != '\\')
				printf("%c",args[i][j]);
			else if((args[i][j] == '"') && args[i][j - 1] == '\\')
				printf("%c",args[i][j]);
			else if((args[i][j] == '\'') && args[i][j - 1] == '\\')
			{
				printf("%c",args[i][j - 1]);
				printf("%c",args[i][j]);
			}
			else if(args[i][j] == '\\' && args[i][j + 1] == '\\')
			{
				printf("%c",args[i][j]);
				j++;
			}
			j++;
		}
		if(args[i + 1])
			printf(" ");				
		i++;
	}
	printf("\n");
}

void echo_fct(char **args)
{
	
	if(!strcmp(args[0],"echo") && args[1])
	{
		if(!strcmp(args[1],"-n"))
			echo_with_option(args);
		else
			echo_no_option(args);
	}
	else if(!strcmp(args[0],"echo") && !args[1])
		printf("\n");
	
}
