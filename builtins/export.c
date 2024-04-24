/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:11:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/23 16:07:36 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
		return (1);
	while (str[i])
	{
		if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
			return (1);
		i++;
	}
	return (0);
}

char *remove_quotes(char *input)
{
	char *result;
    if (input == NULL || strlen(input) < 2)
        return NULL;
    result = malloc(strlen(input) - 1);
    if (result == NULL)
        return NULL;
    strncpy(result, input + 1, strlen(input) - 1);
    result[strlen(input) - 1] = '\0';
	
    return (result);
}


int existe_deja(char *key, s_env *env)
{
	s_env *current;

	current = env;
	while (current != NULL && current->value)
	{
		if (strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

s_env *export_fct(char **args, s_env *env, s_env *export_i, char **eenv)
{
	int i = 1;
	int j;
	// int f = 0;
	char *key;
	char *value;
	s_env *current;

	// if (!eenv[0] && !strcmp(args[0], "export") && !args[1])
	// 	print_export(export_i);
	// else if (!strcmp(args[0], "export") && !args[1])
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
					{
						printf("+++++++++++++++++++|%s|++++++++++++++++++\n", key);
						ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
					}
				}
				else
				{
					if (args[i][j] == '=')
					{
						j++;
						int start;
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
					else if (args[i][j] == '+' && args[i][j + 1] == '=')
					{
						j = j + 2;
						int start;
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
				}
			}
			else
				syntax_error();
			i++;
		}
	}
	if (!eenv[0] && !strcmp(args[0], "export") && !args[1])
		print_export(export_i);
	
	return (env);
}
