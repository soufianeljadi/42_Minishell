/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/01 00:48:48 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_cd(char **args)
{
	int i = 0;
	while(args[i])
		i++;
	if (i != 1)
	{
		if (!strcmp(args[0], "cd")  && args[1])
		{
			if (chdir(args[1]) != 0)
				perror("cd");
		}
	}
	else
	{
		if (!strcmp(args[0], "cd"))
		{
			if (chdir(getenv("HOME")) == -1)
				perror("HOME");
		}
	}
}

