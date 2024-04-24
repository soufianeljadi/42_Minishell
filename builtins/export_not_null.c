/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:25:42 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/24 22:02:29 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void fct_equal(char **args, s_env *env, char *key, int j)
{
	int i = 1;
	char *value;
	int start;
	s_env *current;

	j++;
	start = j;
	if (args[i][j] == '"')
	{
		j++;
		while (args[i][j] && args[i][j] != '"')
			j++;
	}
	else
		while (args[i][j] && args[i][j] != ' ')
			j++;
	value = ft_substr(args[i], start, j - start);
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

void ftc_concatination(char **args, s_env *env, char *key, int j)
{
	int i = 1;
	char *value;
	int start;
	s_env *current;
	
	j = j + 2;
	start = j;
	while (args[i][j] && args[i][j] != ' ')
		j++;
	value = ft_substr(args[i], start, j - start);
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

s_env *not_null(char **args, s_env *env)
{
	int i = 1;
	int j;
	char *key;

	if (!strcmp(args[0], "export") && !args[1])
		print_export(env);
	else if (!strcmp(args[0], "export") && args[1])	
	{
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
						fct_equal(args, env, key, j);
					else if (args[i][j] == '+' && args[i][j + 1] == '=')
						ftc_concatination(args, env, key, j);
				}
			}
			else
				syntax_error();
			i++;
		}
	}
	return (env);	
}