/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:32:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/03 18:55:14 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_env	*ft_lstnew(void)
{
	s_env	*b;

	b = (s_env *)malloc(sizeof(s_env));
	if (!b)
		exit(EXIT_FAILURE);
	b ->key = NULL;
	b ->value = NULL;
	b ->next = NULL;
	return (b);
}

s_env	*ft_lstnew_data(char *value, char *key)
{
	s_env	*b;

	b = (s_env *)malloc(sizeof(s_env));
	if (!b)
		exit(EXIT_FAILURE);
	b ->key = key;
	b ->value = value;
	b ->next = NULL;
	return (b);
}

void	ft_lstadd_back(s_env **lst, s_env *new)
{
	s_env	*tmp;

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

void	free_s_env(s_env *head)
{
	s_env	*current;
	s_env	*next;

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

void	print_list(s_env *list)
{
	while (list)
	{
		if (list->value[0])
		{
			printf("%s", list->key);
			printf("=%s\n", list->value);
		}
		list = list->next;
	}
}

void	print_export(s_env *list)
{
	while (list)
	{
		if (!strcmp(list->key, "_"))
			list = list->next;
		else
		{
			if (!list->value[0])
				printf("declare -x %s\n", list->key);
			else
			{
				printf("declare -x %s=", list->key);
				printf("\"%s\"\n", list->value);
			}
			list = list->next;
		}
	}
}
