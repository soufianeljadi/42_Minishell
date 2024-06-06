/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:07:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/06 19:32:08 by sdiouane         ###   ########.fr       */
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
	if (!str)
		return (NULL);
	g_flags.shlvl = ft_atoi(str);
	free(str);
	++g_flags.shlvl;
	return (ft_itoa(g_flags.shlvl++));
}


static char	*get_key(char *env_var, int j)
{
	char	*key;

	while (env_var[j] != '=')
		j++;
	key = ft_substr(env_var, 0, j);
	return (key);
}


char *return_fct(void *ptr)
{
	if (!ptr)
		return (NULL);
	return (ptr);
}
void free_var(char *var)
{
	if (!var)
		free(var);
}

char *get_value(char **env, char *key, int i, int j)
{
	char *value;

	if (!strcmp(key, "_"))
		value = ft_strdup("/usr/bin/env");
	if (!strcmp(key, "SHLVL"))
		value = ft_value_of_shlvl(ft_substr(env[i], j + 1,
			ft_strlen(env[i])));
	else if (!strcmp(key, "OLDPWD"))
		value = NULL;
	else
		(value = ft_substr(env[i], j + 1, ft_strlen(env[i])),
			return_fct(value));	
	return (value);
}

s_env *split_env(char **env, s_env *lst)
{
	int i;
	int j;
	char *key;
	char *value;

	(1) && (i = 0);
	while (env[i])
	{
		j = 0;
		key = get_key(env[i], j);
		if (!key)
			return (NULL);
		value = get_value(env, key, i, j);
		ft_lstadd_back(&lst, ft_lstnew_data(value, key));
		i++;
		(free_var(key), free_var(value));
	}
	return (lst);
}

s_env *add_env_entry(s_env *head, char *key, char *value)
{
   static  s_env *lst;
	
	lst = (s_env*)malloc(sizeof(s_env));
	
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

s_env *split_export_i(s_env *lst)
{
    lst = add_env_entry(lst, "_", "/usr/bin/env");
    lst = add_env_entry(lst, "OLDPWD", NULL);
    lst = add_env_entry(lst, "SHLVL", "1");
    lst = add_env_entry(lst, "PWD", "/Users/sdiouane/Desktop/our_big_shell");
    return (lst);
}
