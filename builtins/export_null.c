/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:24:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/27 10:37:19 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void is_equal(char **args, s_env *export_i, char *key, int i, int j)
{
	int start;
	char *value = NULL;
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
		current = export_i;
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
			ft_lstadd_back(&export_i, ft_lstnew_data(value, key));
	}
	else
	{
		value = remove_quotes(value);
		current = export_i;
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
			ft_lstadd_back(&export_i, ft_lstnew_data(value, key));
	}
}

void concatenation(char **args, s_env *export_i, char *key, int i, int j)
{
	char *value = NULL;
	s_env *current;
	j = j + 2;
	int start;
	start = j;
	while (args[i][j] && args[i][j] != ' ')
		j++;
	value = ft_substr(args[i], start, j - start);
	if (value[0] != '\"')
	{
		current = export_i;
		while (current != NULL && current->value)
		{
			if (strcmp(current->key, key) == 0)
			{
				current->value = ft_strjoin(current->value, value);
				break ;
			}
			current = current->next;
			if (current == NULL)
				ft_lstadd_back(&export_i, ft_lstnew_data(value, key));						
		}
	}
	else
	{
		value = remove_quotes(value);
		current = export_i;
		while (current != NULL && current->value)
		{
			if (strcmp(current->key, key) == 0)
			{
				current->value = ft_strjoin(current->value, value);
				break ;
			}
			current = current->next;
			if (current == NULL)
				ft_lstadd_back(&export_i, ft_lstnew_data(value, key));						
		}
							
	}	
}

void is_null(char **args, s_env *env, s_env *export_i)
{
	int i = 1;
	int j;
	char *key;
	(void)export_i;

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
						is_equal(args, env, key, i, j);
					else if (args[i][j] == '+' && args[i][j + 1] == '=')
						concatenation(args, env, key, i, j);
				}
			}
			else
				syntax_error();
			i++;
		}
	}
}
