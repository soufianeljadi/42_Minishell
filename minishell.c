/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/01 21:20:28 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void supprimerGuillemets__(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '\'')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

void before_expanding(char **args)
{
	// char *tmp;
	int i = 0;
	int j = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '"')
		{
			while (args[i][j] != '"')
				i++;
			args[i] = ft_substr2(args[i], 1, strlen(args[i]) - 1);
			supprimerGuillemets(args[i]);
			printf("tmp = %s\n", args[i]);
		}
		i++;
	}
}

void supprimerGuillemetsdoll(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '$')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

int is_single(char *str)
{
	int s;
	int d;
	int i;

	i = 0;
	s = d = 0;
	while (str[i])
	{
		if (str[i] == '\'' && d == 0)
			s = s + 1;
		else if (str[i] == '"' && s == 0)
			d = d + 1;
		if (d == 2)
			d = 0;
		if (s == 2)
			s = 0;
		if (str[i] == '$')
			break;
		i++;
	}
	if (s == 1)
		return (1);
	else
		return (0);

	return (0);
}

void	main_loop(char *line, char **env, s_env *export_i, char **null_env)
{
	char **args = NULL;
	noued_cmd *cmd = NULL;
	dup2(0, 3);
	dup2(1, 4);
	while (42)
	{
		//read_line
		line = readline("Minishell --> ");
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
				// before_expanding(args);
				ft_expanding(args, export_i);
				// while (args[i])
				// 	supprimerGuillemetsdoll(args[i++]);
				cmd = split_args_by_pipe(args);
				print_command_list(cmd);
				ft_execution(cmd, args, env, export_i, null_env);
				free (args);
				free_noued_cmd(cmd);
			}
		}
		dup2(3, 0);
		dup2(4, 1);
	}
	free(line);
	clear_history();
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
	char *null_env = NULL;
	s_env *export_i = NULL;

	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	if (!env[0])
	{
		export_i = split_export_i(export_i);
		null_env = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	}
	else
		export_i = split_env(env);
	//signals
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_ctrl_c_d);
	signal(SIGINT, signal_ctrl_c_d);
	main_loop(line,env, export_i, &null_env);
	// free(line);
	free_s_env(export_i);
	close(3);
	close(4);
	return 0;
}
