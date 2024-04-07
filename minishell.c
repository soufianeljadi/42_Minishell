/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/07 21:26:30 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(char *line, s_env *env_, char **env, s_env *env_i)
{
	(void)env_;
	char **args = NULL;
	noued_cmd *cmd = NULL;
	dup2(0, 3);
	dup2(1, 4);
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
				ft_execution(cmd, args, env_, env, env_i);
				free (args);
				free_noued_cmd(cmd);
			}
		}
		dup2(3, 0);
		dup2(4, 1);
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
	s_env *env_i = NULL;

	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	splited_env = split_env(env);
	env_i = split_env_i();
	//signals
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_ctrl_c_d);
	signal(SIGINT, signal_ctrl_c_d);
	main_loop(line, splited_env, env, env_i);

	// free(line);
	free_s_env(splited_env);
	close(3);
	close(4);
	return 0;
}


