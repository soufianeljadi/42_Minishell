/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:07:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/14 18:52:28 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);
	}
	return (1);
}

static char	*get_key(char *env_var, int j)
{
	char	*key;

	while (env_var[j] != '=')
		j++;
	key = ft_substr(env_var, 0, j);
	return (key);
}

static void	free_var(char *var)
{
	if (!var)
		free(var);
}

t_env	*split_env(char **env, t_env *lst)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	(1) && (i = 0);
	while (env[i])
	{
		j = 0;
		key = get_key(env[i], j);
		if (!key)
			return (NULL);
		while (env[i][j] != '=')
			j++;
		value = get_value(env, key, i, j);
		ft_lstadd_back(&lst, ft_lstnew_data(value, key));
		i++;
		(free_var(key), free_var(value));
	}
	return (lst);
}
