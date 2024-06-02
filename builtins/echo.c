/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/02 18:55:38 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_fct(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (args[i] && strcmp(args[i], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		supprimerGuillemets(args[i]);
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
}
