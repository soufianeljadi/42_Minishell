/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:55:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/19 15:03:53 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_last_cmd(s_env **lst, char **args)
{
	int i;
	s_env *tmp;
	
	i = 0;
	tmp = *lst;
	while (args[i])
		i++;
	while (tmp)
	{
		if (!strcmp(tmp->key, "_"))
			tmp->value = strdup(args[i - 1]);
		tmp = tmp->next;
	}
}

char **struct_to_char(s_env **lst)
{
	char **env;
	int i;
	s_env *tmp;

	i = 0;
	tmp = *lst;
	env = malloc(sizeof(char *) * (ft_lstsize(tmp) + 1));
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=");
		if (tmp->value)
			env[i] = ft_strjoin(env[i], tmp->value);
		else
				env[i] = ft_strjoin(env[i], "");
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

// char **check_quotes_before_execution(char *s)
// {
// 	char **cmd = NULL;

// 	printf("s = %s\n", s);
// 		if ((s[0] == '\"' || s[0] == '\'') && (!strstr(s, " ") && !strstr(s, "\t")))
// 		{
// 			cmd = ft_split(s, ' ');
// 			if (cmd[0][0] == '\0')
// 				exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			if (is_not_empty(s) == 0)
// 			{
// 				cmd = malloc(sizeof(char *) * 2);
// 				cmd[0] = strdup("\0");
// 				cmd[1] = NULL;
// 				return (cmd);
// 			}
// 			else
// 			{
// 				cmd = split_space_tab(s, ' ');
// 				if (cmd[0][0] == '\0')
// 					exit(EXIT_FAILURE);
				
// 			}
// 		}
// 		// int i = 0;
// 		// while (cmd[i])
// 		// {
// 		// 	printf("cmd[%d] = %s\n", i, cmd[i]);
// 		// 	i++;
// 		// }
// 	return (cmd);
// }

char **check_quotes_before_execution(char *s)
{
    char **cmd = NULL;

    // printf("s = %s\n", s);
    if ((s[0] == '\"' || s[0] == '\'') && (strstr(s, " ") || strstr(s, "\t")))
    {
        cmd = ft_split(s, ' ');
        if (!cmd || !cmd[0] || cmd[0][0] == '\0')
        {
            if (cmd) free(cmd);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (is_not_empty(s) == 0)
        {
            cmd = malloc(sizeof(char *) * 2);
            if (!cmd) exit(EXIT_FAILURE); // Vérification de l'allocation
            cmd[0] = strdup("\0");
            if (!cmd[0])
            {
                free(cmd);
                exit(EXIT_FAILURE);
            }
            cmd[1] = NULL;
            return cmd;
        }
        else
        {
            cmd = split_space_tab(s, ' ');
            if (!cmd || !cmd[0] || cmd[0][0] == '\0')
            {
                if (cmd) free(cmd);
                exit(EXIT_FAILURE);
            }
        }
    }
    return cmd;
}
