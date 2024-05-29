/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:38:36 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/26 22:52:39 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_status(int status, ExecutionData *data)
{
	g_flags.exit_status = status;

	ExecutionData *tmp;
	tmp = data;
	while (tmp->export_i)
	{
		if (!strcmp(tmp->export_i->key,"?"))
		{
			free(tmp->export_i->value);
			tmp->export_i->value = ft_strdup(ft_itoa(g_flags.exit_status));
			return ;
		}
		tmp->export_i = tmp->export_i->next;
	}
}

