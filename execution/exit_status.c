/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:38:36 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/06/02 20:34:07 by sdiouane         ###   ########.fr       */
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
			printf("value ---> %s\n", tmp->export_i->value);
			break ;
		}
		else
			tmp->export_i = tmp->export_i->next;
	}
}
