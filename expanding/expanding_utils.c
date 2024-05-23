/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:08:19 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/23 11:57:03 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_value(char *key, s_env *export_i)
{
	s_env *tmp;
	char *value = NULL;

	tmp = export_i;
	while (tmp)
	{
		if (!strcmp(tmp->key, key))
		{
			if (tmp->value != NULL)
			{
				value = strdup(tmp->value);
				return (value);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char *ft_str_replace(char *s, char *key, char *value)
{
    int s_len;
    int key_len;
    int value_len;
    char *occurrence;
	char *new_str;
	
	(s_len = ft_strlen(s), key_len = ft_strlen(key),
		value_len = ft_strlen(value), occurrence = strstr(s, key));
    if (!occurrence)
        return (ft_strdup(s));
    new_str = (char *)malloc(s_len - key_len + value_len + 1);
    if (!new_str)
        return (NULL);
    strncpy(new_str, s, occurrence - s);
    new_str[occurrence - s] = '\0';
    strcat(new_str, value);
    strcat(new_str, occurrence + key_len);
    return (new_str);
}

char *get_env_key(char *str, int i)
{
    char *key = NULL;
    while (str[i] && str[i] != '$')
        i++;
    if (str[i] == '$')
    {
        i++;
        int key_start = i;
        while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
            i++;
        key = (char *)malloc((i - key_start + 1) * sizeof(char));
        if (!key)
            exit(EXIT_FAILURE);
        strncpy(key, &str[key_start], i - key_start);
        key[i - key_start] = '\0';
    }
    return (key);
}

void supprimerDoll(char *chaine)
{
	int i = 0;
	int j = 0;

	while (chaine[i])
	{
		if (chaine[i] != '$')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}

int is_closed(char *str, int n)
{
    int i = 0;

    while (str[i] && i < n)
	{
        if (str[i] == '"')
		{
            i++;
            while (str[i] && str[i] != '"')
                i++;
            if (str[i] == '\0' || i >= n)
                return 0;
        }
        i++;
    }
    return 1;
}
