/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 21:56:22 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	chech_for_no_new_line(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_fct(char **args)
{
	int	i;
	int	n;

	(1) && (i = 1, n = 0);
	while (args[i] && (ft_strcmp(args[i], "-n") == 0
			|| !chech_for_no_new_line(args[i])))
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		ft_rm_quotes(args[i]);
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	exit_stat(0);
}
