/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/30 15:23:15 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cmp(void *data1, void *data2)
{
	char *int_data1 = (char *)data1;
	char *int_data2 = (char *)data2;
	if (*int_data1 == *int_data2)
		return 0;
	else
		return 1;
}

void	remove_key(s_env **begin_list, void *data_ref, int (*cmp)())
{
	s_env	*remove;
	s_env	*current;

	current = *begin_list;
	while (current && current->next)
	{
		if ((*cmp)(current->next->key, data_ref) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove);
		}
		current = current->next;
	}
	current = *begin_list;
	if (current && (*cmp)(current->key, data_ref) == 0)
	{
		*begin_list = current->next;
		free(current);
	}
}

s_env *unset_fct(char **args, s_env *env)
{
	int i = 1;
	int j;
	char *key;
	if (!strcmp(args[0] ,"unset"))
	{
		while (args[i])
		{
			j = 0;
			while (args[i][j])
			{
				while (args[i] && args[i][j] != ' ' && args[i][j] != '\t' && args[i][j] != '\0')
					j++;
				key = ft_substr2(args[i], 0, j);
				if (verif_export(key) == 0)
					remove_key(&env, key, cmp);
				else
					fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n", args[i]);
				free(key);
				while (args[i][j] == ' ' || args[i][j] == '\t')
					j++;
			}
			i++;
		}
	}
	return env;
}
