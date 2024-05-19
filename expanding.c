/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/19 21:08:35 by sdiouane         ###   ########.fr       */
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

char *sera_expander_quotes(char *str)
{
	int i = 0;
	int j = 0;
	char *new_str = (char *)malloc((strlen(str) + 1) * sizeof(char));
	if (!new_str)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				new_str[j++] = str[i++];
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				new_str[j++] = str[i++];
		}
		else
			i++;
			// new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);		
}



char get_q(char *str)
{
	while(*str)
		if(ft_strchr("\'\"",*(str++)))
			return *(str - 1);
	return(0);
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

// char *ft_expanding(char *commande, s_env *export_i)
// {
//     char	*exp_commande;
//     char	*exp_cmd;
//     char	*key;
//     char	*value;
// 	t_p		p;
	
// 	if (!commande)
// 		exit(EXIT_FAILURE);
// 	(1) && (p.i = 0, p.j = 0, p.quote_open = 0, p.current_quote = '\0');
// 	(1) && (exp_cmd = NULL, key = NULL, value = NULL);
// 	exp_commande = strdup(commande);
//     if (!exp_commande)
//         exit(EXIT_FAILURE);
//     while (exp_commande && exp_commande[p.i] != '\0')
// 	{
//         if (exp_commande[p.i] == '"' || exp_commande[p.i] == '\'')
// 		{
//             if (p.quote_open && exp_commande[p.i] == p.current_quote)
//                 (1) && (p.quote_open = 0, p.current_quote = '\0');
// 			else if (!p.quote_open)
//                 (1) && (p.quote_open = 1, p.current_quote = exp_commande[p.i]);
//         } 
// 		else if (exp_commande[p.i] == '$' && (!p.quote_open || (p.quote_open && p.current_quote == '"')))
// 		{
//             key = get_env_key(exp_commande, p.i);
//             if (!key)
//                 exit(EXIT_FAILURE);
//             value = get_env_value(key, export_i);
//             if (!value || !strcmp(value, "") || !strcmp(value, " "))
// 			{
//                 exp_commande = ft_str_replace(exp_commande, key, strdup(""));
// 				if (!exp_commande)
// 					exit (EXIT_FAILURE);
//         		(free(key), free(value));
//             }
// 			else
// 			{
//                 key = ft_strjoin("$", key);
// 				if (!key)
// 					exit (EXIT_FAILURE);
//                 exp_cmd = ft_str_replace(exp_commande, key, value);
// 				if (!exp_cmd)
// 					exit (EXIT_FAILURE);
//                 free(exp_commande);
//                 exp_commande = strdup(exp_cmd);
// 				if (!exp_commande)
// 					exit (EXIT_FAILURE);
//                 (free(key), free(value));
//             }
//         }
//         p.i++;
//     }

//     if (strstr(exp_commande, "$") && is_closed(exp_commande, p.i) == 0)
//         supprimerDoll(exp_commande);
//     // printf("\nIN EXPANDING :\n");
//     // printf("------------------------------------------ > |%s| <------------------------------------------\n", exp_commande);
//     return (exp_commande);
// }

void check_memory_allocation(void *ptr) 
{
    if (!ptr) exit(EXIT_FAILURE);
}

void handle_quotes(char *exp_commande, t_p *p)
{
    if (exp_commande[p->i] == '"' || exp_commande[p->i] == '\'')
	{
        if (p->quote_open && exp_commande[p->i] == p->current_quote)
		{
            p->quote_open = 0;
            p->current_quote = '\0';
        }
		else if (!p->quote_open)
		{
            p->quote_open = 1;
            p->current_quote = exp_commande[p->i];
        }
    }
}

char *process_variable(char *exp_commande, t_p *p, s_env *export_i)
{
    char *key;
    char *value;
	char *full_key;
	char *exp_cmd;

	(key= get_env_key(exp_commande, p->i), check_memory_allocation(key));
	value = get_env_value(key, export_i);
    if (!value || !strcmp(value, "") || !strcmp(value, " "))
	{
        exp_commande = ft_str_replace(exp_commande, key, strdup(""));
        (check_memory_allocation(exp_commande), free(key), free(value));
    }
	else
	{
        full_key = ft_strjoin("$", key);
        check_memory_allocation(full_key);
        exp_cmd = ft_str_replace(exp_commande, full_key, value);
        check_memory_allocation(exp_cmd);
        free(exp_commande);
        exp_commande = strdup(exp_cmd);
        check_memory_allocation(exp_commande);
        (free(full_key), free(exp_cmd), free(key), free(value));
    }
    return (exp_commande);
}

char *ft_expanding(char *commande, s_env *export_i)
{
    char *exp_commande;
	
    t_p p = {0, 0, 0, '\0'};
    if (!commande) exit(EXIT_FAILURE);
    exp_commande = strdup(commande);
    check_memory_allocation(exp_commande);
    while (exp_commande && exp_commande[p.i] != '\0')
	{
        handle_quotes(exp_commande, &p);
        if (exp_commande[p.i] == '$' && (!p.quote_open || (p.quote_open && p.current_quote == '"')))
		{
            exp_commande = process_variable(exp_commande, &p, export_i);
            check_memory_allocation(exp_commande);
        }
        p.i++;
    }
    if (strstr(exp_commande, "$") && is_closed(exp_commande, p.i) == 0)
        supprimerDoll(exp_commande);
    return exp_commande;
}











				// start = i;
				// while (exp_commande[i] && exp_commande[i] != '\'')
				// 	i++;
				// if (exp_commande[i] == '\'')
				// {
				// 	i++;
				// 	continue;
				// }
				// else
				// {
				// 	exp_commande = ft_substr2(exp_commande, 0, start);
				// 	break;
				// }

// int is_closed(char *str, int n)
// {
// 	int i = 0;

// 	while (str[i] && i < n)
// 	{
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '"')
// 				i++;
// 			if (str[i] == '\0' || i >= n)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// 		// exp_commande = sera_expander_quotes(commande);
// char *ft_expanding(char *commande, s_env *export_i)
// {
//     char *exp_commande = strdup(commande);
//     char *exp_cmd = NULL;
//     char *key = NULL;
//     char *value = NULL;
//     int i = 0;
// 	int start = 0;

//     if (!exp_commande)
//         exit(EXIT_FAILURE);
//     while (exp_commande && exp_commande[i] != '\0')
// 	{
// 		if (exp_commande[i] == '\'')
// 		{
// 		}
// 		if (exp_commande[i] == '$')
// 			{
// 				key = get_env_key(exp_commande, i);
// 				if (!key)
// 					exit(EXIT_FAILURE);
// 				value = get_env_value(key, export_i);
// 				// printf("key = |%s|, value = |%s|\n", key, value);
// 				if (!value || !strcmp(value, "") || !strcmp(value, " "))
// 				{	
// 					exp_commande = ft_str_replace(exp_commande, key, strdup(""));
// 					(free(key), free(value));
// 				}
// 				else
// 				{
// 					key = ft_strjoin("$", key);
// 					exp_cmd = ft_str_replace(exp_commande, key, value);
// 					(free(exp_commande), exp_commande = exp_cmd);
// 					(free(key), free(value));
// 				}
// 			}
// 		i++;
// 	}
//     // printf("BEFORE : exp_commande = |%s|\n", exp_commande);
// 	if (strstr(exp_commande, "$") && is_single(exp_commande) == 0)
//     	supprimerDoll(exp_commande);
// 	printf("\nIN EXPANDING :\n");
// 	printf("------------------------------------------ > |%s| <------------------------------------------\n", exp_commande);
//     return exp_commande;
// }