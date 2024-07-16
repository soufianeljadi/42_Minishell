/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:08:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/15 00:43:21 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env_var(char	*key, char	*value)
{
	t_env	*new_var;

	new_var = ft_malloc(sizeof(t_env));
	if (!new_var || !key || !value)
		return (free (new_var), NULL);
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	return (new_var);
}

int	set_env_var(t_env	**lst, char	*key, char	*value)
{
	t_env	*current;
	t_env	*new_var;

	new_var = new_env_var(key, value);
	current = *lst;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (free_s_env(new_var), 0);
		}
		current = current->next;
	}
	if (!new_var)
		return (-1);
	new_var->next = *lst;
	*lst = new_var;
	return (0);
}

char	*get_env_var(t_env	*lst, char	*key)
{
	while (lst && key)
	{
		if (ft_strcmp(lst->key, key) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}
