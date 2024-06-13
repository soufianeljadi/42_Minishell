/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:48:45 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/07 22:22:29 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pwd_without_options(char **args, char *pwd, s_env *lst)
{
	if (!strcmp(args[0], "pwd"))
	{
		if (pwd != NULL)
		{
			printf("%s\n", pwd);
			exit_stat(0);
		}
		else
		{
			printf("%s\n", get_env_value("PWD", lst));
			exit_stat(1);
		}
	}
	return (pwd);
}
