/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/08 18:08:30 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cc(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '"')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

void cc2(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '\'')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}
s_env *unset_fct(char **args, s_env *env)
{
    int i = 1;
    int j;
    char *key;
    if (!strcmp(args[0], "unset"))
	{
        while (args[i])
		{
			printf("args[%d] = %s\n", i, args[i]);
			cc(args[i]);
			if (args[i][0] == '\'')
				cc2(args[i]);
            j = 0;
            while (args[i][j])
			{
                while (args[i] && args[i][j] != ' ' && args[i][j] != '\t' && args[i][j] != '\0')
                    j++;
                key = ft_substr2(args[i], 0, j);
                // key = get_key(args[i], j);

                s_env *prev = NULL;
                s_env *current = env;
				printf("key = %s\n", key);
                if (verif_export(key) == 1)
                    fprintf(stderr, "minishell: unset: %s: not a valid identifier\n", key);
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
