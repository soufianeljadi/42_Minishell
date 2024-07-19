/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:54:34 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 20:44:09 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_qotes(char *chaine)
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

void	del_dbl_quotes(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine && chaine[i])
	{
		if (chaine[i] != '"')
			chaine[j++] = chaine[i];
		i++;
	}
	if (chaine)
		chaine[j] = '\0';
}

void	supprimerguillemets(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		if (chaine[i] != '$')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}

void	del_sngl_quotes(char *chaine)
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
