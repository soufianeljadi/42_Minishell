/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/02 22:30:41 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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

s_env *split_env(char **env)
{
	int i = 0;
	int j = 0;
	s_env	*lst = NULL;
	s_env	*tmp = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		ft_lstadd_back(&lst, ft_lstnew_data(ft_substr(env[i] ,j + 1 ,ft_strlen(env[i])) ,ft_substr(env[i] ,0 , j)));
		i++;
	}
	tmp = lst;
	while(lst)
	{
		if(!strcmp(lst->key, "_"))
		{
			free(lst->value);
			lst->value = strdup("/usr/bin/env");
		}
		lst = lst->next;
	}
	lst = tmp;
	// free_s_env(tmp);
	return (lst);
}

void	main_loop(char *line, s_env *s_env, char **env)
{
	(void)s_env;
	char **args = NULL;
	noued_cmd *cmd = NULL;
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
				// split_args_by_pipe :
				cmd = split_args_by_pipe(args);
				// print_command_list(cmd);
				ft_execution(cmd, args, s_env, env);
				free (args);
				free_noued_cmd(cmd);
			}
			//exit
			if (strncmp(line, "exit", 4) == 0)
			{
				printf("exit\n");
				free(line);
				free(args);
				free_noued_cmd(cmd);
				break;
			}
		}
	}
	free(line);
	// clear_history();
	free_noued_cmd(cmd);
	ft_free_tab(args);
}

void	f(void)
{
	// system("lsof minishell > file");
	system("leaks minishell");
}


int main(int ac, char **av, char **env)
{
	(void)av;
	// atexit(f);
	char *line = NULL;
	s_env *splited_env = NULL;

	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	splited_env = split_env(env);
	//signals
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_ctrl_c_d);
	signal(SIGINT, signal_ctrl_c_d);
	main_loop(line, splited_env, env);
	// free(line);
	free_s_env(splited_env);
	return 0;
}


