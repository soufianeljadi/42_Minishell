/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:09:48 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/15 01:25:22 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*variable_with_value(char *full_key, char *key, char *value,
	char *exp_commande)
{
	char	*exp_cmd;

	full_key = ft_strjoin("$", key);
	check_memory_allocation(full_key);
	exp_cmd = ft_str_replace(exp_commande, full_key, value);
	(check_memory_allocation(exp_cmd));
	exp_commande = ft_strdup(exp_cmd);
	check_memory_allocation(exp_commande);
	free(exp_cmd);
	free(key);
	return (exp_commande);
}

char	*ft_strcat(char *dest, const char *src)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (*d != '\0')
		d++;
	while (*s != '\0')
	{
		*d = *s;
		d++;
		s++;
	}
	*d = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
