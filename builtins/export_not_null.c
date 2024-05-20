/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:25:42 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/20 12:49:47 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sp(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '"')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

void  fct_equal(char **args, s_env *env, char *key)
{
	char	*value;
	s_env	*current;
	int		start;

	value = NULL;
	current = NULL;	
	env->j++;
	start = env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != '\0')
		env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	if (value[0] == '\'')
		value = ft_substr(value, 1, ft_strlen(value) - 2);
	if (value[0] == '\"')
		sp(value);
	current = env;
	while (current != NULL)
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

void ftc_concatination(char **args, s_env *env, char *key)
{
	char *value;
	int start;
	s_env *current;
	
	env->j = env->j + 2;
	start = env->j;
	if (args[env->i][env->j] == '"')
	{
		env->j++;
		start = env->j;
		while (args[env->i][env->j] && args[env->i][env->j] != '"')
			env->j++;
	}
	else
		while (args[env->i][env->j] && args[env->i][env->j] != '\"')
			env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	if (value[0] != '\"')
	{
		current = env;
		while (current != NULL)
		{
			if (strcmp(current->key, key) == 0)
			{
				current->value = ft_strjoin(current->value, value);
				break ;
			}
			current = current->next;
		}
					
	}
	else
	{
		current = env;
		while (current != NULL)
		{
			if (strcmp(current->key, key) == 0)
			{
				current->value = ft_strjoin(current->value, value);
				break ;
			}
			current = current->next;
		}
						
							
	}
}

s_env *not_null(char **args, s_env *env)
{
	int i;
	int j;
	char *key;
	
	i = 1;
	if (!strcmp(args[0], "export") && !args[1])
		print_export(env);
	else if (!strcmp(args[0], "export") && args[1])	
	{
		while (args[i])
		{
			j = 0;
			if (!args[i])
				break;
			while (args[i][j] &&  args[i][j] != '=' && args[i][j] != '+') // here
				j++;
			key = ft_substr(args[i], 0, j);
			if (args[i][j] == '+' && (args[i][j + 1] != '='))
			{
				printf("export : %c, not a valid identifier", args[i][j]);
				return (env);
			}
			if (verif_export(key) == 0)
			{
				if (args[i][j] == '\0')
				{
					if (existe_deja(key, env) == 0)
						ft_lstadd_back(&env, ft_lstnew_data(NULL, key));
				}
				else
				{
					if (args[i][j] == '=')
					{
						(env->i = i, env->j = j);
						fct_equal(args, env, key);
					}             
					else if (args[i][j] == '+' && args[i][j + 1] == '=')
					{
						(env->i = i, env->j = j);
						printf("here\n");
						ftc_concatination(args, env, key);
					}
				}
			}
			else
				fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", args[i]);	
			i++;
		}
	}
	return (env);	
}
