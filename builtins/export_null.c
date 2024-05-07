/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:24:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/07 16:19:08 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void is_equal(char **args, s_env *env, char *key)
{
	char	*value;
	s_env	*current;
	int		start;
	
	value = NULL;
	current = NULL;
	env->j++;
	start = env->j;
	if (args[env->i][env->j] == '"')
	{
		env->j++;
		while (args[env->i][env->j] && args[env->i][env->j] != '"')
			env->j++;
	}
	else
		while (args[env->i][env->j] && args[env->i][env->j] != ' ')
			env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	if (value[0] != '\"')
	{
		current = env;
		while (current != NULL && current->value)
		{
			if (strcmp(current->key, key) == 0)
			{
				free(current->value);
				current->value = value;
				break;
			}
			current = current->next;
		}
		if (current == NULL)
			ft_lstadd_back(&env, ft_lstnew_data(value, key));
	}
	else
	{
		value = remove_quotes(value);
		current = env;
		while (current != NULL && current->value)
		{
			if (strcmp(current->key, key) == 0)
			{
				free(current->value);
				current->value = value;
				break;
			}
			current = current->next;
		}
		if (current == NULL)
			ft_lstadd_back(&env, ft_lstnew_data(value, key));
	}
}

void concatenation(char **args, s_env *env, char *key)
{
	char *value = NULL;
	s_env *current;
	
	env->j = env->j + 2;
	int start;
	start = env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != ' ')
		env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	if (value[0] != '\"')
	{
		current = env;
		while (current != NULL && current->value)
		{
			if (strcmp(current->key, key) == 0)
			{
				current->value = ft_strjoin(current->value, value);
				break ;
			}
			current = current->next;
			if (current == NULL)
				ft_lstadd_back(&env, ft_lstnew_data(value, key));						
		}
	}
	else
	{
		value = remove_quotes(value);
		current = env;
		while (current != NULL && current->value)
		{
			if (strcmp(current->key, key) == 0)
			{
				current->value = ft_strjoin(current->value, value);
				break ;
			}
			current = current->next;
			if (current == NULL)
				ft_lstadd_back(&env, ft_lstnew_data(value, key));						
		}
							
	}	
}

void is_null(char **args, s_env *env)
{
	int i = 1;
	int j;
	char *key;

	if (!strcmp(args[0], "export") && !args[1])
		print_export(env);
	else if (!strcmp(args[0], "export") && args[1])	
	{
		supprimerGuillemets(args[1]);
		while (args[i])
		{
			j = 0;
			while (args[i][j] &&  args[i][j] != '=' && args[i][j] != '+')
				j++;
			key = ft_substr(args[i], 0, j);
			if (verif_export(key) == 0)
			{
				if (args[i][j] == '\0')
				{		
					if (!existe_deja(key, env))
						ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
				}
				else
				{
					if (args[i][j] == '=')
					{
						env->i = i;
						env->j = j;
						is_equal(args, env, key);
					}
					else if (args[i][j] == '+' && args[i][j + 1] == '=')
					{
						env->i = i;
						env->j = j;
						concatenation(args, env, key);
					}
				}
			}
			else
				fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", args[i]);
			i++;
		}
	}
}
