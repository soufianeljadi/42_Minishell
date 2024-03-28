/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:11:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/27 23:45:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_export(char *str)
{
	int	i;

	i = 0;
	if(str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))) 
			return (1);
		i++;
	}
	return (0);
}



s_env *export_fct(char **args, s_env *env)
{
    int i = 1;
    int j;
    int start;
    char *key;
    char *value;
    s_env *current;
    if (!strcmp(args[0], "export") && !args[1])
        print_export(env);
    else if (!strcmp(args[0], "export"))
	{
        while (args[i])
		{
            j = 0;
            while (args[i][j] != '=' || args[i][j] == '\0')
                j++;
            key = ft_substr(args[i], 0, j);
            if (verif_export(key) == 0)
			{
                if (args[i][j] == '\0')
                    ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
                else
				{
                    j++;
                    start = j;
                    while (args[i][j] && args[i][j] != ' ')
                        j++;
                    value = ft_substr(args[i], start, j - start);
                    if ((value[0] || (args[i][j] == ' ' && args[i][j + 1] != '\0')) && args[i][j] != 'h')
					{
                        current = env;
                        while (current != NULL && current->value)
						{
                            if (strcmp(current->key, key) == 0)
							{
                                free(current->value);
                                current->value = value;
                                break;
                            }
                            current = current->next;
                        }
                        if (current == NULL && key[0])
                            ft_lstadd_back(&env, ft_lstnew_data(value, key));
                    }
					else
					{
                        current = env;
                        while (current != NULL && current->value)
						{
                            if (strcmp(current->key, key) == 0)
							{
                                free(current->value);
                                current->value = strdup("");
                                break;
                            }
                            current = current->next;
                        }
                        if (current == NULL && key[0])
                            ft_lstadd_back(&env, ft_lstnew_data(value, key));
                    }
                }
            } else
                syntax_error();
            i++;
        }
    }
    return env;
}