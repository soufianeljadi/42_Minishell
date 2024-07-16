/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:02:27 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/06/14 17:56:03 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env *list)
{
	while (list)
	{
		if (ft_strcmp(list->key, "_") != 0 && ft_strcmp(list->key, "?") != 0)
		{
			if (list->value == NULL)
				printf("declare -x %s\n", list->key);
			else
			{
				if (!ft_strcmp(list->value, ""))
				{
					printf("declare -x %s=", list->key);
					printf("\"%s\"\n", list->value);
				}
				else if (ft_strcmp(list->value, ""))
				{
					printf("declare -x %s=", list->key);
					if (list->value[0] == '"')
						printf("%s\n", list->value);
					else
						printf("\"%s\"\n", list->value);
				}
			}
		}
		list = list->next;
	}
}
