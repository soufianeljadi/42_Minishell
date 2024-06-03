/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/03 14:05:33 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// s_env	*execute_cd(char **args, s_env *lst)
// {
// 	int i = 0;
// 	char *new_pwd;
// 	char *old_pwd;
// 	while(args[i])
// 		i++;

// 	if (i != 1)
// 	{
// 		if (!strcmp(args[0], "cd")  && args[1])
// 		{
// 			if (chdir(getenv("HOME")) == -1)
// 			{
// 				printf("hahahahahhahahahahhah\n");
// 				return (lst);
// 			}
// 			if (chdir(args[1]) != 0)
// 				perror("cd");
// 			new_pwd = getcwd(NULL, 0);
// 			if (!new_pwd)
// 			{
// 				while (lst && lst->next != NULL)
// 				{
// 					if (!strcmp(lst->key, "PWD"))
// 						lst->value = ft_strjoin(lst->value, "/..");
// 					lst = lst->next;
// 				}
// 				ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
// 				return (lst);
// 			}
// 			while (lst && lst->next != NULL)
// 			{
// 				if (!strcmp(lst->key, "PWD"))
// 					old_pwd = ft_strdup(lst->value);
// 				if (!strcmp(lst->key, "PWD"))
// 					lst->value = ft_strdup(new_pwd);
// 				else if (!strcmp(lst->key, "OLDPWD"))
// 					lst->value = ft_strdup(old_pwd);
// 				lst = lst->next;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (!strcmp(args[0], "cd"))
// 		{
// 			if (chdir(getenv("HOME")) == -1)
// 			{
// 				printf("hahahahahhahahahahhah\n");
// 				return (lst);
// 			}
// 			new_pwd = getcwd(NULL, 0);
// 			while (lst && lst->next != NULL)
// 			{
// 				if (!strcmp(lst->key, "PWD"))
// 					lst->value = ft_strdup(new_pwd);
// 				lst = lst->next;
// 			}
// 		}
// 	}
// 	return (lst);
// }

// < Makefile cat | " "
s_env *update_env_var(s_env *lst, char *key, char *new_value)
{
	s_env *head = lst;
	while (lst != NULL)
	{
		if (!strcmp(lst->key, key))
		{
			free(lst->value);
			lst->value = ft_strdup(new_value);
		}
		lst = lst->next;
	}
	return head;
}

s_env *execute_cd(char **args, s_env *lst)
{
	int i;
	char *new_pwd;
	char *old_pwd;
	char *home;

	(1) && (i = 0, new_pwd = NULL, old_pwd = NULL);
	while (args[i])
		i++;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("getcwd");
		return (lst);
	}
	if (i == 1 || (i == 2 && strcmp(args[1], "~") == 0))
	{
		home = get_env_value("HOME", lst);
		if (!home)
		{
			exit_stat(1);
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			free(old_pwd);
			return lst;
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			free(old_pwd);
			return lst;
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			exit_stat(256);
			perror("cd");
			free(old_pwd);
			return lst;
		}
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		new_pwd = ft_strjoin(old_pwd, "/..");
	}
	lst = update_env_var(lst, "OLDPWD", old_pwd);
	lst = update_env_var(lst, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return lst;
}