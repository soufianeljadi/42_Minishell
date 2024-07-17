/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/17 14:51:23 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_whitespace(char *inp, t_points *p)
{
	while (is_white_space(inp[p->i]))
		p->i++;
}

static void	set_end_position(char *inp, t_points *p)
{
	if (check_quots(inp + p->i) == 1 && inp[p->i])
		p->end = get_end_quots(inp + p->i) + p->i;
	else if (check_quots(&inp[p->i]) == 0 && inp[p->i])
		p->end = get_end_space(&inp[p->i]) + p->i;
}

static char	*create_substring(char *inp, t_points *p)
{
	char	*tmp;
	char	*result;

	tmp = ft_substr2(inp, p->start, p->end);
	result = ft_strjoin(tmp, "");
	free(tmp);
	return (result);
}

static char	**ft_allocation(char *inp, t_points *p)
{
	char	**strs;
	int		count;

	if (!inp)
		return (NULL);
	count = ft_count_cmd(inp);
	strs = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (syntax_error(), NULL);
	p->i = 0;
	p->j = 0;
	return (strs);
}

char	**split_args(char *inp)
{
	char		**strs;
	t_points	p;

	if (!inp)
		return (NULL);
	strs = ft_allocation(inp, &p);
	if (strs == NULL)
		return (NULL);
	while (inp[p.i])
	{
		skip_whitespace(inp, &p);
		if (!inp[p.i])
			break ;
		p.start = p.i;
		set_end_position(inp, &p);
		p.i = p.end;
		strs[p.j] = create_substring(inp, &p);
		if (strs[p.j++] == NULL)
			return (ft_free_tab(strs), NULL);
		p.i++;
	}
	strs[p.j] = 0;
	return (strs);
}
// $LL"$USER"$PWD | ECHO HI