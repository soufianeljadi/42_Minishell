/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/09 20:41:49 by sdiouane         ###   ########.fr       */
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

char *ft_str_replace(char *source, char *pattern, char *replacement)
{
    size_t pattern_len = strlen(pattern);
    size_t replacement_len = strlen(replacement);

    const char *occurrence = strstr(source, pattern);

    if (!occurrence)
        return strdup(source);
    size_t new_size = strlen(source) - pattern_len + replacement_len + 1;
    char *new_str = (char *)malloc(new_size);
    if (!new_str)
        return NULL;
    memcpy(new_str, source, occurrence - source);
    new_str[occurrence - source] = '\0';
    strcat(new_str, replacement);
    strcat(new_str, occurrence + pattern_len);
    return new_str;
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

void ft_expanding(char **args, s_env *export_i)
{
	int i = 0;
	int j;
    char *expanded_cmd;
    char *key;
    char *value;
    i = j = 0;

    
    while (args[i])
    {
        if (is_single(args[i]) == 1)
            return ;
        j = 0;
        while (args[i] && args[i][j])
        {
                if (args[i][j] == '$')
                {
                    key = get_env_key(args[i], j);
                    if (!key)
                        exit(EXIT_FAILURE);       
                    value = get_env_value(key, export_i);
					printf("value = %s\n", value);
					if (!value)
					{
                        key = ft_strjoin("$", key);
                        args[i] = ft_str_replace(args[i], key, strdup(""));   
                        args[i] = ft_substr(args[i], 0, strlen(args[i]));
						return ;
					}					
                    if (strcmp(value, "") && strcmp(value, " "))
                    {
                        key = ft_strjoin("$", key);
                        expanded_cmd = ft_str_replace(args[i], key, value);
                        expanded_cmd = ft_substr(expanded_cmd, 0, strlen(expanded_cmd));
                        free(args[i]);
                        args[i] = expanded_cmd;
                        args[i] = ft_substr(args[i], 0, strlen(args[i]));
                        free(key);
                        free(value);
                    }
                    else if (value)
                    {
                        // key = ft_strjoin("$", key);
                        args[i] = ft_str_replace(args[i], key, strdup(""));    
                        args[i] = ft_substr(args[i], 0, strlen(args[i]));
                    }
                }
            j++;
        }
        i++;
    }
}

