/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:11:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/23 02:45:09 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_of_env(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);
}

s_env *export_fct(char *line, s_env *env)
{
    int i = 0;
    int start1, start2;
    char *key, *value;

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (strncmp(&line[i], "export", 6) == 0)
    {
        i += 6;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        while (line[i] != '\0')
        {
            start1 = i;
            while (line[i] != '=' && line[i] != '\0')
                i++;
            if (line[i] != '=')
            {
                syntax_error();
                exit(EXIT_FAILURE);
            }
            start2 = ++i;
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
                i++;
            value = ft_substr(&line[start2], 0, i - start2);
            key = ft_substr(&line[start1], 0, start2 - start1 - 1);
            s_env *current = env;
            while (current != NULL)
            {
                if (strcmp(current->key, key) == 0)
                {
                    free(current->value);
                    current->value = value;
                    break;
                }
                current = current->next;
            }
            if (current == NULL)
                ft_lstadd_back(&env, ft_lstnew_data(value, key));
            while (line[i] == ' ' || line[i] == '\t')
                i++;
        }
    }
    return env;
}