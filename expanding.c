/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/15 15:49:05 by sdiouane         ###   ########.fr       */
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
		}
		supprimerDoll(str[i]);
		if (f == 1)
			str[i] = ft_strjoin(str[i], "$");
		i++;
	}

}



// asl 
char *ft_expanding(char *commande, s_env *export_i)
{
    char	*exp_commande;
	char	*exp_cmd;
	char	*key;
	char	*value;
    int		i;

	(exp_commande = strdup(commande), i = 0, exp_cmd = NULL);
    while (exp_commande && exp_commande[i] != '\0')
	{
		if (is_single(exp_commande) == 1)
			return (exp_commande);
        if (exp_commande[i] && exp_commande[i] == '$') 
		{
            key = get_env_key(exp_commande, i);
            if (!key)
                exit(EXIT_FAILURE);
            value = get_env_value(key, export_i);
			// protect the case of $var after '='
			if (!value)
			{
				exp_cmd = ft_str_replace(exp_commande, key, strdup(""));
				(free(exp_commande), exp_commande = exp_cmd);
			}
            else if (!value || (!strcmp(value, "") || !strcmp(value, " ")))
			{
                exp_commande = ft_str_replace(exp_commande, key, strdup(""));
                (free(key), free(value));
            }
			else
			{
				key = ft_strjoin("$", key);
                exp_cmd = ft_str_replace(exp_commande, key, value);
                (free(exp_commande), exp_commande = exp_cmd);
                (free(key), free(value));
			}
        }
        	i++;
    }
	if (strstr(exp_commande, "$"))
		supprimerDoll(exp_commande);
    return (exp_commande);
}
