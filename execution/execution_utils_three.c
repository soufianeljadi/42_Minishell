/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:12:09 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/17 14:48:20 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_process(t_data *data)
{
	signal(SIGQUIT, SIG_DFL);
	if (data->lst->redirection != NULL)
		execute_with_redirection(data);
	if (data->lst->cmd != NULL)
		execute(data->lst->cmd, data->env, data);
}

void	add_last_cmd(t_env **lst, char **args)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *lst;
	while (args[i])
		i++;
	if (i == 0)
		return ;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(args[i - 1]);
			if (!tmp->value)
				exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
}

void	ft_execut_error(char *cmd)
{
	int	ref;
	DIR	*ptr;

	ref = errno;
	ft_putstr_fd("minishell: ", 2);
	if (!ft_strcmp(cmd, "\0"))
		(ft_putendl_fd(": command not found", 2), exit(127));
	ft_putstr_fd(cmd, 2);
	if (ref == 2)
	{
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else if (ref == 13)
	{
		ptr = opendir(cmd);
		if (ptr && !closedir(ptr))
			ft_putendl_fd(": is directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	exit(0);
}

void	remove_outermost_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 2)
		return ;
	if (str[0] == '"' || str[0] == '\'')
	{
		memmove(str, str + 1, len - 1);
		str[len - 1] = '\0';
		len--;
	}
	if (str[len - 1] == '"' || str[len - 1] == '\'')
		str[len - 1] = '\0';
}

void	check_error(char **cmd, char **env, char *chemin)
{
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		if (execve(cmd[0], cmd, env) == -1)
			(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(0));
	if (execve(chemin, cmd, env) == -1 && ft_strcmp(cmd[0], "\0"))
	{
		if (ft_strcmp(cmd[0], "\0"))
			(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(0));
	}
}
