/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/09 16:16:29 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *init_data(char **args, noued_cmd *cmd, s_env *export_i)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->lst = cmd;
	data->args = args;
	data->export_i = export_i;
	return (data);
}

void loop_fct(t_data *data, char *line)
{
	char	*pwd;

	pwd = NULL;
	while (42)
	{
		
		(pwd = print_directory(pwd), line = readline(pwd));
		if (!line)
			(printf("exit\n"), exit_stat(0), exit(0));
		if (line != NULL && only_spaces(line) == 0)
		{
			add_history(line);
			if (parsing(line, data) == 1)
				(1) && (syntax_error(), exit_stat(258));
			else
			{
				data->args = line_to_args(line);
				check_here_doc(data);
				data->lst = split_args_by_pipe(data->args);
				data->lst = ft_expanding(&data, data->export_i);
				(dup2(0, 3), dup2(1, 4), ft_execution(data));
				(dup2(3, 0), dup2(4, 1), close(3), close(4));
				(free(data->args) /*, free_noued_cmd(data->lst)*/);
			}
		}
	}
}

void main_loop(char *line, s_env *export_i)
{
	char		**args;
	noued_cmd	*cmd;
	t_data		*data;

	data = NULL;
	args = NULL;
	cmd = NULL;
	if (export_i == NULL)
	{
		ft_putstr_fd("envirement empty\n", 2);
		return ;
	}
	data = init_data(args, cmd, export_i);
	loop_fct(data, line);
	free(line);
	clear_history();
	free_noued_cmd(cmd);
	ft_free_tab(args);
}

void f(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	char	*line;
	s_env	*export_i;
	s_env 	*lst;

	(void)av;
	export_i = NULL;
	lst = NULL;
	line = NULL;
	if (ac != 1)
		(printf("Args not allowed !\n"), exit(EXIT_FAILURE));
	if (!isatty(STDIN_FILENO))
		(printf("minishell: is not a tty\n"), exit(EXIT_FAILURE));
	rl_catch_signals = 0;
	if (env[0] == NULL)
		export_i = split_export_i(export_i);
	else
		export_i = split_env(env);
	signals_init();
	main_loop(line, export_i);
	free_s_env(export_i);
	return (0);
}
