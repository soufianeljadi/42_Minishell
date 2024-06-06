/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:25:42 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/06 18:24:08 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

s_env *begin_export(s_env *env, char **args, char *key)
{
	if (args[env->i][env->j] == '=')
		fct_equal(args, env, key);
	else if (args[env->i][env->j] == '+' && args[env->i][env->j + 1] == '=')
		ftc_concatination(args, env, key);
	else if (existe_deja(key, env) == 0)
		ft_lstadd_back(&env, ft_lstnew_data(NULL, key));
	return (env);
}

void print_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free (str);
}

s_env	*process_export_args(char **args, s_env *env)
{
	int		i;
	int		j;
	char	*key;

	(1) && (i = 1, key = NULL);
	while (args[i])
	{
		if (strstr(args[i], " ") || strstr(args[i], "\t"))
			del_dbl_quotes(args[i]);
		j = 0;
		while (args[i][j] && args[i][j] != '=' && args[i][j] != '+')
			j++;
		key = ft_substr(args[i], 0, j);
		if (args[i][j] == '+' && args[i][j + 1] != '=')
			(print_error(ft_strjoin(key, ft_strdup(&args[i][j]))), exit_stat(1));
		else if (verif_export(key) == 0)
		{
			(env->i = i, env->j = j);
			begin_export(env, args, key);
		}
		else
			(print_error(key), exit_stat(1));
		i++;
	}
	return (env);
}

s_env	*not_null(char **args, s_env *env)
{
	if (!strcmp(args[0], "export"))
	{
		if (!args[1])
			print_export(env);
		else
			env = process_export_args(args, env);
	}
	return (env);
}
