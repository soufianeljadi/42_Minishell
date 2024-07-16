/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:56:01 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/15 01:34:24 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dbl_q(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		if (chaine[i] != '"')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}

void	sng_q(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		if (chaine[i] != '\'')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}
