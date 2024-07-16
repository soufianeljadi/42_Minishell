/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_null_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:28:17 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/06/15 21:42:32 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	determine_start_index(char **args, t_env *env)
{
	if (args[env->i][env->j] == '"')
	{
		env->j++;
		return (env->j);
	}
	return (env->j);
}

static char	*extract_val(char **args, t_env *env, int start)
{
	while (args[env->i][env->j] && args[env->i][env->j] != '"')
		env->j++;
	return (ft_substr2(args[env->i], start, env->j - start));
}

static t_env	*find_current(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void	update_value(t_env *current, char *value)
{
	char	*tmp;

	tmp = ft_strdup(current->value);
	free(current->value);
	current->value = ft_strjoin(tmp, value);
	free(value);
	free(tmp);
}

void	concatenation(char **args, t_env *env, char *key)
{
	t_env	*current;
	int		start;
	char	*value;

	increment_j(env);
	start = determine_start_index(args, env);
	value = extract_val(args, env, start);
	current = find_current(env, key);
	if (current != NULL)
		update_value(current, value);
	else
		free(value);
}
