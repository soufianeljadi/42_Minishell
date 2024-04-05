/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:12:06 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/04/03 00:22:06 by sdiouane         ###   ########.fr       */
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

	type = ft_get_quots_type(inp); // "   " 
	i = 0;
	count_qouts = 0;
	while (inp[i])
	{
		if ((size_t)i == (ft_strlen(inp)) - 1)
			return (i);
		if (inp[i] == type)
			count_qouts++;
		if (count_qouts % 2 == 0 && count_qouts != 0 && inp[i] == ' ') // "   " 
			return (i - 1);
		i++;
	}
	if (count_qouts % 2 == 0 && count_qouts != 0 && inp[i] == '\0') // "   "
		return (i - 1);
	return (-1);
}

int	check_quots(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == ' ')
			return (0);
		else if (inp[i] == '"' || inp[i] == '\'')
			return (1);
		if (inp[i])
			i++;
	}
	return (0);
}

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_count_cmd(char *inp)
{
	t_points	p;

	p.i = 0;
	p.j = 0;
	if (!inp && !*inp)
		return (0);
	while (inp[p.i])
	{
		while (is_white_space(inp[p.i]))
			p.i++;
		if (!inp[p.i])
			break ;
		p.start = p.i;
		if (check_quots(inp + p.i) == 1 && inp[p.i])
		{
			p.end = get_end_quots(inp + p.i) + p.i;
		}
		else if (check_quots(&inp[p.i]) == 0 && inp[p.i])
			p.end = get_end_space(&inp[p.i]) + p.i;
		p.i = (p.end);
		p.j++;
		p.i++;
	}
	return (p.j);
}

 char	**ft_allocation(char *inp, t_points *p)
{
	char	**strs;
	int		count;

	if (!inp)
		return (NULL);
	count = ft_count_cmd(inp);
	strs = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (syntax_error(), NULL);
	p->i = 0;
	p->j = 0;
	return (strs);
}

 char	**split_args(char *inp)
{
	t_points	p;
	char		**strs;

	strs = ft_allocation(inp, &p);
	if (strs == NULL)
		return (NULL);
	while (inp[p.i])
	{
		while (is_white_space(inp[p.i]))
			p.i++;
		if (!inp[p.i])
			break ;
		p.start = p.i;
		if (check_quots(inp + p.i) == 1 && inp[p.i])
			p.end = get_end_quots(inp + p.i) + p.i;
		else if (check_quots(&inp[p.i]) == 0 && inp[p.i])
			p.end = get_end_space(&inp[p.i]) + p.i;
		p.i = (p.end);
		strs[p.j] = ft_substr2(inp, p.start, p.end);
		if (strs[p.j++] == NULL)
			return (ft_free(strs), NULL);
		p.i++;
	}
	strs[p.j] = 0;
	return (strs);
}


char **line_to_args(char *line)
{
    char **cmds;
	char *sp_line;
    t_parse d = {0};

    sp_line = ft_add_sep(line, d);
    cmds = split_args(sp_line);
    // affii
	// int i = 0;
	// while(cmds[i])
	// {
	// 	printf("%d : %s\n",i, cmds[i]);
	// 	i++;
	// }
	free (sp_line);
	return(cmds);
}
