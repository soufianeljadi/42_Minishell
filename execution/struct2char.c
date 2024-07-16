/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:37:50 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/15 00:59:34 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**allocate_env(int size)
{
	return (ft_malloc(sizeof(char *) * size));
}

static char	*create_env_entry(t_env *node)
{
	char	*entry;
	char	*temp;

	entry = my_strjoin(node->key, "=");
	if (node->value)
	{
		temp = entry;
		entry = my_strjoin(entry, node->value);
		free(temp);
	}
	else
	{
		temp = entry;
		entry = my_strjoin(entry, "");
		free(temp);
	}
	return (entry);
}

static void	fill_env(char **env, t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		env[i] = create_env_entry(tmp);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
}

char	**struct_to_char(t_env **lst)
{
	char	**env;
	int		size;

	env = NULL;
	if (lst[0])
	{
		size = ft_lstsize(*lst) + 1;
		env = allocate_env(size);
		if (!env)
			return (NULL);
		fill_env(env, *lst);
	}
	return (env);
}
