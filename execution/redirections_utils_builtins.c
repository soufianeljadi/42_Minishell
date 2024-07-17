/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_builtins.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:49:09 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/17 16:08:09 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_special_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\''
		|| c == '"' || c == '<' || c == '>');
}

static int	is_only_spaces_tabs_quotes_redirections(const char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (!is_special_char(str[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < len - 1)
	{
		if ((str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>'))
			return (0);
		i++;
	}
	return (1);
}

static char	**l_to_args(char *line)
{
	char	**cmds;
	t_parse	d;
	char	*str;

	d.count = 0;
	d.dq = 0;
	d.sq = 0;
	d.i = 0;
	if (!is_only_spaces_tabs_quotes_redirections(line))
	{
		str = ft_add_sep(line);
		cmds = split_args(str);
		free(str);
		return (cmds);
	}
	str = ft_add_sep(line);
	cmds = split_args(str);
	free (str);
	return (cmds);
}

static int	handle_redirections_builtins(char **red, int *fd_in, int *fd_out, char *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (red[i])
	{
		if (!ft_strcmp(red[i], "<") || !ft_strcmp(red[i], "<<"))
		{
			if (!ft_strcmp(red[i], "<<") && !cmd)
				exit(0);
			flag = redirection_in_builtins(red[i], red[i + 1], fd_in);
		}
		if (!ft_strcmp(red[i], ">>"))
			flag = redirection_double_out_builtins(red[i + 1], fd_out);
		if (!ft_strcmp(red[i], ">"))
			flag = redirection_out_builtins(red[i + 1], fd_out);
		i++;
	}
	return (flag);
}

int	execute_with_redirection_builtins(t_data *data)
{
	int		fd_in;
	int		fd_out;
	int		flag;
	char	**red;
	char	*r;

	(1) && (fd_in = 0, fd_out = 1, flag = 0);
	if (data->lst->redirection)
	{
		r = ft_strdup(data->lst->redirection);
		red = l_to_args(r);
		if (!red)
			return (0) ;
		flag = handle_redirections_builtins(red, &fd_in, &fd_out, data->lst->cmd);
		(free(r), ft_free_tab(red));
	}
	return (flag);
}
