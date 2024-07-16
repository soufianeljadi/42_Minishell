/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:01:18 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/11 23:01:55 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_bultin(char *cmd)
{
	if (cmd && !ft_strcmp(cmd, "echo"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "cd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "pwd"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "export"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "unset"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "env"))
		return (1);
	else if (cmd && !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
