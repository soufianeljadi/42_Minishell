/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_helper_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:34:57 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/06/09 22:35:34 by sel-jadi         ###   ########.fr       */
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
