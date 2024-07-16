/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/15 01:34:38 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_key(char *key)
{
	return (verif_export(key) == 1);
}

static void	handle_unset_quotes(char *arg)
{
	if (arg[0] == '"')
		dbl_q(arg);
	if (arg[0] == '\'')
		sng_q(arg);
}

static t_env	*remove_env_var(t_env *env, char *key)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0 && ft_strcmp(current->key, "_"))
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
	return (env);
}

t_env	*unset_fct(char **args, t_env *env)
{
	int		i;
	char	*key;

	(1) && (key = NULL, i = 0);
	if (ft_strcmp(args[0], "unset") == 0)
	{
		while (args[++i])
		{
			handle_unset_quotes(args[i]);
			key = strtok(args[i], " \t");
			while (key)
			{
				if (is_valid_key(key))
				{
					fprintf(stderr,
						"minishell: unset: %s: not a valid identifier\n", key);
					exit_stat(1);
				}
				else
					env = remove_env_var(env, key);
				key = strtok(NULL, " \t");
			}
		}
	}
	return (exit_stat(0), env);
}
