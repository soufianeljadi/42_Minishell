/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:11:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/20 12:00:00 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z')
		&& !(str[i] >= 'A' && str[i] <= 'Z'))
		return (1);
	while (str[i])
	{
		if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *input)
{
	char	*result;

	if (input == NULL || ft_strlen(input) < 2)
		return (NULL);
	result = ft_malloc(ft_strlen(input) - 1);
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, input + 1, ft_strlen(input) - 1);
	result[ft_strlen(input) - 1] = '\0';
	return (result);
}

int	existe_deja(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

t_env	*export_fct(char **args, t_env *env, char **eenv)
{
	if (!eenv[0])
		is_null(args, env);
	else if (eenv[0])
		return (not_null(args, env));
	return (env);
}
