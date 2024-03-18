/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/18 23:05:39 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_env(char **env)
{
	s_env *lst = NULL;
	lst->env = env;
}

int only_spaces(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);	
	}
	return(1);
}


int main(int ac, char **av, char **env)
{
	((void)ac, (void)av);
	(void)env;	
	char *line = NULL;
	Token **token;
	while (1)
	{  
		if((line = readline("Minishell :$ "))!= NULL  && only_spaces(line) == 0)
		{
			if (!line)
			    break;
			add_history(line);
			if(parsing(line) == 1)		
				syntax_error();
			else
			{
				token = parse_command(line);
				print_tokens(token);
			}
			if (strncmp(line, "exit", 4) == 0)
			{
				printf("exit\n");
				free(line);
				break;
			}
		}
		free(line);
	}
	return 0;
}
