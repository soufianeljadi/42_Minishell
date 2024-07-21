/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null_utils_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:24:11 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/20 11:59:44 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_value(t_env *env, char *key, char *value)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&env, ft_lstnew_data(value, ft_strdup(key)));
}

void	fct_equal(char **args, t_env *env, char *key)
{
	int		start;
	char	*value;

	start = ++env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != '\0')
		env->j++;
	value = extract_value(args[env->i], start, env->j);
	update_env_value(env, key, value);
	exit_stat(0);
}

void	concat_value(t_env *env, char *key, char *value)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strjoin(current->value, value);
			flag = 1;
			return ;
		}
		current = current->next;
	}
	if (flag == 0)
		ft_lstadd_back(&env, ft_lstnew_data(ft_strdup(value), ft_strdup(key)));
	exit_stat(0);
}

void	ftc_concatination(char **args, t_env *env, char *key)
{
	int		start;
	char	*value;

	env->j += 2;
	if (args[env->i][env->j] == '"')
		env->j++;
	start = env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != '"')
		env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	concat_value(env, key, value);
	free (value);
}
