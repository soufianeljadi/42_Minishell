/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:32:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/03 02:09:27 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


s_env	*ft_lstnew()
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

void free_s_env(s_env *head)
{
    s_env *current = head;
    s_env *next;

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
	// if (list->key && list->value)
	// {
		printf("%s=", list->key);
		printf("\"%s\"\n", list->value);
	// }
  	list = list->next;
  }
}
void	print_export(s_env *list)
{
  while (list)
  {
	if (!strcmp(list->key,"_"))
		list = list->next;
	else
	{
		if (!strcmp(&list->value[0], ""))
			printf("declare -x %s=", list->key);
		else
			printf("declare -x %s=", list->key);
		printf("\"%s\"\n", list->value);
		list = list->next;
	}
  }
}
