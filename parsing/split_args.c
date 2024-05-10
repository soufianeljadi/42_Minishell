/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:12:06 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/10 12:06:29 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

int	get_end_space(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (is_white_space(inp[i]))
		{
			if (i == 0)
				return (i);
			return (i - 1);
		}
		i++;
	}
	if (inp[i] == '\0')
		return (i - 1);
	return (-1);
}

static char	ft_get_quots_type(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == '\"' || inp[i] == '\'')
			return (inp[i]);
		if (inp[i])
			i++;
	}
	return (0);
}

int	get_end_quots(char *inp)
{
	int		i;
	int		count_qouts;
	char	type;

	type = ft_get_quots_type(inp);
	i = 0;
	count_qouts = 0;
	while (inp[i])
	{
		if ((size_t)i == (ft_strlen(inp)) - 1)
			return (i);
		if (inp[i] == type)
			count_qouts++;
		if (count_qouts % 2 == 0 && count_qouts != 0 && inp[i] == ' ')
			return (i - 1);
		i++;
	}
	if (count_qouts % 2 == 0 && count_qouts != 0 && inp[i] == '\0')
		return (i - 1);
	return (-1);
}

char	**line_to_args(char *line)
{
	char	**cmds;
	char	*sp_line;
	t_parse	d;
	
	d.count = 0;
	d.dq = 0;
	d.sq = 0;
	d.i = 0;
	printf("line[0] = |%c|\tline[1] = |%c|\n", line[0], line[1]);
	// if ((line[0] == '>' || line[0] == '<' || line[0] == '|') && (line[1] == ' ' || line[1] == '\t' || line[1] == '\0'))
	// {
	// 	syntax_error();
	// 	return (NULL);
	// }
	sp_line = ft_add_sep(line, d);
	cmds = split_args(sp_line);

	int i = 0;
	while (cmds[i])
	{
		printf("cmds[%d] = |%s|\n", i, cmds[i]);
		i++;
	}
	
	free(sp_line);
	return (cmds);
}
