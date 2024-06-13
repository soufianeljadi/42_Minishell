/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/07 20:13:45 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_before_begin(char *args)
{
	if (args[0] == '"')
		del_dbl_quotes(args);
	if (args[0] == '\'')
		del_sngl_quotes(args);
	return (args);
}

void ft_valid_identif(s_env *env, s_env *current, s_env *prev, char *key)
{
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}
						
}

int skip_words(char *args, int j)
{
	while (args && args[j] != ' ' && args[j] != '\t' && args[j] != '\0')
		j++;
	return (j);
}

int skip_spaces(char *args, int j)
{
	while (args[j] == ' ' || args[j] == '\t')
		j++;
	return (j);
}

void print_error(char *str, char *type)
{
	ft_putstr_fd("minishell: `", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free (str);
}

s_env	*unset_fct(char **args, s_env *env)
{
	int		i;
	int		j;
	char	*key;
	s_env	*prev;
	s_env	*current;

	(1) && (i = -1, prev = NULL, current = NULL);
	if (!strcmp(args[0], "unset"))
	{
		while (args[++i])
		{
			(1) && (args[i] = ft_before_begin(args[i]), j = 0);
			while (args[i][j])
			{
				(1) && (j = skip_words(args[i], j),
					key = ft_substr2(args[i], 0, j), current = env);
				if (verif_export(key) == 1)
					return(print_error(key, "unset"), exit_stat(1), env);
				else
					(ft_valid_identif(env, current, prev, key),
						free(key), j = skip_spaces(args[i], j));
			}
		}
	}
	return (exit_stat(0), env);
}
