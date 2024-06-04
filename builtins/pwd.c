/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:48:45 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/04 22:20:27 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pwd_without_options(char **args, char *pwd)
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
			perror("getcwd() error");
			exit_stat(1);
		}
	}
	return (pwd);
}
