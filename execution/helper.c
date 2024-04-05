/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:07:50 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/05 23:08:28 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int only_spaces(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);	
	}
	return(1);
}

s_env *split_env(char **env)
{
	int i = 0;
	int j = 0;
	s_env	*lst = NULL;
	s_env	*tmp = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		ft_lstadd_back(&lst, ft_lstnew_data(ft_substr(env[i] ,j + 1 ,ft_strlen(env[i])) ,ft_substr(env[i] ,0 , j)));
		i++;
	}
	tmp = lst;
	while(lst)
	{
		if(!strcmp(lst->key, "_"))
		{
			free(lst->value);
			lst->value = strdup("/usr/bin/env");
		}
		lst = lst->next;
	}
	lst = tmp;
	// free_s_env(tmp);
	return (lst);
}

s_env *add_env_entry(s_env *head, char *key, char *value)
{
    s_env *lst;
	
	lst = (s_env*)malloc(sizeof(s_env));
	
    if (lst == NULL)
        exit(EXIT_FAILURE);
		
    lst->key = ft_strdup(key);
    lst->value = ft_strdup(value);
    if (lst->key == NULL || lst->value == NULL)
        exit(EXIT_FAILURE);
    lst->next = head;

    return (lst);
}

s_env *split_env_i()
{
    s_env *lst = NULL;

    lst = add_env_entry(lst, "_", "/usr/bin/env");
    lst = add_env_entry(lst, "SHLVL", "1");
    lst = add_env_entry(lst, "PWD", "/Users/sdiouane/Desktop/our_big_shell");
    return (lst);
}