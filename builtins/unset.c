/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/02 12:23:20 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

s_env *unset_fct(char **args, s_env *env)
{
    int i = 1;
    int j;
    char *key;
    if (!strcmp(args[0], "unset"))
	{
        while (args[i])
		{
            j = 0;
            while (args[i][j])
			{
                while (args[i] && args[i][j] != ' ' && args[i][j] != '\t' && args[i][j] != '\0')
                    j++;
                key = ft_substr2(args[i], 0, j);
                // key = get_key(args[i], j);

                s_env *prev = NULL;
                s_env *current = env;
                if (verif_export(key) == 1)
                    fprintf(stderr, "minishell: unset: `%s': not found\n", key);
				else
				{
					while (current != NULL)
					{
						if (strcmp(current->key, key) == 0)
						{
							if (prev != NULL)
								prev->next = current->next;
							else
								env = current->next;
							free(current->key);
							free(current->value);
							free(current);
							break;
						}
						prev = current;
						current = current->next;
					}
					free(key);
					while (args[i][j] == ' ' || args[i][j] == '\t')
						j++;
				}
            }
            i++;
        }
    }
    return env;
}
