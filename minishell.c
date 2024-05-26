/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/26 22:57:53 by sdiouane         ###   ########.fr       */
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
    int s = 0, d = 0;
	
    for (int i = 0; str[i]; i++)
	{
        if (str[i] == '\'' && !d)
			s = !s;
        if (str[i] == '"' && !s)
			d = !d;
        if ((str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == '\t')) ||
            (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\'')))
            return 1;
        if (s || d)
			return 1;
    }
    return 0;
}

ExecutionData *init_data(char **args, noued_cmd *cmd, s_env *export_i)
{
	ExecutionData *data;
	data = (ExecutionData *)malloc(sizeof(ExecutionData));
	if (!data)
		return (NULL);
	data->lst = cmd;
	data->args = args;
	data->export_i = export_i;
	return (data);
}

void loop_fct(ExecutionData *data, char *line)
{
	char	*pwd;
	
	pwd = NULL;
	while (42)
	{
		// (pwd = print_directory(pwd), line = readline(pwd));
		line = readline(ANSI_COLOR_GREEN "minishell >" ANSI_RESET_ALL);
		if (!line)
			(printf("exit\n"),exit(0));
		if(line != NULL && only_spaces(line) == 0)
		{
			add_history(line);
			if(parsing(line) == 1)	
				syntax_error();
			else
			{
				data->args = line_to_args(line);
				data->lst = split_args_by_pipe(data->args);
				data->lst = ft_expanding(&data, data->export_i);
				(dup2(0, 3),dup2(1, 4), ft_execution(data));
				(dup2(3, 0), dup2(4, 1), close(3), close(4));
				// print_command_list(data->lst);
				(free (data->args)/*, free_noued_cmd(data->lst)*/);
			}
		}
	}	
}

void	main_loop(char *line, s_env *export_i)
{
	char			**args;
	noued_cmd		*cmd;
	ExecutionData	*data;
	
	data = NULL;
	args = NULL;
	cmd = NULL;
	data = init_data(args, cmd, export_i);
	loop_fct(data, line);
	free(line);
	clear_history();
	free_noued_cmd(cmd);
	ft_free_tab(args);
}

void	f(void)
{     
	system("leaks minishell");
}
// export x="ls > gg">
int main(int ac, char **av, char **env)
{
	(void)av;
	// atexit(f);
	char *line;
	s_env *export_i;

	(export_i = NULL, line = NULL);
	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	// if (!isatty(STDIN_FILENO))
	// {
	// 	printf("minishell: is not a tty\n");
	// 	exit(EXIT_FAILURE);
	// }
	if (env[0] == NULL)
		export_i = split_export_i(export_i);
	else
		export_i = split_env(env);        
	rl_catch_signals = 0;
	signals_init();
	main_loop(line, export_i);
	// free(line);
	free_s_env(export_i);
	return 0;
}
