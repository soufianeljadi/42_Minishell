/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/27 00:16:28 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_fct(char **args)
{
	int i = 2;
	if(!strcmp(args[0],"echo"))
	{
		if(!strcmp(args[1],"-n"))
		{
			while(args[i])
				printf("%s",args[i++]);
		}
		else
		{
			i = 1;
			while(args[i])
				printf("%s",args[i++]);
			printf("\n");
		}
	}
}
