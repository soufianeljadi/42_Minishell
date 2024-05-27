/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:24:11 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/27 20:41:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *remove_protection(char *str)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	check_memory_allocation(new_str);
	while (str[i])
	{
		if (str[i] != '\"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);

}

int count_quotes(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char *extract_value(char *arg, int start, int end)
{
    char *value ;
	
	value = ft_substr(arg, start, end - start);
	if (count_quotes(value, '\"') % 2 == 0)
    	del_dbl_quotes(value);
	else if (count_quotes(value, '\'') % 2 == 0)
		del_sngl_quotes(value);
    return (value);
}

void update_env_value(s_env *env, char *key, char *value)
{
	s_env *current = env;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			return;
		}
		current = current->next;
	}
	ft_lstadd_back(&env, ft_lstnew_data(value, key));
}

void fct_equal(char **args, s_env *env, char *key)
{
	int start = ++env->j;
	while (args[env->i][env->j] && args[env->i][env->j] != '\0')
		env->j++;
	char *value = extract_value(args[env->i], start, env->j);
	printf("value = %s\n", value);
	update_env_value(env, key, value);
}

void concat_value(s_env *env, char *key, char *value)
{
    s_env *current = env;
    while (current != NULL) 
	{
        if (strcmp(current->key, key) == 0) 
		{
            current->value = ft_strjoin(current->value, value);
            return;
        }
        current = current->next;
    }
}

void ftc_concatination(char **args, s_env *env, char *key)
{
    int start;
    env->j += 2;
    start = (args[env->i][env->j] == '"') ? ++env->j : env->j;
    while (args[env->i][env->j] && args[env->i][env->j] != '"')
        env->j++;
    char *value = ft_substr(args[env->i], start, env->j - start);
    concat_value(env, key, value);
}
