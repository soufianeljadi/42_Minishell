/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/25 17:00:25 by sdiouane         ###   ########.fr       */
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

s_env *unset_fct(char *line, s_env *env)
{
	int i = 0;
	int start;
	char *key;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (strncmp(&line[i], "unset", 5) == 0)
	{
		i = i + 5;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		while (line[i] != '\0')
		{
			start = i;
			while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
				i++;
			key = strndup(&line[start], i - start);
			remove_key(&env, key, cmp);
			free(key);
			while (line[i] == ' ' || line[i] == '\t')
				i++;
		}
	}
	return env;
}
