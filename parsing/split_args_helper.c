/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/17 13:11:56 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
