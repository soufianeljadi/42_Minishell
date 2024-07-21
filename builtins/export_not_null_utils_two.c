/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null_utils_two.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:16:44 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/20 11:59:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quotes(char *str, char c)
{
	int	i;
	int	count;

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

char	*extract_value(char *arg, int start, int end)
{
	char	*value;

	value = ft_substr(arg, start, end - start);
	return (value);
}

void	remove_q(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		if (chaine[i] != '\'')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}

t_env	*begin_export(t_env *env, char **args, char *key)
{
	if (args[env->i][env->j] == '=')
		fct_equal(args, env, key);
	else if (args[env->i][env->j] == '+' && args[env->i][env->j + 1] == '=')
		ftc_concatination(args, env, key);
	else if (existe_deja(key, env) == 0)
	{
		ft_lstadd_back(&env, ft_lstnew_data(NULL, ft_strdup(key)));
	}
	return (env);
}
