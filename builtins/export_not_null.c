/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:25:42 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/11 14:54:07 by sdiouane         ###   ########.fr       */
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

void fct_equal(char **args, s_env *env, char *key, int f)
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
		while (args[env->i][env->j] && args[env->i][env->j] != '\"')
			env->j++;
	value = ft_substr(args[env->i], start, env->j - start);
	if (f == 1)
		value = ft_strdup("");
	printf("value = %s\n", value);
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
		// sp(value);
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

void ftc_concatination(char **args, s_env *env, char *key)
{
	char *value;
	int start;
	s_env *current;
	
	env->j = env->j + 2;
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
		// value = remove_quotes(value);
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
	int i = 0;
	int j;
	char *key;
	int f = 0;
	
	i = 1;
	if (!strcmp(args[0], "export") && !args[1])
		print_export(env);
	else if (!strcmp(args[0], "export") && args[1])	
	{
		// sp(args[1]);
		// supprimerGuillemets(args[1]);
		while (args[i])
		{
			supprimerGuillemets(args[i]);
			if ((!strcmp(args[i], ">") || !strcmp(args[i], ">>") || !strcmp(args[i], "<") || !strcmp(args[i], "<<")))
			{
				if (args[i + 1])
					i = i + 2;
			}
			j = 0;
			if (!args[i])
				break;
			while (args[i][j] &&  args[i][j] != '=' && args[i][j] != '+') // here
				j++;
			key = ft_substr(args[i], 0, j);
			// j++;
			if (args[i][j] == '+' && (args[i][j + 1] != '='))
				printf("export : %c, not a valid identifier", args[i][j]);
			if (args[i][j] == '=' && (args[i][j + 1] == ' ' || args[i][j + 1] == '\t' || args[i][j + 1] == '\0'))
				f = 1;
			if (verif_export(key) == 0)
			{
				if (args[i][j] == '\0')
				{					
					if (!existe_deja(key, env))
					{
						ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
					}
				}
				else
				{
					if (args[i][j] == '=')
					{
						env->i = i;
						env->j = j;
						fct_equal(args, env, key, f);
					}             
					else if (args[i][j] == '+' && args[i][j + 1] == '=')
					{
						env->i = i;
						env->j = j;
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
