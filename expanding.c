/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/12 19:30:58 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(char *key, s_env *export_i)
{
	s_env *tmp;
	char *value = NULL;
	// int i = 0;

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
    size_t s_len = strlen(s);
    size_t key_len = strlen(key);
    size_t value_len = strlen(value);

    char *occurrence = strstr(s, key);

    if (!occurrence)
        return strdup(s);
    size_t new_size = s_len - key_len + value_len + 1;

    char *new_str = (char *)malloc(new_size);
    if (!new_str)
        return NULL;
    strncpy(new_str, s, occurrence - s);
    new_str[occurrence - s] = '\0';
    strcat(new_str, value);
    strcat(new_str, occurrence + key_len);

    return new_str;
}



// char *get_env_key(char *str, int i)
// {
// 	char *key = NULL;
// 	while (str[i] && str[i] != '$')
// 		i++;
// 	if (str[i] == '$')
// 	{
// 		i++;
// 		int key_start = i;
// 		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
// 			i++;
// 		key = (char *)malloc((i - key_start + 1) * sizeof(char));
// 		if (!key)
// 			exit(EXIT_FAILURE);
// 		strncpy(key, &str[key_start], i - key_start);
// 		key[i - key_start] = '\0';
// 	}
// 	return (key);
// }

char *get_env_key(char *str, int i)
{
    char *key = NULL;
    while (str[i] && str[i] != '$')
        i++;
    if (str[i] == '$')
    {
        i++;
        int key_start = i;
        while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
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

void rmv(char **str)
{
	int i = 0;
	int j;
	int f = 0;
	while(str[i])
	{
		j = 0;
		if (str[i][j] == '\'' || str[i][j] == '"')
			j++;
		if (str[i][strlen(str[i]) - 2] == '$')
		{
			str[i] = ft_substr2(str[i], 1, strlen(str[i]) - 3);
			f = 1;
			// printf("str = %s\n", str[i]);
		}
		supprimerDoll(str[i]);
		if (f == 1)
			str[i] = ft_strjoin(str[i], "$");
		i++;
	}

}

char *ft_expanding(char *commande, s_env *export_i)
{
    int i;
    char *expanded_commande = strdup(commande);
	
    i = 0;
    while (expanded_commande && expanded_commande[i] != '\0')
	{
        if (expanded_commande[i] == '$') 
		{
            char *key = get_env_key(expanded_commande, i);
            if (!key)
                exit(EXIT_FAILURE);
            char *value = get_env_value(key, export_i);
			if (!value)
			{
				key = ft_strjoin("$", key); 
				char *expanded_cmd = ft_str_replace(expanded_commande, key, strdup(""));
				free(expanded_commande);
				expanded_commande = expanded_cmd;
				break ;
			}
            else if (!value || (!strcmp(value, "") || !strcmp(value, " ")))
			{
				key = ft_strjoin("$", key);
                expanded_commande = ft_str_replace(expanded_commande, key, strdup(""));
				break ;
                free(key);
                free(value);
            }
			else
			{
				key = ft_strjoin("$", key);
                char *expanded_cmd = ft_str_replace(expanded_commande, key, value);
                free(expanded_commande);
                expanded_commande = expanded_cmd;
                free(key);
                free(value);
			}
        }
        	i++;
    }
	if (strstr(expanded_commande, "$"))
		supprimerDoll(expanded_commande);
    return (expanded_commande);
}
