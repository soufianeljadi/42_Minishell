/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:08:19 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/15 01:09:58 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *key, t_env *export_i)
{
	t_env		*tmp;
	char		*value;

	value = NULL;
	tmp = export_i;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->value != NULL)
			{
				value = ft_strdup(tmp->value);
				return (value);
			}
		}
		tmp = tmp->next;
	}
	free(value);
	return (NULL);
}

void	supprimer_dollar(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i] != '\0')
	{
		if (chaine[i] != '$')
		{
			chaine[j++] = chaine[i];
		}
		i++;
	}
	chaine[j] = '\0';
}

char	*ft_str_replace(char *s, char *key, char *value)
{
	int		s_len;
	int		key_len;
	int		value_len;
	char	*occurrence;
	char	*new_str;

	(1) && (new_str = NULL, s_len = ft_strlen(s), key_len = ft_strlen(key));
	(1) && (value_len = ft_strlen(value), occurrence = ft_strstr(s, key));
	if (!occurrence || !value || !key)
	{
		if (value)
			free(value);
		return (free(key), ft_strdup(s));
	}
	new_str = ft_malloc(s_len + value_len + 1);
	if (!new_str)
		return (free(occurrence), free(key), NULL);
	ft_strncpy(new_str, s, occurrence - s);
	new_str[occurrence - s] = '\0';
	(ft_strcat(new_str, value), ft_strcat(new_str, occurrence + key_len));
	occurrence = NULL;
	if (occurrence)
		free(occurrence);
	(free(key), free(value));
	return (new_str);
}

char	*get_env_key(char *str, int i)
{
	char	*key;
	int		key_start;

	key = NULL;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$' && str[i + 1])
	{
		i++;
		key_start = i;
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_' || str[i] == '?'))
			i++;
		key = (char *)ft_malloc((i - key_start + 1) * sizeof(char));
		if (!key)
			exit(EXIT_FAILURE);
		ft_strncpy(key, &str[key_start], i - key_start);
		key[i - key_start] = '\0';
	}
	else
		key = ft_strdup(&str[i]);
	return (key);
}

int	is_closed(char *str, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '\0' || i >= n)
				return (0);
		}
		i++;
	}
	return (1);
}
