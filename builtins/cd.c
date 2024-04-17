/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/17 16:11:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_cd(char **args, s_env *lst)
{
	int i = 0;
	char *pwd;
	while(args[i])
		i++;
	if (i != 1)
	{
		if (!strcmp(args[0], "cd")  && args[1])
		{
			if (chdir(args[1]) != 0)
				perror("cd");
			pwd = getcwd(NULL, 0);
			while (lst->next != NULL)
			{
				if (!strcmp(lst->key, "PWD"))
					lst->value = ft_strdup(pwd);
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
			pwd = getcwd(NULL, 0);
			while (lst->next != NULL)
			{
				if (!strcmp(lst->key, "PWD"))
					lst->value = ft_strdup(pwd);
				lst = lst->next;
			}
		}
	}
}

