/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/10 12:14:16 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_len_env(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);	
}

void print_env_i(s_env *lst)
{
	while (lst)
	{
		if (!strcmp(lst->key, "PWD"))
			printf("%s=%s\n", lst->key, lst->value);
		else if (!strcmp(lst->key, "SHLVL"))
			printf("%s=%s\n", lst->key, lst->value);
		else if (!strcmp(lst->key, "_"))
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

int	is_builtins(char **args, ExecutionData *data, int *flag)
{
	char *pwd;
	if (!strcmp(args[0], "exit"))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (!strcmp(args[0], "echo"))
		echo_fct(args, data->export_i);
	else if (!strcmp(args[0], "pwd"))
	{
		pwd = getcwd(NULL, 0);
		pwd_without_options(args, pwd);
		free(pwd);
	}
	else if (!strcmp(args[0], "export"))
		data->export_i = export_fct(args, data->export_i, data->export_i, data->env);
	else if (!strcmp(args[0], "unset"))
		data->export_i = unset_fct(args, data->export_i);
	else if (!strcmp(args[0], "cd"))
		data->export_i = execute_cd(args, data->export_i);        
	else if (!strcmp(args[0], "env") && !args[1])
	{
		if (*(data->env) || !*(data->env))	
			print_list(data->export_i);
	}
	else
		*flag = 1;
	return (*flag);
}

int builtins(ExecutionData *data)
{
	char **args = NULL;
	int flag = 0;
	
	if (data->lst->cmd[0] != '\0' && data->lst->cmd[0])
	{
		args = ft_split(data->lst->cmd, ' ');
		flag = is_builtins(args, data, &flag);
	}
	else
		return (1);
	return(flag);
}
