/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:55:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 19:07:00 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**splt_args(char *line)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = split_args(line);
	while (cmds[i])
	{
		ft_rm_quotes(cmds[i]);
		i++;
	}
	return (cmds);
}

int	should_remove_quotes(char *s)
{
	int	contains_space;
	int	contains_tab;

	(1) && (contains_space = 0, contains_tab = 0);
	if (ft_strstr(s, " "))
		contains_space = 1;
	if (ft_strstr(s, "\t"))
		contains_tab = 1;
	return ((contains_space || contains_tab) && is_blank(s));
}

char	**handle_backslash_case(char *s)
{
	char	**cmd;

	(supprimer_protection(s), del_sngl_quotes(s));
	cmd = ft_malloc(sizeof(char *) * 2);
	if (!cmd)
		exit(EXIT_FAILURE);
	cmd[0] = ft_strdup(s);
	if (!cmd[0])
		(free(cmd), exit(EXIT_FAILURE));
	cmd[1] = NULL;
	return (cmd);
}

char	**check_quotes_before_execution(char *s)
{
	char	**cmd;

	if (!s)
		exit(EXIT_FAILURE);
	cmd = splt_args(s);
	if (!cmd)
		exit(EXIT_FAILURE);
	return (cmd);
}
