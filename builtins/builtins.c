/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/03/31 01:30:53 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int get_len_env(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);	
}

void check_variables(char **args, s_env *lst)
{
    char *key;
    s_env *current;
    int i = 0;
    int j;
    while (args[i])
	{
        j = 0;
        while (args[i][j])
		{
            if (args[i][j] == '$')
			{
                int key_start = j + 1;
                while (args[i][j] && args[i][j] != ' ' && args[i][j] != '\t')
                    j++;
                key = (char *)malloc(((j - key_start) + 1) * sizeof(char));
                if (!key)
                    exit(EXIT_FAILURE);
                strncpy(key, &args[i][key_start], j - key_start);
                key[j - key_start] = '\0';
                current = lst;
                while (current)
				{
                    if (strcmp(current->key, key) == 0)
					{
                        printf("%s\n", current->value);
                        break;
                    }
                    current = current->next;
                }
                free(key);
            }
			else
                j++;
        }
        i++;
    }
}

void builtins(char **args, s_env *s_env)
{
	// echo :
	echo_fct(args);
	// pwd :
	pwd_without_options(args);
	// unset :
	s_env = unset_fct(args, s_env);
	// export :
	export_fct(args ,s_env); // += 
	//env
	if (!strcmp(args[0], "env") && !args[1])
			print_list(s_env);
	// $variables :
	check_variables(args, s_env);
}
  