/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/30 12:58:05 by sdiouane         ###   ########.fr       */
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
			// printf("K:%s_____________\n",s_env->key);
			// printf("V:%s_____________\n\n",s_env->value);
		if(!strcmp(s_env->key,str))
		{
			printf("%s",s_env->value);
			return(1);
		}
		s_env=s_env->next;
	}
	return(0);
}
static void echo_with_option(char **args, s_env *s_env)
{
	int i;
	int j;
	
	i = 2;
	if (check_variables(args, s_env) == 1)
	{
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
}



// $chi sauce !
static void echo_no_option(char **args, s_env *s_env)
{
	int i;
	int j;
	
	i = 1;
	if (check_variables(args, s_env) == 1)
	{
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
			}
				if(args[i + 1])
					printf(" ");				
			i++;
		}
	}
		printf("\n");
}
//make it accept char **args  : echo -n -nnn hola -nnnn
static int only_n(char *s)
{
	int i;
	int j;
	char *str = malloc(ft_strlen(s));
	
	i = 0;
	j = 0;
	if(s[j] == '"')
	{
		j++;
		while(s[j]  != '"')
		{
			str[i] = s[j];
			i++;
			j++;
		}
	}
	else { 
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	if (str && str[0] == '-')
	{
		i = 1;
		while (str[i] == 'n')
			i++;
		if(str[i] == '\0')
			return(1);
	}
	else if(str && !strncmp(str,"-n",2))
	{
		free(str);
		return(1);
	}
	free(str);
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

// int all__args_n(char **s1)
// {
//     int i = 0;

//     if(s1[i] == '-' && s1[i + 1] == 'n')
//     {
//         i++;
//         while(s1[i])
//         {
//             if(s1[i] != 'n')
//                 return (1);
//             i++;
//         }
//         return (0);
//     }
//     return (1);
// }

void echo_fct(char **args, s_env *s_env)
{
	if((!strcmp(args[0],"echo") && !args[1] )|| all__args_n(args))
		printf("\n");
	else if(!strcmp(args[0],"echo") && args[1])
	{
		if(only_n(args[1]))
			echo_with_option(args, s_env);
		else
			echo_no_option(args, s_env);
	}
}
