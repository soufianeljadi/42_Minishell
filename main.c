/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:02:35 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/03/23 00:42:24 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **init_env(char **env)
{
	if (!env || !(*env))
		return (NULL);
	char **new_env = NULL;
	new_env = env;
	return (new_env);
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

int get_len_env(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);	
}

void check_variables(char *line, s_env	*lst)
{
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] == '"')
		{
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\t')
		{
			i++;
			while (lst)
			{
				if (strcmp(line + i, lst->key) == 0)
				{
					printf("%s\n", lst->value);
				}
				lst = lst->next;
			}
		}
		}
		i++;
	}
}

s_env *split_env(char **env)
{
	int i = 0;
	int j = 0;
	s_env	*lst = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		ft_lstadd_back(&lst, ft_lstnew_data(ft_substr(env[i] ,j + 1 ,strlen(env[i])) ,ft_substr(env[i] ,0 , j)));
		i++;
	}
	return (lst);
}

int main(int ac, char **av, char **env)
{
	(void)av;
	if(ac == 1)
	{
		//env bouhdha
		char **new_env;
		new_env = env;
		s_env *lst = NULL;
		
		//signals
		char *line = NULL;
		rl_catch_signals = 0;
		signal(SIGQUIT, signal_ctrl_c_d);
		signal(SIGINT, signal_ctrl_c_d);
		while (1)
		{  
			//read_line
			line = readline("Minishell :$ ");
			if (!line)
			{
				printf("exit\n");
				exit(0);
			}
			if(line != NULL && only_spaces(line) == 0)
			{
				//history
				add_history(line);
				//synatax_error
				if(parsing(line) == 1)		
					syntax_error();
				//all_good -> exec
				else
				{
					lst = split_env(new_env);
					check_variables(line, lst);
				}
				//exit_cmd
				if (strncmp(line, "exit", 4) == 0)
				{
					printf("exit\n");
					free(line);
					break;
				}
			}
			free(line);
			signal(SIGINT, signal_ctrl_c_d);

		}
	}
	return 0;
}
