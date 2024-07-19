/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_three.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:09:48 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/19 22:57:59 by sel-jadi         ###   ########.fr       */
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

char	*prc_variable(char *exp_commande, t_p *p, t_env *export_i)
{
	char	*key;
	char	*value;
	char	*str;
	char	*full_key;

	(1) && (str = NULL, full_key = NULL);
	key = get_env_key(exp_commande, p->i);
	value = format_value_if_needed(key, export_i);
	if (!value || !ft_strcmp(value, "") || !ft_strcmp(value, " "))
	{
		if (ft_strcmp(key, ""))
		{
			str = ft_str_replace(exp_commande, key, ft_strdup(""));
			return (protect_value(value), free(exp_commande), str);
		}
		else
			return (free(key), exp_commande);
	}
	else
	{
		str = variable_with_value(full_key, key, value, exp_commande);
		(check_memory_allocation(str), free(exp_commande));
	}
	return (str);
}
