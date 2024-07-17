/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/17 16:40:22 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_builtin_pwd(char **args, t_env *export_i)
{
	char	*pwd;

	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = get_env_value("PWD", export_i);
	pwd_without_options(args, pwd);
	free(pwd);
}

char	*get_pwd_value(char *key, t_env *export_i)
{
	t_env	*tmp;
	char	*value;

	value = NULL;
	tmp = export_i;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value != NULL)
			{
				value = ft_strdup(tmp->value);
				return (value);
			}
		}
		tmp = tmp->next;
	}
	free(value);
	return (NULL);
}

int	is_builtins(char **args, t_env **export_i, char **env, int *flag)
{
	// if (args[0] && ft_strcmp(args[0], ""))
	// 	supprimerguillemets(args[0]);
	if (args[0] && !ft_strcmp(args[0], "exit"))
		exit_fct(args);
	else if (args[0] && !ft_strcmp(args[0], "echo"))
		echo_fct(args);
	else if (args[0] && !ft_strcmp(args[0], "pwd"))
		handle_builtin_pwd(args, *export_i);
	else if (args[0] && !ft_strcmp(args[0], "export"))
		*export_i = export_fct(args, *export_i, env);
	else if (args[0] && !ft_strcmp(args[0], "unset"))
		*export_i = unset_fct(args, *export_i);
	else if (args[0] && !ft_strcmp(args[0], "cd"))
	{
		*export_i = execute_cd(args, *export_i, getcwd(NULL, 0));
	}
	else if (args[0] && !args[1] && !ft_strcmp(args[0], "env"))
		print_list(*export_i);
	else
		*flag = 1;
	return (*flag);
}

int	builtins(t_data *data)
{
	char	**args;
	int		flag;

	flag = 0;
	args = NULL;
	if (data->lst->cmd[0] != '\0')
	{
		args = split_with_quotes(data->lst->cmd);
		flag = is_builtins(args, &data->export_i, data->env, &flag);
		ft_free_tab(args);
	}
	else
		return (1);
	return (flag);
}
