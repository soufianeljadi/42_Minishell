/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/27 16:04:09 by sdiouane         ###   ########.fr       */
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



//add non valuable keys 
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

void	main_loop(char *line,s_env *s_env)
{
	(void)s_env;
	char **args;
	while (42)
	{ 
		//read_line
        line = readline("Minishell :$ ");
        if (!line)
            (printf("exit\n"),exit(0));
        if(line != NULL && only_spaces(line) == 0)
		{
			// history :
			add_history(line);
			if(parsing(line) == 1)		
				syntax_error();
			else
			{
				// split_line_into_arguments :
				args = line_to_args(line);
				// Builtins :
				builtins(args, s_env);
			}
			//exit
			if (strncmp(line, "exit", 4) == 0)
			{
				printf("exit\n");
				free(line);
				break;
			}
		}
	}
}

int main(int ac, char **av, char **env)
{
	(void)av;
	char *line = NULL;
	s_env *splited_env = NULL;
	
	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	
	splited_env = split_env(env);
	//signals
    rl_catch_signals = 0;
    signal(SIGQUIT, signal_ctrl_c_d);
    signal(SIGINT, signal_ctrl_c_d);

	main_loop(line, splited_env);
	free(line);
	return 0;
}
