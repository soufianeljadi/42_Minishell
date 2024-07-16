/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:36:56 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/11 23:23:58 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(void *lst)
{
	int		c;
	t_env	*p;

	c = 0;
	p = lst;
	while (p)
	{
		p = p->next;
		c++;
	}
	return (c);
}

static char	*return_fct(void *ptr)
{
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*get_value(char **env, char *key, int i, int j)
{
	char	*value;
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(key, "_"))
	{
		tmp = ft_strdup("/usr/bin/env");
		value = tmp;
	}
	else if (!ft_strcmp(key, "OLDPWD"))
		value = NULL;
	else
	{
		value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
		return_fct(value);
	}
	return (value);
}

t_env	*add_env_entry(t_env *head, char *key, char *value)
{
	static t_env	*lst;

	lst = (t_env *)ft_malloc(sizeof(t_env));
	if (lst == NULL)
		exit(EXIT_FAILURE);
	lst->key = ft_strdup(key);
	if (value)
		lst->value = ft_strdup(value);
	else
		lst->value = NULL;
	if (lst->key == NULL)
		exit(EXIT_FAILURE);
	lst->next = head;
	return (lst);
}

t_env	*split_export_i(t_env *lst)
{
	lst = add_env_entry(lst, "_", "/usr/bin/env");
	lst = add_env_entry(lst, "OLDPWD", NULL);
	lst = add_env_entry(lst, "SHLVL", "1");
	lst = add_env_entry(lst, "PWD", "/Users/sdiouane/Desktop/our_big_shell");
	return (lst);
}
