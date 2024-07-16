/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:24:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/05 10:48:46 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_qotes1(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		if (chaine[i] != '"')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}

void	is_equal(char **args, t_env *env, char *key)
{
	t_env	*current;
	char	*value;
	int		start;

	start = ++env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != '\0')
		env->j++;
	value = ft_substr2(args[env->i], start, env->j - start);
	if (value[0] == '"')
		del_qotes1(value);
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			free(value);
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&env, ft_lstnew_data(value, key));
	free(value);
}

void	check(char *key, char **args, t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (args[env->i][env->j] == '+')
	{
		if (args[env->i][env->j + 1] != '=')
			printf("export : %c, not a valid identifier", args[env->i][env->j]);
		else
			concatenation(args, env, key);
	}
	else if (args[env->i][env->j] == '=')
		is_equal(args, env, key);
	else if (args[env->i][env->j] == '\0')
	{
		if (!existe_deja(key, env))
		{
			tmp = ft_strdup("");
			ft_lstadd_back(&env, ft_lstnew_data(tmp, key));
			free(tmp);
		}
	}
}

void	is_null(char **args, t_env *env)
{
	char	*key;
	int		i;
	int		j;

	key = NULL;
	if (!ft_strcmp(args[0], "export"))
	{
		if (!args[1])
			print_export(env);
		else
		{
			i = 1;
			while (args[i])
			{
				j = 0;
				while (args[i][j] && args[i][j] != '=' && args[i][j] != '+')
					j++;
				key = ft_substr(args[i], 0, j);
				(1) && (env->i = i, env->j = j);
				check(key, args, env);
				free(key);
				i++;
			}
		}
	}
}

void	increment_j(t_env *env)
{
	env->j += 2;
}
