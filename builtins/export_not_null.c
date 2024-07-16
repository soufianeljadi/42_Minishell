/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:25:42 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/13 18:01:16 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str, char *type)
{
	ft_putstr_fd("minishell: `", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(str);
}

void	process_argument(char **args, t_env *env, int i)
{
	char	*key;
	int		j;

	(1) && (j = 0, key = NULL);
	key = extract_key(args[i], &j);
	if (is_invalid_plus(args[i], j))
		handle_invalid_plus(key, args[i], j);
	else if (verif_export(key) == 0)
	{
		(1) && (env->i = i, env->j = j);
		begin_export(env, args, key);
		free(key);
	}
	else
		handle_invalid_key(key);
}

t_env	*process_export_args(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		process_argument(args, env, i);
		i++;
	}
	return (env);
}

t_env	*not_null(char **args, t_env *env)
{
	if (!ft_strcmp(args[0], "export"))
	{
		if (!args[1])
			print_export(env);
		else
			env = process_export_args(args, env);
	}
	return (env);
}
