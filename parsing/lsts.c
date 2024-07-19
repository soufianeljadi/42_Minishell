/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:32:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 22:29:34 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew(void)
{
	t_env	*b;

	b = (t_env *)ft_malloc(sizeof(t_env));
	if (!b)
		exit(EXIT_FAILURE);
	b ->key = NULL;
	b ->value = NULL;
	b ->next = NULL;
	return (b);
}

t_env	*ft_lstnew_data(char *value, char *key)
{
	t_env	*b;

	b = (t_env *)ft_malloc(sizeof(t_env));
	if (!b)
		exit(EXIT_FAILURE);
	if (key)
		b->key = key;
	else
		b->key = NULL;
	if (value)
		b->value = value;
	else
		b->value = NULL;
	b->next = NULL;
	return (b);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_s_env(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	print_list(t_env *list)
{
	while (list)
	{
		if (list->value != NULL
			&& (list->value[0] || !ft_strcmp(list->value, "")))
		{
			printf("%s", list->key);
			ft_rm_quotes(list->value);
			printf("=%s\n", list->value);
		}
		list = list->next;
	}
}
