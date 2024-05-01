/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:11:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/01 17:08:49 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
		return (1);
	while (str[i])
	{
		if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

char *remove_quotes(char *input)
{
	char *result;
    if (input == NULL || strlen(input) < 2)
        return NULL;
    result = malloc(strlen(input) - 1);
    if (result == NULL)
        return NULL;
    strncpy(result, input + 1, strlen(input) - 1);
    result[strlen(input) - 1] = '\0';
	
    return (result);
}


int existe_deja(char *key, s_env *env)
{
	s_env *current;

	current = env;
	while (current != NULL && current->value)
	{
		if (strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

s_env *export_fct(char **args, s_env *env, s_env *export_i, char **eenv)
{
	
	if (!eenv[0])
		is_null(args, env, export_i);
	else if (eenv[0])
		return (not_null(args, env));
	return (export_i);
}
