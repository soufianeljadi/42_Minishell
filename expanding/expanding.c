/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/02 22:51:44 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_memory_allocation(void *ptr)
{
    if (!ptr) exit(EXIT_FAILURE);
}


char *protect_value(char *str)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	check_memory_allocation(new_str);
	new_str = ft_strjoin("\'", str);
	check_memory_allocation(new_str);
	new_str = ft_strjoin(new_str, "\'");
	check_memory_allocation(new_str);
	return (new_str);
}

// char *remove_protection(char *str)
// {
// 	char *new_str;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	new_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
// 	check_memory_allocation(new_str);
// 	while (str[i])
// 	{
// 		if (str[i] != '\\')
// 			new_str[j++] = str[i];
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);

// }



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

char *concat_str(char *s, char **args)
{
	int i = 1;
	while (args[i])
	{
		s = ft_strjoin(s, args[i]);
		i++;
	}
	return (s);
}

char *new(char *str)
{
	char **args = ft_split(str, ' ');
	char *s = NULL;
	
	if (strcmp(args[0], "export") == 0)
	{
		s = concat_str(s, args);
	}
	else
	{
		s = strdup(str);
	}
	return (s);
}

char *process_variable(char *exp_commande, t_p *p, s_env *export_i)
{
    char *key;
    char *value;
    char *full_key;
    char *exp_cmd;

    key = get_env_key(exp_commande, p->i);
    check_memory_allocation(key);
    value = get_env_value(key, export_i);
	if (value && value[0] == '\"' && value[ft_strlen(value) - 1] == '\"')
		value = ft_substr2(value, 1, ft_strlen(value) - 2);
	else if (value && value[0] == '\'' && strcmp(value, "\""))
	{
		value = ft_strjoin("\\", value);
		value = ft_strjoin(value ,"\\");
	}
    if (!value || !strcmp(value, "") || !strcmp(value, " "))
	{
		if (strcmp(key, ""))
		{
			full_key = ft_strjoin("$", key);
        	exp_commande = ft_str_replace(exp_commande, full_key, strdup(" "));
		}
        (free(key), free(value));
    }
	else
	{
        full_key = ft_strjoin("$", key);
        check_memory_allocation(full_key);
        exp_cmd = ft_str_replace(exp_commande, full_key, value);
        (check_memory_allocation(exp_cmd), free(exp_commande));
        exp_commande = strdup(exp_cmd);
        check_memory_allocation(exp_commande);
        (free(full_key), free(exp_cmd), free(key), free(value));
    }
    return (exp_commande);
}

char *exp_fct(char *commande, s_env *export_i, int *flag)
{
    char *exp_commande;
    t_p p = {0, 0, 0, '\0'};
	
    if (!commande) exit(EXIT_FAILURE);
    exp_commande = strdup(commande);
    check_memory_allocation(exp_commande);
    while (exp_commande && exp_commande[p.i] != '\0')
	{
        handle_quotes(exp_commande, &p);
        if (exp_commande[p.i] == '$' && exp_commande[p.i + 1] == '?')
        {
            exp_commande = ft_str_replace(exp_commande, ft_strdup("$?"), ft_itoa(g_flags.exit_status));
        }
        if (exp_commande[p.i] == '$' && (!p.quote_open || (p.quote_open && p.current_quote == '"')))
		{
            exp_commande = process_variable(exp_commande, &p, export_i);
            check_memory_allocation(exp_commande);
			*flag = 1;
        }
        p.i++;
    }
    return (exp_commande);
}

noued_cmd *ft_expanding(ExecutionData **data, s_env *export_i)
{
    ExecutionData *tmp = *data;
    noued_cmd *current = tmp->lst;
	int f = 0;

    while (current)
	{
        if (current->cmd)
            current->cmd = exp_fct(current->cmd, export_i, &f);
        if (current->redirection)
            current->redirection = exp_fct(current->redirection, export_i, &f);
        current = current->next;
    }
    current = tmp->lst;
    while (current)
        current = current->next;
		
    return (tmp->lst);
}


// char *process_variable(char *exp_commande, t_p *p, s_env *export_i)
// {
//     char *key;
//     char *value;
//     char *full_key;
//     char *exp_cmd;

//     key = get_env_key(exp_commande, p->i);
//     check_memory_allocation(key);
//     value = get_env_value(key, export_i);
// 	// value = protect_value(value);
// 	printf("value = %s\n", value);
// 	if (!value || !strcmp(value, ""))
// 	{
// 		// if (strcmp(key, ""))
// 		// {
// 			key = ft_strjoin("$", key);
// 			exp_commande = ft_str_replace(exp_commande, key, strdup(""));
// 			check_memory_allocation(exp_commande);
// 		// }
// 		(free(key), free(value));
// 	}
// 	else
// 	{
// 		full_key = ft_strjoin("$", key);
// 		check_memory_allocation(full_key);
// 		exp_cmd = ft_str_replace(exp_commande, full_key, value);
// 		(check_memory_allocation(exp_cmd), free(exp_commande));
// 		exp_commande = strdup(exp_cmd);
// 		check_memory_allocation(exp_commande);
// 		(free(full_key), free(exp_cmd), free(key), free(value));
// 	}
//     return (exp_commande);
// }

// char *exp_fct(char *commande, s_env *export_i)
// {
//     char	*exp_commande;
//     t_p		p;

// 	(1) && (p= (t_p){0, 0, 0, '\0'}, exp_commande = NULL);
//     if (!commande) exit(EXIT_FAILURE);
//     exp_commande = strdup(commande);
//     check_memory_allocation(exp_commande);
//     while (exp_commande && exp_commande[p.i] != '\0')
// 	{
//         handle_quotes(exp_commande, &p);
//         if (exp_commande[p.i] == '$' && (!p.quote_open || (p.quote_open && p.current_quote == '"')))
// 		{
//             exp_commande = process_variable(exp_commande, &p, export_i);
//             check_memory_allocation(exp_commande);
//         }
//         p.i++;
//     }
// 	// if (strstr(exp_commande, "$") && is_closed(exp_commande, p.i) == 0)
//     return (exp_commande);
// }

// noued_cmd *ft_expanding(ExecutionData **data, s_env *export_i)
// {
//     ExecutionData	*tmp;
//     noued_cmd		*current;

// 	(1) && (tmp = *data, current = tmp->lst);
//     while (current)
// 	{
//         if (current->cmd)
//             current->cmd = exp_fct(current->cmd, export_i);
//         if (current->redirection)
//             current->redirection = exp_fct(current->redirection, export_i);
//         current = current->next;
//     }
//     current = tmp->lst;
//     while (current)
//         current = current->next;
//     return (tmp->lst);
// }

