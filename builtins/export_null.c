/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:24:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/04 22:17:30 by sel-jadi         ###   ########.fr       */
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

void	is_equal(char **args, s_env *env, char *key)
{
	s_env	*current;
	char	*value;
	int		start;

	start = ++env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != '\0')
		env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	if (value[0] == '"')
		del_qotes1(value);
	current = env;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			return ;
		}
		current = current->next;
	}
	ft_lstadd_back(&env, ft_lstnew_data(value, key));
}

void	concatenation(char **args, s_env *env, char *key)
{
	s_env	*current;
	int		start;
	char	*value;

	env->j += 2;
	start = (args[env->i][env->j] == '"') ? ++env->j : env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != '"')
		env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	current = env;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			current->value = ft_strjoin(current->value, value);
			return ;
		}
		current = current->next;
	}
}

void	check(char *key, int i, int j, char **args, s_env *env)
{
	if (args[i][j] == '+')
	{
		if (args[i][j + 1] != '=')
			printf("export : %c, not a valid identifier", args[i][j]);
		else
			concatenation(args, env, key);
	}
	else if (args[i][j] == '=')
		is_equal(args, env, key);
	else if (args[i][j] == '\0')
	{
		if (!existe_deja(key, env))
			ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
	}
}

void	is_null(char **args, s_env *env)
{
	char	*key;
	int		i;
	int		j;

	key = NULL;
	if (!strcmp(args[0], "export"))
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
				check(key, i, j, args, env);
				i++;
			}
		}
	}
}
