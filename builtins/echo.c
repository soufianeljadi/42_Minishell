/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/15 22:20:20 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo_dollar(char *args, s_env *s_env)
{
	char *str;
	
	if(!strcmp(args,"$$"))
	{
		printf("%d",getpid());
		return(1);
	}
	str = args + 1; 
	while(s_env)
	{
		if(!strcmp(s_env->key,str))
		{
			printf("%s",s_env->value);
			return(1);
		}
		s_env=s_env->next;
	}
	return(0);
}
static void echo_with_option(char **args, s_env *s_env, int i)
{
	int j;

		if(!strncmp(args[i],"$",1) && echo_dollar(args[i],s_env))
		;
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

static void echo_no_option(char **args, s_env *s_env,int q)
{
	int i;
	int j;
	
	(void)q;
	i = 1;

		while(args[i])
		{
		if(!strncmp(args[i],"$",1) && echo_dollar(args[i],s_env))
		;
			else 
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
					else if(args[i][j] == '\'' && args[i][j + 1] != '\0')
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
			}
				if(args[i + 1])
					printf(" ");				
			i++;
		}
		printf("\n");
}
// make it accept char **args  : echo -n -nnn hola -nnnn
static int only_n(char **args)
{
	int i;
	int j;
	int x;
	int flag = 0;
	char *str = NULL; 
	
	x = 1;
	while(args[x])
	{
		i = 0;
		j = 0;
		str = malloc(ft_strlen(args[x]) + 1);
		if(args[x][j] == '"')
		{
			j++;
			while(args[x][j]  != '"')
			{
				str[i] = args[x][j];
				i++;
				j++;
			}
		}
		else
		{ 
			while(args[x][j]  != '\0')
			{
				str[i] = args[x][j];
				i++;
				j++;
			}
		}
		str[i] = '\0';
		if(x == 1 && strncmp(str,"-n",2))
			return(0);
		if (str && str[0] == '-')
		{
			i = 1;
			while (str[i] == 'n')
				i++;
			if(str[i] == '\0' && args[x + 1])
				flag = 1;
			if(str[i] != '\0' && flag == 0)
				return(0);
			if(str[i] != '\0' && flag == 1)
				return(x);
			if(str[i] == '\0' && !args[x + 1])
				return(-1);
		}
		else
			return(x);
		free(str);
		x++;
	}
	return(0);
}

static int all__args_n(char **args)
{
	int i;
	
	i = 1;
	while(args[i])
	{
		if(strncmp(args[i],"-n",2))
			return(0);
		i++;
	}
	return(1);
}

void echo_fct(char **args, s_env *s_env)
{

	if((!strcmp(args[0],"echo") && !args[1] )|| all__args_n(args))
		printf("\n");
	else if(!strcmp(args[0],"echo") && args[1])
	{
		if(only_n(args))
			echo_with_option(args, s_env,only_n(args));
		else
			echo_no_option(args, s_env,only_n(args));
	}
}
