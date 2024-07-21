/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/20 11:21:48 by sel-jadi         ###   ########.fr       */
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

void	ft_free_key(char *key)
{
	if (key)
		free (key);
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
			key = ft_strtok(args[i], " \t");
			while (key)
			{
				if (is_valid_key(key))
					(print_error(key), exit_stat(1));
				else
				{
					env = remove_env_var(env, key);
					free (key);
				}
				(key = ft_strtok(NULL, " \t"));
			}
		}
		ft_free_key(key);
	}
	return (exit_stat(0), env);
}
