/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null_utils_three.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:16:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/20 11:13:36 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_invalid_key(char *key)
{
	print_error(key);
	exit_stat(1);
}

void	handle_invalid_plus(char *key, char *arg, int j)
{
	char	*tmp;
	char	*error_message;

	tmp = ft_strdup(&arg[j]);
	error_message = ft_strjoin(key, tmp);
	print_error(error_message);
	free(tmp);
	free (key);
	exit_stat(1);
}

int	is_invalid_plus(char *arg, int j)
{
	return (arg[j] == '+' && arg[j + 1] != '=');
}

char	*extract_key(char *arg, int *j)
{
	while (arg[*j] && arg[*j] != '=' && arg[*j] != '+')
		(*j)++;
	return (ft_substr(arg, 0, *j));
}

int	contains_space_or_tab(char *arg)
{
	return (ft_strstr(arg, " ") || ft_strstr(arg, "\t"));
}
