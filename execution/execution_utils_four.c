/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_four.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:28:04 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/14 00:21:05 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_data *data, char *chemin)
{
	execute_with_redirection(data);
	builtins(data);
	free(chemin);
	exit(1);
}

void	handle_execve_error(char **cmd, char *chemin)
{
	ft_execut_error(cmd[0]);
	ft_free_tab(cmd);
	free(chemin);
	exit(EXIT_FAILURE);
}

static void	exec_command(char **cmd, char **env, char *chemin)
{
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		if (execve(cmd[0], cmd, env) == -1)
			handle_execve_error(cmd, chemin);
	if (execve(chemin, cmd, env) == -1)
		handle_execve_error(cmd, chemin);
}

char	*ft_check(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == '\0')
		{
			tmp = ft_substr(str, 0, ft_strlen(str) - 1);
			free(str);
			str = ft_strdup(tmp);
			free(tmp);
			break ;
		}
		i++;
	}
	return (str);
}

void	execute(char *s, char **env, t_data *data)
{
	char	*chemin;
	char	**cmd;

	chemin = NULL;
	cmd = NULL;
	if (*env)
	{
		cmd = check_quotes_before_execution(s);
		if (cmd[0] == NULL)
			exit(exit_stat(1));
		cmd[0] = ft_check(cmd[0]);
		chemin = get_path(cmd[0], env);
		if (chemin == NULL)
			handle_path_error(cmd);
		if (check_bultin(cmd[0]) == 0)
			exec_command(cmd, env, chemin);
		else
			execute_builtin(data, chemin);
	}
}
