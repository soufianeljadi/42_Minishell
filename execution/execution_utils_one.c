/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_one.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:55:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/15 00:54:37 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**splt_args(char *line)
{
	char	**cmds;

	cmds = split_args(line);
	return (cmds);
}

void	process_command(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (count_quotes(cmd[i], '\"') % 2 == 0
			&& ft_strstr(cmd[i], "\"") != NULL
			&& !just_quotes(cmd[i]))
			del_dbl_quotes(cmd[i]);
		else if (count_quotes(cmd[i], '\'') % 2 == 0
			&& ft_strstr(cmd[i], "'") != NULL && !just_quotes(cmd[i]))
			del_sngl_quotes(cmd[i]);
		i++;
	}
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
	if (should_remove_quotes(s))
		supprimerguillemets(s);
	cmd = splt_args(s);
	if (!cmd)
		exit(EXIT_FAILURE);
	process_command(cmd);
	return (cmd);
}
