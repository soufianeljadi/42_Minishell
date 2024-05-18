/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/18 18:10:10 by sdiouane         ###   ########.fr       */
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

char *concat_strings(char **strings, int count) {
    int total_length = 0;
    for (int i = 0; i < count; i++) {
        total_length += strlen(strings[i]);
    }
    total_length += count - 1;
    char *result = (char *)malloc((total_length + 1) * sizeof(char));
    if (!result) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }
    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(result, strings[i]);
        if (i < count - 1) strcat(result, " ");
    }
    return result;
}


// char *ft_expanding(char *commande, s_env *export_i) {
//     if (!commande) exit(EXIT_FAILURE);
//     char **exp_commande = ft_split(commande, ' ');
//     if (!exp_commande) exit(EXIT_FAILURE);

// 	int i = 0;
//     for (i = 0; exp_commande[i]; i++) {
//         if (is_single(exp_commande[i])) return strdup(exp_commande[i]);
//         for (int j = 0; exp_commande[i][j]; j++) {
//             if (exp_commande[i][j] == '$') {
//                 char *key = get_env_key(exp_commande[i], j);
//                 if (!key) exit(EXIT_FAILURE);
//                 char *value = get_env_value(key, export_i);
//                 if (!value) value = strdup("");
//                 char *new_str = ft_str_replace(exp_commande[i], key, value);
//                 if (!new_str) exit(EXIT_FAILURE);
//                 free(exp_commande[i]);
//                 exp_commande[i] = new_str;
//                 free(key);
//                 free(value);
//             }
//         }
//     }
//     char *s = concat_strings(exp_commande, i);
//     printf("s = %s\n", s);
// 	if (strstr(s, "$"))
// 		supprimerDoll(s);
//     printf("s = %s\n", s);
//     return s;
// }


// char *ft_expanding(char *commande, s_env *export_i)
// {
//     char	**exp_commande;
// 	char	*exp_cmd;
// 	char	*key;
// 	char	*value;
//     int		i;

// 	if (!commande)
// 		exit(EXIT_FAILURE);
// 	(/*xp_commande = strdup(commande),*/ i = 0, exp_cmd = NULL);
// 	exp_commande = ft_split(commande, ' ');
// 	while (exp_commande[i])
// 	{
// 		if (is_single(exp_commande[i]) == 1)
// 			return (exp_commande[i]);
// 		int j = 0;
// 		while (exp_commande && exp_commande[i][j] != '\0')
// 		{
// 			if (exp_commande[i] && exp_commande[i][j] == '$') 
// 			{
// 				key = get_env_key(exp_commande[i], j);
// 				if (!key)
// 					exit(EXIT_FAILURE);
// 				value = get_env_value(key, export_i);
// 				if (!value || !strcmp(value, "") || !strcmp(value, " "))
// 				{
// 					exp_commande[i] = ft_str_replace(exp_commande[i], key, strdup(""));
// 					(free(key), free(value));
// 				}
// 				else
// 				{
// 					key = ft_strjoin("$", key);
// 					exp_cmd = ft_str_replace(exp_commande[i], key, value);
// 					(free(exp_commande[i]), exp_commande[i] = exp_cmd);
// 					(free(key), free(value));
// 				}
// 			}
// 				i++;
// 		}
// 	}
// 	// del_dbl_quotes(exp_commande);
	// if (strstr(exp_commande, "$"))
	// 	supprimerDoll(exp_commande);
// 	char *s = concat_strings(exp_commande, i);
// 	printf("s = %s\n", s);
//     return (s);
// }

int expanded(char **str) {
    int i = 0;

    while (str[i]) {
        int j = 0;
        int in_double_quote = 0;

        while (str[i][j]) {
            if (str[i][j] == '"') {
                in_double_quote = !in_double_quote;
            }

            if (in_double_quote && str[i][j] == '$') {
                return 1;
            }

            j++;
        }

        i++;
    }

    return 0;
}


char *ft_expanding(char *commande, s_env *export_i)
{
    char *exp_commande = strdup(commande);
    char *exp_cmd = NULL;
    char *key = NULL;
    char *value = NULL;
    int i = 0;

    if (!exp_commande)
        exit(EXIT_FAILURE);
    while (exp_commande && exp_commande[i] != '\0')
	{
		// 	return (strdup(exp_commande));
		// if (exp_commande[i] == '$')
		if (axpanded(exp_commande, i) == 1)
        if (exp_commande[i] == '$' && (exp_commande[i + 1] != ' ' && exp_commande[i + 1] != '\0' && exp_commande[i + 1] != '\t'))
		{
            key = get_env_key(exp_commande, i);
            if (!key)
                exit(EXIT_FAILURE);
			value = get_env_value(key, export_i);
            if (!value || !strcmp(value, "") || !strcmp(value, " "))
			{
				key = ft_strjoin("$", key);
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
    return exp_commande;
}
