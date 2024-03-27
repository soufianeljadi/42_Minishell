/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:48:45 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/27 15:38:48 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd_without_options(char **args)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);


	if (!strcmp(args[0], "pwd"))
	{
		if (pwd != NULL)
		{
			printf("%s\n", pwd);
			free(pwd);
		}
		else
			perror("getcwd() error");
	}
}