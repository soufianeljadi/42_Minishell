/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/20 07:02:01 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_cd(char **args, s_env *lst)
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
			while (lst->next != NULL)
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
			while (lst->next != NULL)
			{
				if (!strcmp(lst->key, "PWD"))
					lst->value = ft_strdup(new_pwd);
				lst = lst->next;
			}
		}
	}
}
