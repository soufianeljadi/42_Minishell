/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/03/27 16:02:51 by sdiouane         ###   ########.fr       */
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


int check_env(char *line)
{
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (strncmp(&line[i], "env", 3) == 0)
	{
		i += 3;
		while ((line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] == '\0')
			return 0;
	}
	return 1;
}

int check_export(char *line)
{
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (strncmp(&line[i], "export", 5) == 0)
	{
		i += 6;
		while ((line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] == '\0')
			return 0;
	}
	return 1;
}
void builtins(char ** args, s_env *s_env)
{
	//ECHO
	echo_fct(args);
	// pwd :
	pwd_without_options(args);
	// unset :
	s_env = unset_fct(args, s_env);
	// export :
	export_fct(args ,s_env);

	//env
	if (!strcmp(args[0], "env") && !args[1])
			print_list(s_env);
	// $variables :
	check_variables(args, s_env);
}
