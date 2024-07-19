//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/16 22:15:07 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_rm_quotes(char *str)
{
	int len = strlen(str);
	int i, j;
	char quote_type = '\0'; // Type de quote actuelle

	for (i = 0, j = 0; i < len; i++)
	{
		if (quote_type == '\0' && (str[i] == '"' || str[i] == '\''))
		{
			// Si on trouve une quote ouvrante, on marque son type et on la saute
			quote_type = str[i];
		}
		else if (str[i] == quote_type)
		{
			// Si on trouve une quote fermante correspondante, on réinitialise le type de quote et on la saute
			quote_type = '\0';
		}
		else
		{
			// Sinon, on copie le caractère
			str[j++] = str[i];
		}
	}
	str[j] = '\0'; // Terminer la chaîne
}


static void init_data(t_data *data, char *line)
{
	data->args = line_to_args(line);
	check_here_doc(data);
	data->lst = split_args_by_pipe(data->args);
	data->lst = ft_expanding(&data, data->export_i);
}

void loop_fct(t_data *data, char *line)
{
	char *pwd;

	pwd = NULL;
	while (42)
	{
		g_signal = 0;
		pwd = print_directory(pwd);
		line = readline(pwd);
		if (!line)
			(printf("exit\n"), exit(exit_stat(-1)));
		if (line != NULL && *line && only_spaces(line) == 0)
		{
			add_history(line);
			if (parsing(line, data) == 1)
				(1) && (syntax_error(), exit_stat(258));
			else if (parsing(line, data) == 0)
			{
				init_data(data, line);
				(dup2(0, 3), dup2(1, 4), ft_execution(data));
				(dup2(3, 0), dup2(4, 1), close(3), close(4));
				(ft_free_tab(data->args), free_noued_cmd(data->lst));
			}
		}
		free(line);
	}
}

void main_loop(char *line, t_env *export_i)
{
	t_data *data;

	if (export_i == NULL)
	{
		ft_putstr_fd("envirement empty\n", 2);
		return;
	}
	data = (t_data *)ft_malloc(sizeof(t_data));
	if (!data)
		return;
	data->lst = NULL;
	data->args = NULL;
	data->env = NULL;
	data->fd_in = 0;
	data->fd_out = 1;
	data->export_i = export_i;
	loop_fct(data, line);
	clear_history();
}

int main(int ac, char **av, char **env)
{
	char *line;
	t_env *export_i;
	t_env *lst;

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
		export_i = split_env(env, lst);
	signals_init();
	main_loop(line, export_i);
	free_s_env(lst);
	free(line);
	return (0);
}
// '            'ls 