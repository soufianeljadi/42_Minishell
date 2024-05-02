/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/02 12:05:52 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_env	*execute_cd(char **args, s_env *lst)
{
	int i = 0;
	char *new_pwd;
	char *old_pwd;
	while(args[i])
		i++;
	if (i != 1)
	{
		if (!strcmp(args[0], "cd")  && args[1])
		{
			if (chdir(args[1]) != 0)
				perror("cd");
			new_pwd = getcwd(NULL, 0);
			if (!new_pwd)
			{
				while (lst && lst->next != NULL)
				{
					if (!strcmp(lst->key, "PWD"))
						lst->value = ft_strjoin(lst->value, "/..");
					lst = lst->next;
				}
				ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
				return (lst);
			}
			while (lst && lst->next != NULL)
			{
				if (!strcmp(lst->key, "PWD"))
					old_pwd = ft_strdup(lst->value);
				if (!strcmp(lst->key, "PWD"))
					lst->value = ft_strdup(new_pwd);
				else if (!strcmp(lst->key, "OLDPWD"))
					lst->value = ft_strdup(old_pwd);
				lst = lst->next;
			}
		}
	}
	else
	{
		if (!strcmp(args[0], "cd"))
		{
			if (chdir(getenv("HOME")) == -1)
				perror("HOME");
			new_pwd = getcwd(NULL, 0);
			while (lst && lst->next != NULL)
			{
				if (!strcmp(lst->key, "PWD"))
					lst->value = ft_strdup(new_pwd);
				lst = lst->next;
			}
		}
	}
	return (lst);
}
