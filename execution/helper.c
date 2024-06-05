/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:07:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/05 15:22:55 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int only_spaces(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);
	}
	return (1);
}
static char *ft_value_of_shlvl(char *str)
{
	g_flags.shlvl = ft_atoi(str);
	free(str);
	++g_flags.shlvl;
	return (ft_itoa(g_flags.shlvl++));
}
s_env *split_env(char **env, s_env *lst)
{
	int i;
	int j;
	char *key;
	char *value;
	char *str;

	(1) && (i = 0);
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		key = ft_substr(env[i], 0, j);
		check_memory_allocation(key);
		if (!strcmp(key, "_"))
		{
			value = strdup("/usr/bin/env");
			check_memory_allocation(value);
		}
		if (!strcmp(key, "SHLVL"))
		{
			str = ft_substr(env[i], j + 1, ft_strlen(env[i]));
			check_memory_allocation(str);
			value = ft_value_of_shlvl(str);
			check_memory_allocation(value);
		}
		else if (!strcmp(key, "OLDPWD"))
			value = NULL;
		else
		{
			value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
			check_memory_allocation(value);
		}
		ft_lstadd_back(&lst, ft_lstnew_data(value, key));
		i++;
		if (!key)
			free(key);
		if (!value)
			free(value);
	}
	return (lst);
}

s_env *add_env_entry(s_env *head, char *key, char *value)
{
	static s_env *lst;

	lst = (s_env *)malloc(sizeof(s_env));

	if (lst == NULL)
		exit(EXIT_FAILURE);
	lst->key = ft_strdup(key);
	ft_value_of_shlvl(lst->key);
	if (value)
		lst->value = ft_strdup(value);
	else
		lst->value = NULL;
	if (lst->key == NULL)
		exit(EXIT_FAILURE);
	lst->next = head;
	return (lst);
}

s_env *split_export_i(s_env *lst)
{
	lst = add_env_entry(lst, "_", "/usr/bin/env");
	lst = add_env_entry(lst, "OLDPWD", NULL);
	lst = add_env_entry(lst, "SHLVL", "1");
	lst = add_env_entry(lst, "PWD", "/Users/sdiouane/Desktop/our_big_shell");
	return (lst);
}
