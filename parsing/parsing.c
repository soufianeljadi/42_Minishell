/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:55:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/08 18:09:04 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(void)
{
	printf("syntax error \n");
}

int	parsing(char *line, t_data *data)
{
	(void)data;
	if (parse_single_input(line, '|') || line[0] == '|')
		return (1);
	if (ft_quots(&line))
		return (1);
	if (parse_redirection(line) == 1)
		return (1);
	return (0);
}
